#define BLYNK_TEMPLATE_ID "TMPL3p3SjvEee"
#define BLYNK_TEMPLATE_NAME "weather monitoring"
#define BLYNK_AUTH_TOKEN "MJMSH-vJFZZV2cEf11UVqtVLj_J1hZFq"

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN 2 // the NodeMCU pin where DHT is connected
#define DHTTYPE DHT11 // DHT 11 sensor type

DHT dht(DHTPIN, DHTTYPE);
Servo servo1;

// Your WiFi credentials
char ssid[] = "Airtel_ardent_5472";
char pass[] = "Ardent!132";

void setup() {
  // Debug console
  Serial.begin(115200);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Read humidity and temperature from DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Print humidity to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Send temperature and humidity to Blynk
  Blynk.virtualWrite(V3, humidity);
  Blynk.virtualWrite(V4, temperature);
  
  // Delay for 3 seconds before reading again
  delay(3000);
}
