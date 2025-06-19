#include <Arduino.h>

// Deklarasi pin tombol
int tombol1 = 34;
int tombol2 = 33;
int tombol3 = 32;

// Deklarasi pin LED
int lampuMerah = 23;
int lampuKuning = 22;
int lampuHijau = 21;

void setup()
{
  Serial.begin(115200);
  Serial.println("Program LED dan Tombol ESP32");

  // Konfigurasi tombol sebagai input dengan pull-up internal
  pinMode(tombol1, INPUT_PULLUP);
  pinMode(tombol2, INPUT_PULLUP);
  pinMode(tombol3, INPUT_PULLUP);

  // Konfigurasi LED sebagai output
  pinMode(lampuMerah, OUTPUT);
  pinMode(lampuKuning, OUTPUT);
  pinMode(lampuHijau, OUTPUT);
}

void loop()
{
  if (digitalRead(tombol1) == LOW)
  {
    // Tombol 1: Lampu merah berkedip 5 kali
    for (int i = 0; i < 5; i++)
    {
      digitalWrite(lampuMerah, HIGH);
      delay(500);
      digitalWrite(lampuMerah, LOW);
      delay(500);
    }
  }

  if (digitalRead(tombol2) == LOW)
  {
    // Tombol 2: Lampu merah dan hijau berkedip bergantian
    for (int i = 0; i < 5; i++)
    {
      digitalWrite(lampuMerah, HIGH);
      digitalWrite(lampuHijau, LOW);
      delay(500);
      digitalWrite(lampuMerah, LOW);
      digitalWrite(lampuHijau, HIGH);
      delay(500);
    }
    digitalWrite(lampuHijau, LOW); // Matikan LED setelah selesai
  }

  if (digitalRead(tombol3) == LOW)
  {
    // Tombol 3: Lampu merah, kuning, dan hijau berkedip bergantian
    for (int i = 0; i < 5; i++)
    {
      digitalWrite(lampuMerah, HIGH);
      delay(500);
      digitalWrite(lampuMerah, LOW);
      digitalWrite(lampuKuning, HIGH);
      delay(500);
      digitalWrite(lampuKuning, LOW);
      digitalWrite(lampuHijau, HIGH);
      delay(500);
      digitalWrite(lampuHijau, LOW);
    }
  }
}
