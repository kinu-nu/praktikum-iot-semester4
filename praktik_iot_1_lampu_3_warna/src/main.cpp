#include <Arduino.h>

int ledm = 15;
int ledk = 16;
int ledh = 17;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledm, OUTPUT);
  pinMode(ledk, OUTPUT);
  pinMode(ledh, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledm, HIGH);
  digitalWrite(ledk, LOW);
  digitalWrite(ledh, LOW);
  delay(30000);
  digitalWrite(ledm, LOW);
  digitalWrite(ledk, HIGH);
  digitalWrite(ledh, LOW);
  delay(5000);
  digitalWrite(ledm, LOW);
  digitalWrite(ledk, LOW);
  digitalWrite(ledh, HIGH);
  delay(20000);
}