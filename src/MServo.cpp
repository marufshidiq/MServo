#include "Arduino.h"
#include "MServo.h"

// Constructor
MServo::MServo(int pot, int dirA, int pwm) {
  _driverType = 1;
  _pot = pot;
  _dirA = dirA;
  _pwm = pwm;
  pinMode(_pot, INPUT);
  pinMode(_dirA, OUTPUT);
  pinMode(_pwm, OUTPUT);

  // Change all value to 0
  for (int thisReading = 0; thisReading < _numRead; thisReading++) {
    _readings[thisReading] = 0;
  }
}

MServo::MServo(int pot, int dirA, int dirB, int pwm) {
  _driverType = 2;
  _pot = pot;
  _dirA = dirA;
  _dirB = dirB;
  _pwm = pwm;
  pinMode(_pot, INPUT);
  pinMode(_dirA, OUTPUT);
  pinMode(_dirB, OUTPUT);
  pinMode(_pwm, OUTPUT);

  // Change all value to 0
  for (int thisReading = 0; thisReading < _numRead; thisReading++) {
    _readings[thisReading] = 0;
  }
}

int MServo::getPot() {
  return analogRead(_pot);
}

int MServo::movingAverage() {
  int result;
  _total -= _readings[_readIndex];
  _readings[_readIndex] = getPot();
  _total += _readings[_readIndex];
  _readIndex += 1;
  if (_readIndex >= _numRead) {
    _readIndex = 0;
  }
  result = _total / _numRead;
  return result;
}

void MServo::move(int val) {
  if(reverse){
    val *=-1;
  }
  if(_driverType == 1){
    moveTypeOne(val);
  }
  else if(_driverType == 2){
    moveTypeTwo(val);
  }
}

void MServo::moveTypeOne(int val){
  if (val >= 0) {
    digitalWrite(_dirA, 0);
    analogWrite(_pwm, val);
  } else if (val < 0) {
    digitalWrite(_dirA, 1);
    analogWrite(_pwm, 255 + val);
  }
}

void MServo::moveTypeTwo(int val){
  if (val >= 0) {
    digitalWrite(_dirA, 0);
    digitalWrite(_dirB, 1);
    analogWrite(_pwm, val);
  } else if (val < 0) {
    digitalWrite(_dirA, 1);
    digitalWrite(_dirB, 0);
    analogWrite(_pwm, 255 + val);
  }
}

int MServo::getAngle() {
  int angle = map(movingAverage(), _minPot, _maxPot, _minAngle, _maxAngle);
  return constrain(angle, _minAngle, _maxAngle);
}

int MServo::getTarget(){
  return _target;
}

void MServo::resetTarget(){
  _target = getAngle();
}

void MServo::setAngleConstrain(int min, int max) {
  _minAngle = min;
  _maxAngle = max;
}

void MServo::setPotConstrain(int min, int max) {
  _minPot = min;
  _maxPot = max;
}

void MServo::setTolerance(int tolerance) {
  if (tolerance < 0) {
    tolerance *= -1;
  }
  _tolerance = tolerance;
}

void MServo::write(int target) {
  _target = target;
}

void MServo::update() {
  int target = _target;
  int feedback = getAngle();
  int diff = feedback - target;
  int tolerance = _tolerance / 2;
  if ((diff < tolerance) && (diff > -tolerance)) {
    move(0);
  }
  else {
    if (diff > tolerance) {
      move(_baseSpeed);
    }
    else if (diff < -tolerance) {
      move(-1 * _baseSpeed);
    }
  }
}