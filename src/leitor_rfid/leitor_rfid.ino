/*
   Adaptado para ESP32 WROOM-32

   - ESP32 possui múltiplas portas seriais: Serial, Serial1, Serial2.
   - Neste exemplo, usaremos Serial2 para comunicação com o módulo RFID.
   - Ajuste os pinos RX/TX conforme sua ligação:
       RX do ESP32 ← TX do leitor
       TX do ESP32 → RX do leitor
   - Ajuste o baud rate conforme o módulo (geralmente 9600 ou 115200)
*/

#define RX_PIN 16  // Pino RX do ESP32 conectado ao TX do leitor
#define TX_PIN 17  // Pino TX do ESP32 conectado ao RX do leitor

// Comando "Single Polling" (ler uma única tag no campo)
byte singlePollingCmd[] = {0xBB, 0x00, 0x22, 0x00, 0x00, 0x22, 0x7E};

void setup() {
  Serial.begin(115200);          // Monitor Serial do PC
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); // Serial para o leitor RFID

  Serial.println("Iniciando RFID UHF no ESP32...");
}

void loop() {
  // Envia o comando "Single Polling" para o leitor
  Serial2.write(singlePollingCmd, sizeof(singlePollingCmd));
  Serial.println("Comando enviado: Single Polling");

  // Aguarda resposta do leitor por até 500 ms
  unsigned long start = millis();
  while (millis() - start < 500) {
    if (Serial2.available()) {
      byte b = Serial2.read();
      printHex(b);
      Serial.print(" ");
    }
  }

  Serial.println();
  delay(2000); // espera 2 segundos antes da próxima leitura
}

// Função auxiliar: imprime byte em HEX sempre com 2 dígitos
void printHex(byte num) {
  if (num < 0x10) Serial.print("0");
  Serial.print(num, HEX);
}
