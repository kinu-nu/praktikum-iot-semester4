#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6ZKCyS-tg"
#define BLYNK_TEMPLATE_NAME "uts iot"
#define BLYNK_AUTH_TOKEN "B2YUkJGiZdlG3FHz7qEwNRzm7E_7omTz"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// ------------------- Blynk Config -------------------
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;

// ------------------- Pin Setup -------------------
#define TRIG_PIN 18
#define ECHO_PIN 19
#define LED_PIN 14
#define BUZZER_PIN 15

// ------------------- Variabel Jarak -------------------
long duration;
int distance;

// ------------------- Fungsi Efek -------------------
void kondisiDarurat() {
  digitalWrite(LED_PIN, HIGH);
  for (int i = 0; i < 5; i++) {
    tone(BUZZER_PIN, 2000, 100);
    delay(110);
  }
}

void kedapKedipCepat() {
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  tone(BUZZER_PIN, 1000, 100);
  delay(150);
}

void kedapKedipLambat() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  tone(BUZZER_PIN, 500, 100);
  delay(500);
}

// ------------------- Kirim Data ke Blynk & Kontrol -------------------
void sendSensorData() {
  // Trigger sensor ultrasonik
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // Kirim ke Blynk
  Blynk.virtualWrite(V0, distance);

  // Log jarak ke Serial
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Logika kontrol
  if (distance < 15) {
    kondisiDarurat();
    Serial.println("⚠ Jarak sangat dekat! Risiko tabrakan.");
  } else if (distance <= 50) {
    kedapKedipCepat();
  } else if (distance <= 100) {
    kedapKedipLambat();
  } else if (distance <= 150) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

// ------------------- Setup -------------------
void setup() {
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("🚀 Sistem Monitoring Jarak Siap!");

  timer.setInterval(1000L, sendSensorData);
}

// ------------------- Loop -------------------
void loop() {
  Blynk.run();
  timer.run();
}
