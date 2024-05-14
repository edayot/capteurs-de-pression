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
    servo.write(0);
}


int state = 0;
int attente_max = 100;
int attente = 0;

int tps_rempli = 0;
// 0 == standby
// 1 == verre détecté
// 2 == remplissage
// 3 == verre détecté plein, on attend qu'il soit retiré

void loop()
{   
    int value0 = analogRead(IN0);
    int value1 = analogRead(IN1);
    int value2 = analogRead(IN2);  

    int sum = value0 + value1 + value2;

    
    Serial.print(String(sum) + " " + String(state) + " " + String(attente) + " " + String(attente_max) + "\n");


    // match case
    switch (state)
    {
        case 0:
            if (sum > 300)
            {
                state = 1;
                attente = 0;
            }
            break;
        case 1:
            attente++;
            if (attente > attente_max / 2 && sum < 900)
            {
                state = 2;
                attente = 0;
                tps_rempli = 0;
            }
            if (sum < 50 || sum > 900)
            {
                state = 3;
                attente = 0;
            }
            break;
        case 2:
            attente++;
            if ((attente > attente_max * 4) || sum < 50 || tps_rempli > 10)
            {
                state = 3;
                attente = 0;
                tps_rempli = 0;
                break;
            }
            if (sum > 900)
            {
                tps_rempli++;
            }
            servo.write(180);
            break;
        case 3:
            servo.write(0);
            attente++;
            if (attente > attente_max / 2 && sum < 300)
            {
                state = 0;
                attente = 0;
            }
            break;
    }

    
    delay(50);
}
