/*
   Exemplo de comunicação com módulo RFID UHF (protocolo do manual)

   - O Arduino envia um comando "Single Polling" (BB 00 22 00 00 22 7E)
     para pedir ao leitor que leia uma tag.
   - O módulo responde com um frame contendo EPC, RSSI, CRC, etc.
   - O código lê a resposta byte a byte e imprime no Monitor Serial.

   >>> PASSOS:
   1. Ajuste a Serial correta:
      - Se for um Arduino UNO → usar SoftwareSerial em pinos RX/TX.
      - Se for Mega ou ESP32 → pode usar Serial1 / Serial2 direto.
   2. Conecte TX do leitor → RX do Arduino e RX do leitor → TX do Arduino.
   3. Ajuste o baud rate (9600 ou 115200, conforme seu leitor).
   4. Abra o Monitor Serial para ver o EPC das tags.
*/

#include <SoftwareSerial.h>

// Defina os pinos usados para RX/TX (se usar Arduino UNO)
// RX do Arduino ← TX do leitor
// TX do Arduino → RX do leitor
SoftwareSerial rfidSerial(10, 11); // RX=10, TX=11

// Comando "Single Polling" (ler uma única tag no campo)
byte singlePollingCmd[] = {0xBB, 0x00, 0x22, 0x00, 0x00, 0x22, 0x7E};

void setup() {
  Serial.begin(9600);      // Monitor Serial do PC
  rfidSerial.begin(9600);  // Porta serial para o leitor RFID (ajuste se necessário)

  Serial.println("Iniciando RFID UHF...");
}

void loop() {
  // Envia o comando para o leitor pedir leitura de tag
  rfidSerial.write(singlePollingCmd, sizeof(singlePollingCmd));
  Serial.println("Comando enviado: Single Polling");

  // Aguarda resposta por até 500 ms
  unsigned long start = millis();
  while (millis() - start < 500) {
    if (rfidSerial.available()) {
      byte b = rfidSerial.read();
      printHex(b);
      Serial.print(" ");
    }
  }

  Serial.println();
  delay(2000); // espera 2 segundos antes da próxima leitura
}

// Função auxiliar: imprime byte em HEX sempre com 2 dígitos
void printHex(byte num) {
  if (num < 0x10) {
    Serial.print("0");
  }
  Serial.print(num, HEX);
}
