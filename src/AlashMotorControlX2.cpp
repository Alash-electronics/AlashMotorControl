/*
  AlashMotorControl.cpp - Libreria per gestire i movimenti di un motore DC con il modulo AlashMotorControl
  Autore:   Andrea Lombardo
  Sito web: http://www.lombardoandrea.com  
*/

#include "AlashMotorControlX2.h"
#include "AlashMotorControl.h"

#define DEBUG 0

typedef void (*CallBackFunction)();

AlashMotorControlX2::AlashMotorControlX2(
                 uint8_t pinIN1_A,
                 uint8_t pinIN2_A,
                 uint8_t pinEnable_A,
                 uint8_t pinIN1_B,
                 uint8_t pinIN2_B,
                 uint8_t pinEnable_B) : _motorA(
                                             pinIN1_A,
                                             pinIN2_A,
                                             pinEnable_A),
                                     _motorB(
                                             pinIN1_B,
                                             pinIN2_B,
                                             pinEnable_B)
{
  _canMove = true;
  _lastMs = 0;
}

AlashMotorControlX2::AlashMotorControlX2(uint8_t pinIN1_A,
                 uint8_t pinIN2_A,
                 uint8_t pinIN1_B,
                 uint8_t pinIN2_B) : _motorA(pinIN1_A,
                                             pinIN2_A),
                                     _motorB(
                                         pinIN1_B,
                                         pinIN2_B)
{
  _canMove = true;
  _lastMs = 0;
}

void trace(String msg)
{
  if (DEBUG)
  {
    Serial.println(msg);
  }
}

//Motor A
void AlashMotorControlX2::setSpeedA(unsigned short pwmVal)
{
  _motorA.setSpeed(pwmVal);
}

unsigned short AlashMotorControlX2::getSpeedA()
{
  return _motorA.isMoving() ? _motorA.getSpeed() : 0;
}

void AlashMotorControlX2::forwardA()
{
  _motorA.forward();
}

void AlashMotorControlX2::backwardA()
{
  _motorA.backward();
}

void AlashMotorControlX2::runA(AlashMotorControl::Direction direction)
{
  _motorA.run(direction);
}

void AlashMotorControlX2::runForA(unsigned long delay_A, AlashMotorControl::Direction direction_A)
{
  trace("runForA(d, d)");
  _motorA.runFor(delay_A, direction_A);
}

void AlashMotorControlX2::runForA(unsigned long delay_A, AlashMotorControl::Direction direction_A, CallBackFunction callback_A)
{
  trace("runForA(d, d, c)");
  _motorA.runFor(delay_A, direction_A, callback_A);
}

void AlashMotorControlX2::forwardForA(unsigned long delay, CallBackFunction callback)
{
  this->runForA(delay, AlashMotorControl::FORWARD, callback);
}

void AlashMotorControlX2::forwardForA(unsigned long delay)
{
  this->runForA(delay, AlashMotorControl::FORWARD);
}

void AlashMotorControlX2::backwardForA(unsigned long delay, CallBackFunction callback)
{
  this->runForA(delay, AlashMotorControl::BACKWARD, callback);
}

void AlashMotorControlX2::backwardForA(unsigned long delay)
{
  this->runForA(delay, AlashMotorControl::BACKWARD);
}

void AlashMotorControlX2::stopA()
{
  _motorA.stop();
}

void AlashMotorControlX2::resetA()
{
  _motorA.reset();
}

boolean AlashMotorControlX2::isMovingA()
{
  return _motorA.isMoving();
}

AlashMotorControl::Direction AlashMotorControlX2::getDirectionA()
{
  return _motorA.getDirection();
}

//Motor B
void AlashMotorControlX2::setSpeedB(unsigned short pwmVal)
{
  _motorB.setSpeed(pwmVal);
}

unsigned short AlashMotorControlX2::getSpeedB()
{
  return _motorB.isMoving() ? _motorB.getSpeed() : 0;
}

