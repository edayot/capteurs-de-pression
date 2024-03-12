
#include "Arduino.h"

// #define PIN_LED 13
#define PIN_ANALOG_IN A0




void setup()
{
    // pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_ANALOG_IN, INPUT);
    Serial.begin(9600);
    Serial.println("Hello World");
	
}

void loop()
{
    int value = analogRead(PIN_ANALOG_IN);
    float voltage = value * (5.0 / 1023.0);
    Serial.println(voltage);
    delay(200);
}
