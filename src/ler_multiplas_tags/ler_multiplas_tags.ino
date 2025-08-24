/*
  Leitor UHF-RFID com ESP32 WROOM-32
  Baseado no protocolo oficial do módulo (Unit-RFID-UHF-Protocol-EN)
*/

#define RX_PIN 16 // RX do ESP32
#define TX_PIN 17 // TX do ESP32

// Comando oficial "Single Polling" (inventário de uma tag)
byte singlePollingCmd[] = { 0xBB, 0x00, 0x22, 0x00, 0x00, 0x22, 0x7E };

void setup() {
  Serial.begin(9600); 
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN); 
  Serial.println("Iniciando leitor UHF-RFID...");
}

void loop() {
  enviarComando(singlePollingCmd, sizeof(singlePollingCmd));
  delay(1000);
}

// ------------------------ FUNÇÕES ------------------------

void enviarComando(byte *cmd, int len) {
  Serial2.write(cmd, len);

  delay(100); // espera resposta

  if (Serial2.available()) {
    // monta buffer de resposta
    int count = Serial2.available();
    byte resposta[256];  // Aumentei o tamanho do buffer para lidar com múltiplas tags
    for (int i = 0; i < count; i++) {
      resposta[i] = Serial2.read();
    }

    // imprime bruto (debug)
    Serial.print("<< Resposta (HEX): ");
    for (int i = 0; i < count; i++) {
      printHex(resposta[i]); Serial.print(" ");
    }
    Serial.println();

    // traduz a resposta (opcional)
    traduzirResposta(resposta, count);
  } else {
    Serial.println("Nenhuma resposta do módulo.");
  }
}

// Função para traduzir resposta do tipo Notification Frame (Single Polling)
void traduzirResposta(byte *data, int len) {
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
      String epcAscii = "";

      for (int j = 0; j < epcLen; j++) {
        byte b = data[i + 8 + j];
        if (b < 0x10) epcHex += "0";
        epcHex += String(b, HEX);

        if (b >= 32 && b <= 126) {
          epcAscii += (char)b;
        }
      }

      // CRC está no final
      int crcIndex = i + 8 + epcLen;
      uint16_t crc = (data[crcIndex] << 8) | data[crcIndex + 1];

      // Exibe informações da tag lida
      Serial.println("---- TAG LIDA ----");
      Serial.print("RSSI: "); Serial.print((int8_t)rssi); Serial.println(" dBm");
      Serial.print("PC: "); Serial.print(pc_msb, HEX); Serial.println(pc_lsb, HEX);
      Serial.print("EPC (HEX): "); Serial.println(epcHex);
      Serial.print("EPC (ASCII): "); Serial.println(epcAscii);
      Serial.print("CRC: 0x"); Serial.println(crc, HEX);
      Serial.println("------------------");

      // Avança para o próximo pacote de tag
      i = crcIndex + 2 + 1; // O pacote termina 2 bytes após o CRC + 1 byte do 0x7E
    } else {
      i++;
    }
  }
}

// Imprime byte em HEX
void printHex(byte num) {
  if (num < 0x10) Serial.print("0");
  Serial.print(num, HEX);
}
