#include "AlashMotorControlX2.h"
#include "AlashMotorControl.h" // Already included via AlashMotorControlX2.h but good practice
#include "AlashMotorDriverType.h" // Include the enum

#define DEBUG 0 // Keep debug flag if needed

typedef void (*CallBackFunction)();

// Constructor with Enable Pins
AlashMotorControlX2::AlashMotorControlX2(
                 uint8_t pinIN1_A, uint8_t pinIN2_A, uint8_t pinEnable_A,
                 uint8_t pinIN1_B, uint8_t pinIN2_B, uint8_t pinEnable_B,
                 MotorDriverType driverTypeA, MotorDriverType driverTypeB) :
    // Initialize _motorA and _motorB using the updated AlashMotorControl constructor
    _motorA(pinIN1_A, pinIN2_A, pinEnable_A, driverTypeA),
    _motorB(pinIN1_B, pinIN2_B, pinEnable_B, driverTypeB)
{
  _canMove = true; // For combined timed moves
  _lastMs = 0;
}

// Constructor without Enable Pins
AlashMotorControlX2::AlashMotorControlX2(
                 uint8_t pinIN1_A, uint8_t pinIN2_A,
                 uint8_t pinIN1_B, uint8_t pinIN2_B,
                 MotorDriverType driverTypeA, MotorDriverType driverTypeB) :
    // Initialize _motorA and _motorB using the updated AlashMotorControl constructor
    // Pass -1 for enable pins implicitly when calling the correct AlashMotorControl constructor
    _motorA(pinIN1_A, pinIN2_A, driverTypeA),
    _motorB(pinIN1_B, pinIN2_B, driverTypeB)
{
  _canMove = true; // For combined timed moves
  _lastMs = 0;
}


void trace(String msg) {
  if (DEBUG) {
    Serial.println(msg);
  }
}

// --- Methods for Motor A ---
void AlashMotorControlX2::setSpeedA(unsigned short pwmVal) { _motorA.setSpeed(pwmVal); }
unsigned short AlashMotorControlX2::getSpeedA() { return _motorA.getSpeed(); }
void AlashMotorControlX2::forwardA() { _motorA.forward(); }
void AlashMotorControlX2::backwardA() { _motorA.backward(); }
void AlashMotorControlX2::runA(AlashMotorControl::Direction direction) { _motorA.run(direction); }
void AlashMotorControlX2::runForA(unsigned long delay, AlashMotorControl::Direction direction) { _motorA.runFor(delay, direction); }
void AlashMotorControlX2::runForA(unsigned long delay, AlashMotorControl::Direction direction, CallBackFunction callback) { _motorA.runFor(delay, direction, callback); }
void AlashMotorControlX2::forwardForA(unsigned long delay, CallBackFunction callback) { _motorA.forwardFor(delay, callback); }
void AlashMotorControlX2::forwardForA(unsigned long delay) { _motorA.forwardFor(delay); }
void AlashMotorControlX2::backwardForA(unsigned long delay, CallBackFunction callback) { _motorA.backwardFor(delay, callback); }
void AlashMotorControlX2::backwardForA(unsigned long delay) { _motorA.backwardFor(delay); }
void AlashMotorControlX2::stopA() { _motorA.stop(); }
void AlashMotorControlX2::HardStopA() { _motorA.HardStop(); } // Added HardStop
void AlashMotorControlX2::resetA() { _motorA.reset(); }
boolean AlashMotorControlX2::isMovingA() { return _motorA.isMoving(); }
AlashMotorControl::Direction AlashMotorControlX2::getDirectionA() { return _motorA.getDirection(); }
MotorDriverType AlashMotorControlX2::getDriverTypeA() { return _motorA.getDriverType(); } // Added getter

