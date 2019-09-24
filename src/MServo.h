#ifndef MServo_h
#define MServo_h

#include "Arduino.h"

class MServo {
  public:
    MServo::MServo(int pot, int dirA, int pwm);
    MServo::MServo(int pot, int dirA, int dirB, int pwm);
    int getPot();
    int movingAverage();
    void move(int val);
    void moveTypeOne(int val);
    void moveTypeTwo(int val);
    int getAngle();
    int getTarget();
    void resetTarget();
    void setAngleConstrain(int min, int max);
    void setPotConstrain(int min, int max);
    void setTolerance(int tolerance);
    void write(int target);
    void update();
    bool reverse = false;
  private:
    int _pot, _dirA, _dirB, _pwm;
    int _driverType = 1; // Number of pin for control the motor driver

    // Moving Average
    int _numRead = 10; // Default 10
    int _readings[10]; // Default 10
    int _total = 0;
    int _readIndex = 0;
    int _minPot = 0;
    int _maxPot = 1023;
    int _minAngle = 0;
    int _maxAngle = 360;
    int _target = 0;
    int _tolerance = 6;
    int _baseSpeed = 200;
};

#endif