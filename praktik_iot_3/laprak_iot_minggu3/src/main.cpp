#include <DHT.h>
#include <LiquidCrystal.h>

// Konfigurasi LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

// Konfigurasi DHT22
#define DHTPIN 21
#define DHTTYPE DHT22
#define TIMEDHT 1000

float humidity, celsius;
uint32_t timerDHT = TIMEDHT;
DHT dht(DHTPIN, DHTTYPE);

// Konfigurasi LDR
#define LDRPIN 34  // Pin LDR pada ESP32

void getSensorData() {
  if ((millis() - timerDHT) > TIMEDHT) {
    timerDHT = millis();
    
    // Membaca data dari sensor DHT22
    humidity = dht.readHumidity();
    celsius = dht.readTemperature();
    
    if (isnan(humidity) || isnan(celsius)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Membaca data dari sensor LDR
    int lightValue = analogRead(LDRPIN);
    float intensity = (lightValue / 4095.0) * 100.0; // Konversi ke persen

    // Menampilkan data di Serial Monitor
    Serial.print("Temp: "); Serial.print(celsius, 1); Serial.println("C");
    Serial.print("Humidity: "); Serial.print(humidity, 1); Serial.println("%");
    Serial.print("Light: "); Serial.print(intensity, 1); Serial.println("%");

    // Menampilkan data di LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tempt:"); lcd.print(celsius, 1); lcd.print("C ");
    lcd.print("H:"); lcd.print(humidity, 1); lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("Light: "); lcd.print(intensity, 1); lcd.print("%  ");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();
}

void loop() {
  getSensorData();
  delay(500);
}