// --- Methods for Motor B ---
void AlashMotorControlX2::setSpeedB(unsigned short pwmVal) { _motorB.setSpeed(pwmVal); }
unsigned short AlashMotorControlX2::getSpeedB() { return _motorB.getSpeed(); }
void AlashMotorControlX2::forwardB() { _motorB.forward(); }
void AlashMotorControlX2::backwardB() { _motorB.backward(); }
void AlashMotorControlX2::runB(AlashMotorControl::Direction direction) { _motorB.run(direction); }
void AlashMotorControlX2::runForB(unsigned long delay, AlashMotorControl::Direction direction) { _motorB.runFor(delay, direction); }
void AlashMotorControlX2::runForB(unsigned long delay, AlashMotorControl::Direction direction, CallBackFunction callback) { _motorB.runFor(delay, direction, callback); }
void AlashMotorControlX2::forwardForB(unsigned long delay, CallBackFunction callback) { _motorB.forwardFor(delay, callback); }
void AlashMotorControlX2::forwardForB(unsigned long delay) { _motorB.forwardFor(delay); }
void AlashMotorControlX2::backwardForB(unsigned long delay, CallBackFunction callback) { _motorB.backwardFor(delay, callback); }
void AlashMotorControlX2::backwardForB(unsigned long delay) { _motorB.backwardFor(delay); }
void AlashMotorControlX2::stopB() { _motorB.stop(); }
void AlashMotorControlX2::HardStopB() { _motorB.HardStop(); } // Added HardStop
void AlashMotorControlX2::resetB() { _motorB.reset(); }
boolean AlashMotorControlX2::isMovingB() { return _motorB.isMoving(); }
AlashMotorControl::Direction AlashMotorControlX2::getDirectionB() { return _motorB.getDirection(); }
MotorDriverType AlashMotorControlX2::getDriverTypeB() { return _motorB.getDriverType(); } // Added getter

// --- Methods for Both Motors ---
void AlashMotorControlX2::setSpeed(unsigned short pwmVal) {
  _motorA.setSpeed(pwmVal);
  _motorB.setSpeed(pwmVal);
}

void AlashMotorControlX2::forward() {
  _motorA.forward();
  _motorB.forward();
}

void AlashMotorControlX2::backward() {
  _motorA.backward();
  _motorB.backward();
}

void AlashMotorControlX2::run(AlashMotorControl::Direction direction) {
  _motorA.run(direction);
  _motorB.run(direction);
}

// Combined Timing and callback (Simplified: starts both, stops both when time elapses)
// Note: This uses the *internal* _lastMs and _canMove of AlashMotorControlX2
void AlashMotorControlX2::runFor(unsigned long delay, AlashMotorControl::Direction direction, CallBackFunction callback) {
  if ((_lastMs == 0) && _canMove) {
    _lastMs = millis();
    this->run(direction); // Start both motors
  }

  if (_lastMs != 0 && ((millis() - _lastMs) >= delay) && _canMove) {
    this->stop();     // Stop both motors
    _lastMs = 0;
    _canMove = false; // Prevent restarting until reset() is called
    callback();       // Call the callback
  }
}

void AlashMotorControlX2::runFor(unsigned long delay, AlashMotorControl::Direction direction) {
  this->runFor(delay, direction, fakeCallback);
}

void AlashMotorControlX2::forwardFor(unsigned long delay, CallBackFunction callback) {
  this->runFor(delay, AlashMotorControl::FORWARD, callback);
}

void AlashMotorControlX2::forwardFor(unsigned long delay) {
  this->runFor(delay, AlashMotorControl::FORWARD, fakeCallback);
}

void AlashMotorControlX2::backwardFor(unsigned long delay, CallBackFunction callback) {
  this->runFor(delay, AlashMotorControl::BACKWARD, callback);
}

void AlashMotorControlX2::backwardFor(unsigned long delay) {
  this->runFor(delay, AlashMotorControl::BACKWARD, fakeCallback);
}

void AlashMotorControlX2::stop() {
  _motorA.stop();
  _motorB.stop();
}

void AlashMotorControlX2::HardStop() { // Added HardStop
    _motorA.HardStop();
    _motorB.HardStop();
}


void AlashMotorControlX2::reset() {
  _canMove = true;  // Allow combined timed moves again
   _lastMs = 0;
  _motorA.reset(); // Reset individual motor states too
  _motorB.reset();
}

void AlashMotorControlX2::fakeCallback() {
    // Does nothing. Used as default for timed methods.
}