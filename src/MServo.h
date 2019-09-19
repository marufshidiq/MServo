#ifndef MServo_h
#define MServo_h

#include "Arduino.h"

class MServo {
  public:
    MServo();
    void attach(int pot, int dir, int pwm);
    int getPot();
    int movingAverage();
    void move(int val);
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
    int _pot, _dir, _pwm;

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