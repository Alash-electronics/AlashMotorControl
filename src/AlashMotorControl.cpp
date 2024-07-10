/*
  AlashMotorControl.cpp - Libreria per gestire i movimenti di un motore DC con il modulo
  AlashMotorControl Autore:   Alash engineer Sito web: http://www.lombardoandrea.com
*/

#include "AlashMotorControl.h"

typedef void (*CallBackFunction)();

AlashMotorControl::AlashMotorControl(uint8_t pinIN1, uint8_t pinIN2, uint8_t pinEnable) {
  _pinIN1 = pinIN1;
  _pinIN2 = pinIN2;
  _pinEnable = pinEnable;
  _pwmVal = 100;
  _isMoving = false;
  _canMove = true;
  _lastMs = 0;
  _direction = STOP;

  pinMode(_pinEnable, OUTPUT);
  pinMode(_pinIN1, OUTPUT);
  pinMode(_pinIN2, OUTPUT);
}

AlashMotorControl::AlashMotorControl(uint8_t pinIN1, uint8_t pinIN2) {
  _pinEnable = -1;
  _pinIN1 = pinIN1;
  _pinIN2 = pinIN2;
  _pwmVal = 255;  // It's always at the max speed due to jumper on module
  _isMoving = false;
  _canMove = true;
  _lastMs = 0;
  _direction = STOP;

  pinMode(_pinIN1, OUTPUT);
  pinMode(_pinIN2, OUTPUT);
}

void AlashMotorControl::setSpeed(int pwmVal) {
  _pwmVal = pwmVal;
}

unsigned short AlashMotorControl::getSpeed() {
  return this->isMoving() ? _pwmVal : 0;
}

void AlashMotorControl::forward() {
  digitalWrite(_pinIN1, HIGH);
  digitalWrite(_pinIN2, LOW);

  analogWrite(_pinEnable, _pwmVal);

  _direction = FORWARD;
  _isMoving = true;
}

void AlashMotorControl::backward() {
  digitalWrite(_pinIN1, LOW);
  digitalWrite(_pinIN2, HIGH);

  analogWrite(_pinEnable, _pwmVal);

  _direction = BACKWARD;
  _isMoving = true;
}

void AlashMotorControl::run(AlashMotorControl::Direction direction) {
  switch (direction) {
    case BACKWARD:
      this->backward();
      break;
    case FORWARD:
      this->forward();
      break;
    case STOP:
      this->stop();
      break;
  }
}

// Timing and callback

void AlashMotorControl::runFor(unsigned long delay,
                   AlashMotorControl::Direction direction,
                   CallBackFunction callback) {
  if ((_lastMs == 0) && _canMove) {
    _lastMs = millis();

    switch (direction) {
      case FORWARD:
        this->forward();
        break;
      case BACKWARD:
        this->backward();
        break;
      case STOP:
      default:
        this->stop();
        break;
    }
  }

  if (((millis() - _lastMs) > delay) && _canMove) {
    this->stop();
    _lastMs = 0;
    _canMove = false;

    callback();
  }
}

void AlashMotorControl::runFor(unsigned long delay, AlashMotorControl::Direction direction) {
  this->runFor(delay, direction, fakeCallback);
}

void AlashMotorControl::forwardFor(unsigned long delay, CallBackFunction callback) {
  this->runFor(delay, FORWARD, callback);
}

void AlashMotorControl::forwardFor(unsigned long delay) {
  this->runFor(delay, FORWARD);
}

void AlashMotorControl::backwardFor(unsigned long delay, CallBackFunction callback) {
  this->runFor(delay, BACKWARD, callback);
}

void AlashMotorControl::backwardFor(unsigned long delay) {
  this->runFor(delay, BACKWARD);
}

void AlashMotorControl::controlBySpeed(int pwmVal){
  if(pwmVal>255)pwmVal=255;
  else if(pwmVal<-255)pwmVal=-255;
  else if(pwmVal>0){
    this->setSpeed(pwmVal);
    this->forward();
  }
  else if(pwmVal==0){
    this->HardStop();
  }

  else if(pwmVal<0) {
    this->setSpeed(0-pwmVal);
    this->backward();
  }
}

void AlashMotorControl::stop() {
  digitalWrite(_pinIN1, LOW);
  digitalWrite(_pinIN2, LOW);

  analogWrite(_pinEnable, 255);

  _direction = STOP;
  _isMoving = false;
}

void AlashMotorControl::HardStop() {
  digitalWrite(_pinIN1, HIGH);
  digitalWrite(_pinIN2, HIGH);

  analogWrite(_pinEnable, 255);

  _direction = STOP;
  _isMoving = false;
}


void AlashMotorControl::reset() {
  _canMove = true;
}

boolean AlashMotorControl::isMoving() {
  return _isMoving;
}

AlashMotorControl::Direction AlashMotorControl::getDirection() {
  return _direction;
}

void AlashMotorControl::fakeCallback() {}