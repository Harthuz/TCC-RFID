#include <HardwareSerial.h>

#define RFID_RX_PIN 16
#define RFID_TX_PIN 17
HardwareSerial rfidSerial(2);

void setup() {
  Serial.begin(9600);
  rfidSerial.begin(115200, SERIAL_8N1, RFID_RX_PIN, RFID_TX_PIN);
  Serial.println("Leitor RFID EPC - Pronto");
}

void loop() {  
  // Leitura automática a cada 5 segundos
  static unsigned long lastRead = 0;
  if (millis() - lastRead > 5000) {
    readAndDisplayEPC();
    lastRead = millis();
  }
}

void readAndDisplayEPC() {
  // Enviar comando de polling único
  uint8_t pollCommand[] = {0xBB, 0x00, 0x22, 0x00, 0x00, 0x22, 0x7E};
  rfidSerial.write(pollCommand, sizeof(pollCommand));
  
  delay(100);
  
  if (rfidSerial.available() >= 7) {
    if (rfidSerial.read() == 0xBB) {
      uint8_t type = rfidSerial.read();
      uint8_t command = rfidSerial.read();
      uint16_t paramLength = (rfidSerial.read() << 8) | rfidSerial.read();
      
      if (type == 0x02 && command == 0x22) {
        // Extrair dados EPC
        String epcHex = "";
        uint8_t rssi = rfidSerial.read();
        rfidSerial.read(); // PC MSB
        rfidSerial.read(); // PC LSB
        
        for (uint16_t i = 0; i < paramLength - 3; i++) {
          uint8_t byte = rfidSerial.read();
          if (byte < 0x10) epcHex += "0";
          epcHex += String(byte, HEX);
        }
        
        // Converter para ASCII legível
        String epcAscii = "";
        for (size_t i = 0; i < epcHex.length(); i += 2) {
          String byteStr = epcHex.substring(i, i + 2);
          char chr = (char)strtol(byteStr.c_str(), NULL, 16);
          if (chr >= 32 && chr <= 126) {
            epcAscii += chr;
          }
        }
        
        Serial.print("EPC: ");
        Serial.println(epcAscii);
        Serial.print("RSSI: ");
        Serial.println(rssi);
        
        // Limpar buffer
        while (rfidSerial.available()) rfidSerial.read();
      }
    }
  }
}

String hexToAscii(const String& hexString) {
  String result = "";
  for (size_t i = 0; i < hexString.length(); i += 2) {
    String byteStr = hexString.substring(i, i + 2);
    char c = (char)strtol(byteStr.c_str(), NULL, 16);
    if (c >= 32 && c <= 126) result += c;
  }
  return result;
}
