#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Vírus";
const char* password = "397810Wa#";
const char* serverName = "https://vercel-api-two-brown.vercel.app/";

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

    HTTPClient http;
    http.begin(serverName);

    Serial.println("Contagem regressiva de 10 segundos:");
  
    for (int i = 10; i >= 0; i--) {
      Serial.println(i);
      delay(500); // espera meio segundo
    }
  
    Serial.println("Tempo esgotado!");

    int httpResponseCode = http.GET();
    if (httpResponseCode == 200) {
      String payload = http.getString();
      Serial.print("Resposta da API: ");
      Serial.println(payload);

      digitalWrite(ledPin, HIGH); // acende LED se a API respondeu corretamente
    } else {
      Serial.print("Erro na requisição. Código: ");
      Serial.println(httpResponseCode);

      digitalWrite(ledPin, LOW); // apaga LED se não houve resposta 200
    }
    http.end();
  } else {
    Serial.println("\nFalha na conexão Wi-Fi");
    digitalWrite(ledPin, LOW); // apaga LED se não conectou
  }
}

void loop() {
  // nada aqui
}
