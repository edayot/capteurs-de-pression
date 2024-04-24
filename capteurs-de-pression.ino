#include <Servo.h>
#include "Arduino.h"

#define IN0 A0
#define IN1 A1
#define MOTOR 6

Servo myservo;



void setup()
{
    // pinMode(PIN_LED, OUTPUT);
    pinMode(IN0, INPUT);
    pinMode(IN1, INPUT);
    Serial.begin(115200);
    Serial.println("Hello World");
    myservo.attach(MOTOR);
	
}

double pos = 90;

void loop()
{   
    int value1 = analogRead(IN0);
    int value2 = analogRead(IN1);

    int value = (value1 + value2) / 2;

    pos = map(value, 0, 1023, 0, 180);


    myservo.write(pos);
    
    Serial.println(String(value1) + " " + String(value2) + " " + String(value) + " " + String(pos));
    delay(50);
}
