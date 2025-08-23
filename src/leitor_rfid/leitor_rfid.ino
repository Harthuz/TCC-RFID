/*
  Leitor UHF-RFID com ESP32 WROOM-32
  Baseado no protocolo oficial do módulo (Unit-RFID-UHF-Protocol-EN)

  Conexões:
    ESP32 RX (GPIO16) <- TX do leitor RFID
    ESP32 TX (GPIO17) -> RX do leitor RFID
    GND <-> GND
    5V  <-> VCC
*/

#define RX_PIN 16 // RX do ESP32
#define TX_PIN 17 // TX do ESP32

// Comando oficial "Single Polling" (inventário de uma tag)
byte singlePollingCmd[] = { 0xBB, 0x00, 0x22, 0x00, 0x00, 0x22, 0x7E };

// ------------------------ SETUP ------------------------
void setup() {
  Serial.begin(9600); // Monitor Serial
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN); // UART com módulo RFID

  Serial.println("Iniciando leitor UHF-RFID...");
}

// ------------------------ LOOP ------------------------
void loop() {
  enviarComando(singlePollingCmd, sizeof(singlePollingCmd));
  delay(1000); // Faz leitura a cada 1 segundo
}

// ------------------------ FUNÇÕES AUXILIARES ------------------------
void enviarComando(byte *cmd, int len) {
  // Envia comando para o módulo RFID
  Serial2.write(cmd, len);

  Serial.print(">> Enviado: ");
  for (int i = 0; i < len; i++) {
    printHex(cmd[i]);
    Serial.print(" ");
  }
  Serial.println();

  delay(100); // Aguarda resposta

  if (Serial2.available()) {
    Serial.println("<< Resposta recebida:");
    while (Serial2.available()) {
      byte b = Serial2.read();
      printHex(b);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    Serial.println("Nenhuma resposta do módulo.");
  }
}

void printHex(byte num) {
  if (num < 0x10) Serial.print("0");
  Serial.print(num, HEX);
}
