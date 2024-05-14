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

int sum_rempli = 900;
int sum_vide = 300;
int sum_min = 50;

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

    bool if_all_pressed = value0 > 50 && value1 > 50 && value2 > 50;

    
    Serial.print(String(sum) + " " + String(state) + " " + String(attente) + " " + String(attente_max) + " " + String(if_all_pressed) + "\n");

    // match case
    switch (state)
    {
        case 0:
            if (sum > sum_vide && if_all_pressed && sum < sum_rempli)
            {
                state = 1;
                attente = 0;
            }
            break;
        case 1:
            attente++;
            if (attente > attente_max / 2 && sum < sum_rempli && if_all_pressed)
            {
                state = 2;
                attente = 0;
                tps_rempli = 0;
            }
            if (sum < sum_min || sum > sum_rempli || !if_all_pressed)
            {
                state = 3;
                attente = 0;
            }
            break;
        case 2:
            attente++;
            if ((attente > attente_max * 4) || sum < sum_min || tps_rempli > 10 || !if_all_pressed)
            {
                state = 3;
                attente = 0;
                tps_rempli = 0;
                break;
            }
            if (sum > sum_rempli)
            {
                tps_rempli++;
            }
            servo.write(180);
            break;
        case 3:
            servo.write(0);
            attente++;
            if (attente > attente_max / 2 && sum < sum_vide)
            {
                state = 0;
                attente = 0;
            }
            break;
    }

    
    delay(50);
}
