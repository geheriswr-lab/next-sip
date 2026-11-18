/*
  NEXT SIP — Smart Cellar IoT Probe
  ESP32 + DS18B20 Temperature Monitor
*/
#include <WiFi.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverApi = "https://your-domain.com/api/iot/readings";
const char* deviceKey = "YOUR_DEVICE_KEY";

#define ONE_WIRE_BUS 4  // GPIO4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (WiFi.status() == WL_CONNECTED && tempC != DEVICE_DISCONNECTED_C) {
    HTTPClient http;
    http.begin(serverApi);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Device-Key", deviceKey);

    String payload = "{\"temp_c\":" + String(tempC, 2) + "}";
    int httpResponseCode = http.POST(payload);
    Serial.printf("POST: %.2f C, Response: %d\n", tempC, httpResponseCode);
    http.end();
  }
  delay(60000); // Send every 60 seconds
}
