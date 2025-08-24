#define RX_PIN 16 // RX do ESP32
#define TX_PIN 17 // TX do ESP32

// Comando oficial "Single Polling" (inventário de uma tag)
byte singlePollingCmd[] = { 0xBB, 0x00, 0x22, 0x00, 0x00, 0x22, 0x7E };

String tipoProduto, marcaProduto, categoriaProduto, validadeProduto;
String loteID;
String epcList[100];  // Lista de EPCs detectados
int epcCount = 0;     // Contador de EPCs lidos

void setup() {
  Serial.begin(9600); 
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN); 
  Serial.println("Iniciando leitor UHF-RFID...");
}

void loop() {
  // Limpa o vetor de EPCs antes de cada nova leitura
  epcCount = 0;

  // Enviar comando para ler múltiplas tags
  enviarComando(singlePollingCmd, sizeof(singlePollingCmd));
  
  // Se encontrou tags, processa as informações
  if (epcCount > 0) {
    // Gerar um ID único para o lote
    loteID = "L" + String(millis());

    // Solicitar informações do produto
    Serial.println("Digite as informações do produto:");
    Serial.print("Tipo: ");
    tipoProduto = leituraSerial();
    
    Serial.print("Marca: ");
    marcaProduto = leituraSerial();
    
    Serial.print("Categoria: ");
    categoriaProduto = leituraSerial();
    
    Serial.print("Validade (YYYY-MM-DD): ");
    validadeProduto = leituraSerial();
    
    // Gravar informações no "banco de dados" (simulado aqui no console)
    for (int i = 0; i < epcCount; i++) {
      Serial.println("---- Gravando Dados ----");
      Serial.print("EPC: "); Serial.println(epcList[i]);
      Serial.print("Lote ID: "); Serial.println(loteID);
      Serial.print("Tipo: "); Serial.println(tipoProduto);
      Serial.print("Marca: "); Serial.println(marcaProduto);
      Serial.print("Categoria: "); Serial.println(categoriaProduto);
      Serial.print("Validade: "); Serial.println(validadeProduto);
      Serial.println("-----------------------");
    }

    // Limpar lista de EPCs para o próximo lote
    memset(epcList, 0, sizeof(epcList));
    epcCount = 0;
  }
  
  delay(1000);
}

// ------------------------ FUNÇÕES ------------------------

void enviarComando(byte *cmd, int len) {
  Serial2.write(cmd, len);
  delay(100); // espera resposta

  if (Serial2.available()) {
    int count = Serial2.available();
    byte resposta[256];  
    for (int i = 0; i < count; i++) {
      resposta[i] = Serial2.read();
    }

    // Processa a resposta e extrai os EPCs das tags
    processarResposta(resposta, count);
  } else {
    Serial.println("Nenhuma resposta do módulo.");
  }
}

void processarResposta(byte *data, int len) {
  int i = 0;

  while (i < len) {
    if (data[i] == 0xBB && data[i+1] == 0x02 && data[i+2] == 0x22) {
      // Encontrou o início de um pacote de tag
      int paramLen = (data[i+3] << 8) | data[i+4];
      byte rssi = data[i+5];
      byte pc_msb = data[i+6];
      byte pc_lsb = data[i+7];

      int epcLen = paramLen - 5; // desconta RSSI + PC(2B) + CRC(2B)
      String epcHex = "";

      for (int j = 0; j < epcLen; j++) {
        byte b = data[i + 8 + j];
        if (b < 0x10) epcHex += "0";
        epcHex += String(b, HEX);
      }

      // Adiciona o EPC à lista
      if (epcCount < 100) {  // Garantir que não exceda o tamanho do vetor
        epcList[epcCount] = epcHex;
        epcCount++;
      }

      // Avança para o próximo pacote de tag
      int crcIndex = i + 8 + epcLen;
      i = crcIndex + 2 + 1; // O pacote termina 2 bytes após o CRC + 1 byte do 0x7E
    } else {
      i++;
    }
  }
}

// Função para ler entrada serial
String leituraSerial() {
  String input = "";
  while (Serial.available() == 0) {}
  while (Serial.available() > 0) {
    char c = Serial.read();
    input += c;
    delay(10);
  }
  input.trim();  // Remover espaços em branco
  return input;
}