void AlashMotorControlX2::forwardB()
{
  _motorB.forward();
}
void AlashMotorControlX2::backwardB()
{
  _motorB.backward();
}

void AlashMotorControlX2::runB(AlashMotorControl::Direction direction)
{
  _motorB.run(direction);
}

void AlashMotorControlX2::runForB(unsigned long delay_B, AlashMotorControl::Direction direction_B)
{
  _motorB.runFor(delay_B, direction_B);
}
void AlashMotorControlX2::runForB(unsigned long delay_B, AlashMotorControl::Direction direction_B, CallBackFunction callback_B)
{
  _motorB.runFor(delay_B, direction_B, callback_B);
}

void AlashMotorControlX2::forwardForB(unsigned long delay, CallBackFunction callback)
{
  this->runForB(delay, AlashMotorControl::FORWARD, callback);
}

void AlashMotorControlX2::forwardForB(unsigned long delay)
{
  this->runForB(delay, AlashMotorControl::FORWARD);
}

void AlashMotorControlX2::backwardForB(unsigned long delay, CallBackFunction callback)
{
  this->runForB(delay, AlashMotorControl::BACKWARD, callback);
}

void AlashMotorControlX2::backwardForB(unsigned long delay)
{
  this->runForB(delay, AlashMotorControl::BACKWARD);
}

void AlashMotorControlX2::stopB()
{
  _motorB.stop();
}

void AlashMotorControlX2::resetB()
{
  _motorB.reset();
}

boolean AlashMotorControlX2::isMovingB()
{
  return _motorB.isMoving();
}

AlashMotorControl::Direction AlashMotorControlX2::getDirectionB()
{
  return _motorB.getDirection();
}

// Both
void AlashMotorControlX2::setSpeed(unsigned short pwmVal)
{
  _motorA.setSpeed(pwmVal);
  _motorB.setSpeed(pwmVal);
}

void AlashMotorControlX2::forward()
{
  _motorA.forward();
  _motorB.forward();
}

void AlashMotorControlX2::backward()
{
  _motorA.backward();
  _motorB.backward();
}

void AlashMotorControlX2::run(AlashMotorControl::Direction direction)
{
  _motorA.run(direction);
  _motorB.run(direction);
}

//Timing and callback
void AlashMotorControlX2::runFor(unsigned long delay, AlashMotorControl::Direction direction, CallBackFunction callback)
{

  if ((_lastMs == 0) && _canMove)
  {
    _lastMs = millis();
    switch (direction)
    {
    case AlashMotorControl::FORWARD:
      this->forward();
      break;
    case AlashMotorControl::BACKWARD:
      this->backward();
      break;
    case AlashMotorControl::STOP:
    default:
      this->stop();
      break;
    }
  }

  if (((millis() - _lastMs) > delay) && _canMove)
  {
    this->stop();
    _lastMs = 0;
    _canMove = false;

    callback();
  }
}

void AlashMotorControlX2::runFor(unsigned long delay, AlashMotorControl::Direction direction)
{
  this->runFor(delay, direction, fakeCallback);
}

void AlashMotorControlX2::forwardFor(unsigned long delay, CallBackFunction callback)
{
  this->runFor(delay, AlashMotorControl::FORWARD, callback);
}

void AlashMotorControlX2::forwardFor(unsigned long delay)
{
  this->runFor(delay, AlashMotorControl::FORWARD);
}

void AlashMotorControlX2::backwardFor(unsigned long delay, CallBackFunction callback)
{
  this->runFor(delay, AlashMotorControl::BACKWARD, callback);
}

void AlashMotorControlX2::backwardFor(unsigned long delay)
{
  this->runFor(delay, AlashMotorControl::BACKWARD);
}

void AlashMotorControlX2::stop()
{
  _motorA.stop();
  _motorB.stop();
}

void AlashMotorControlX2::reset()
{
  _canMove = true;
  _motorA.reset();
  _motorB.reset();
}

void AlashMotorControlX2::fakeCallback()
{
}