#include <WiFi.h>
#include <HTTPClient.h>

#define MQ135PIN 34  // Ganti dengan pin analog yang digunakan untuk MQ-135

const char* ssid = "VICCEN_Acces"; // Ganti dengan SSID WiFi Anda
const char* password = "A85D4049A73"; // Ganti dengan password WiFi Anda

const char* serverName = "http://192.168.8.101:5000/data"; // Ganti dengan URL server Anda

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  int sensorValue = analogRead(MQ135PIN); // Membaca nilai dari sensor MQ-135

  // Simulasi konversi nilai sensor menjadi nilai CO2 (ppm)
  // Anda harus mengganti bagian ini dengan konversi yang sesuai untuk sensor MQ-135 Anda
  float co2 = sensorValue; // Misalnya, ini adalah nilai CO2 yang dikonversi

  // Check WiFi connection
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Specify request destination
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Prepare JSON payload
    String postData = "{\"CO2\": " + String(co2) + "}";

    // Send HTTP POST request
    int httpResponseCode = http.POST(postData);

    // Handle HTTP response
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    // Close connection
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // Wait before sending the next request
  delay(2000);
}