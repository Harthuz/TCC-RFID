#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Vírus";
const char* password = "397810Wa#";
const char* serverName = "https://randomuser.me/api/";

const int ledPin = 2; // LED no pino 2

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20) { // tenta por ~10s
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConectado ao Wi-Fi");
    digitalWrite(ledPin, HIGH); // LED acende
  } else {
    Serial.println("\nFalha na conexão Wi-Fi");
    digitalWrite(ledPin, LOW); // LED apaga
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String payload = http.getString();

      StaticJsonDocument<2048> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        const char* firstName = doc["results"][0]["name"]["first"];
        const char* lastName  = doc["results"][0]["name"]["last"];
        Serial.print("Primeiro nome: "); Serial.println(firstName);
        Serial.print("Último nome: "); Serial.println(lastName);
      } else {
        Serial.print("Erro ao parsear JSON: "); Serial.println(error.f_str());
      }
    } else {
      Serial.print("Erro na requisição. Código: "); Serial.println(httpResponseCode);
    }
    http.end();
  }
}

void loop() {
  // nada aqui
}
