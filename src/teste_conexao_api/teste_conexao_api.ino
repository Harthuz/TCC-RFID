#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Vírus";
const char* password = "397810Wa#";
const char* serverName = "https://randomuser.me/api/";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao Wi-Fi");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);

    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String payload = http.getString();

      // Usando StaticJsonDocument para evitar warning
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

void loop() {}
