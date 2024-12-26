#ifndef VIBRATION_H
#define VIBRATION_H

#include <Arduino.h>

void turnOnVibration(const int v_pin){
    digitalWrite(v_pin, HIGH);
}

void turnOffVibration(const int v_pin){
    digitalWrite(v_pin, LOW);
}

#endif