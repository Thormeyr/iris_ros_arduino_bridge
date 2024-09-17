#ifndef ENCODER_DRIVER_H
#define ENCODER_DRIVER_H

// Include necessary libraries or headers
#include <Arduino.h>

// Constants for encoder configuration
const unsigned long SPEED_TIMEOUT = 500000;   // Time used to determine wheel is not spinning
const unsigned int UPDATE_TIME = 500;         // Time used to output serial data
const double WHEEL_DIAMETER_CM = 16.5;           // Motor wheel diameter (centimeters)
const double WHEEL_CIRCUMFERENCE_CM = 56.5;      // Motor wheel circumference (centimeters)

// Pin Declarations
const int PIN_SPEED_LEFT = 12;  // Change to the actual pin number
const int PIN_SPEED_RIGHT = 13; // Change to the actual pin number

// Function declarations
void initEncoders();
void resetEncoders();
long readEncoder(int i);

#endif
