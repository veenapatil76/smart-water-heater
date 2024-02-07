#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 14 // DHT11 data pin on ESP32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int TEC_PIN = 13; // Pin connected to the NPN transistor base
const float TARGET_TEMP = 25.0; // Set your desired temperature in Celsius

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(TEC_PIN, OUTPUT);
}

void loop() {
  delay(2000); // Delay for 2 seconds between readings

  float temperature = dht.readTemperature(); // Read temperature from DHT11 sensor

  if (!isnan(temperature)) {
    Serial.print("Temperature: ");
    Serial.println(temperature);

    if (temperature < TARGET_TEMP) {
      // Turn on the TEC1 cooler
      digitalWrite(TEC_PIN, HIGH);
    } else {
      // Turn off the TEC1 cooler
      digitalWrite(TEC_PIN, LOW);
    }
  } else {
    Serial.println("Failed to read from DHT sensor.");
  }
}

