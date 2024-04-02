#include <Servo.h>


#include "Arduino.h"


// #define PIN_LED 13
#define PIN_ANALOG_IN A0
#define MOTOR 9

Servo myservo;



void setup()
{
    // pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_ANALOG_IN, INPUT);
    Serial.begin(9600);
    Serial.println("Hello World");
    myservo.attach(MOTOR);
	
}

int pos = 0;

void loop()
{   
    int value = analogRead(PIN_ANALOG_IN);

    if (value <= 512) {
        pos ++;
    }
    else {
        pos --;
    }
    if (pos < 0) {pos = 0;}
    if (pos > 180) {pos = 180;}


    myservo.write(pos);
    
    Serial.println(value);
    Serial.println(pos);
    delay(10);
}
