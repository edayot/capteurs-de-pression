#include "Arduino.h"
#include <Servo.h>

#define IN0 A0
#define IN1 A1
#define IN2 A2
#define MOTOR 6


Servo servo;

void setup()
{
    // pinMode(PIN_LED, OUTPUT);
    pinMode(IN0, INPUT);
    pinMode(IN1, INPUT);
    pinMode(IN2, INPUT);
    
    Serial.begin(115200);
    Serial.println("Hello World");

    servo.attach(MOTOR);
}


void loop()
{   
    int value0 = analogRead(IN0);
    int value1 = analogRead(IN1);
    int value2 = analogRead(IN2);

    int sum = value0 + value1 + value2;

    
    Serial.print(String(value0) + " " + String(value1) + " " + String(value2) + " " + String(sum) + "\n");


    if (sum < 300)
    {
        servo.write(0);
    }
    else if (sum >= 300 && sum < 1200)
    {
        servo.write(180);
    }
    else if (sum >= 1200)
    {
        servo.write(0);
    }

    
    delay(50);
}
