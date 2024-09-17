#include "encoder_driver.h"

// Variables used in ReadSpeed function
double _freqLeft;   // Frequency of the signal on the left speed pin
double _rpmLeft;    // Left wheel speed in revolutions per minute
double _mpsLeft;    // Left wheel speed in meters per second

double _freqRight;  // Frequency of the signal on the right speed pin
double _rpmRight;   // Right wheel speed in revolutions per minute
double _mpsRight;   // Right wheel speed in meters per second

// Initialize encoder pins
void initEncoders() {
    pinMode(PIN_SPEED_LEFT, INPUT);
    pinMode(PIN_SPEED_RIGHT, INPUT);
}

// Read the speed from the input pin and calculate RPM and m/s
void ReadSpeed() {
    static bool lastStateLeft = false;  
    static unsigned long last_uS_Left = 0;    
    static unsigned long timeout_uS_Left = 0;  

    static bool lastStateRight = false;  
    static unsigned long last_uS_Right = 0;    
    static unsigned long timeout_uS_Right = 0;  

    bool stateLeft = digitalRead(PIN_SPEED_LEFT);
    bool stateRight = digitalRead(PIN_SPEED_RIGHT);

    if (stateLeft != lastStateLeft) {
        unsigned long current_uS = micros();
        unsigned long elapsed_uS = current_uS - last_uS_Left;

        double period_uS = elapsed_uS * 2.0;
        _freqLeft = (1 / period_uS) * 1E6;
        _rpmLeft = _freqLeft / 45 * 60;
        if (_rpmLeft > 5000) _rpmLeft = 0;
        _mpsLeft = (WHEEL_CIRCUMFERENCE_CM / 100) * _rpmLeft / 60 / 60; 

        last_uS_Left = current_uS;
        timeout_uS_Left = last_uS_Left + SPEED_TIMEOUT;
        lastStateLeft = stateLeft;
    } else if (micros() > timeout_uS_Left) {
        _freqLeft = 0;
        _rpmLeft = 0;
        _mpsLeft = 0;
        last_uS_Left = micros();
    }

    if (stateRight != lastStateRight) {
        unsigned long current_uS = micros();
        unsigned long elapsed_uS = current_uS - last_uS_Right;

        double period_uS = elapsed_uS * 2.0;
        _freqRight = (1 / period_uS) * 1E6;
        _rpmRight = _freqRight / 45 * 60;
        if (_rpmRight > 5000) _rpmRight = 0;
        _mpsRight = (WHEEL_CIRCUMFERENCE_CM / 100) * _rpmRight / 60 / 60; 

        last_uS_Right = current_uS;
        timeout_uS_Right = last_uS_Right + SPEED_TIMEOUT;
        lastStateRight = stateRight;
    } else if (micros() > timeout_uS_Right) {
        _freqRight = 0;
        _rpmRight = 0;
        _mpsRight = 0;
        last_uS_Right = micros();
    }
}

// Wrap the encoder reading function for ROSBridge
long readEncoder(int i) {
    ReadSpeed(); // Update speed values

    if (i == LEFT) return _mpsLeft;
    else return _mpsRight;
}

// Reset encoder readings
void resetEncoders() {
    _mpsLeft = 0;
    _mpsRight = 0;
}
