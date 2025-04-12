#include "AlashMotorControl.h"

// Define pin state for ESP32 compatibility if needed (optional, analogWrite usually works)
#if defined(ARDUINO_ARCH_ESP32)
// #include <analogWrite.h> // Include if using a specific ESP32 analogWrite library
#endif

typedef void (*CallBackFunction)();

// Constructor with Enable Pin (primarily for L298N)
AlashMotorControl::AlashMotorControl(uint8_t pinIN1, uint8_t pinIN2, uint8_t pinEnable, MotorDriverType driverType) {
  _pinIN1 = pinIN1;
  _pinIN2 = pinIN2;
  _pinEnable = pinEnable; // Store the enable pin
  _driverType = driverType;
  _pwmVal = 100; // Default speed
  _isMoving = false;
  _canMove = true;
  _lastMs = 0;
  _direction = STOP;

  pinMode(_pinIN1, OUTPUT);
  pinMode(_pinIN2, OUTPUT);
  if (_driverType == DRIVER_L298N && _pinEnable != -1) {
    pinMode(_pinEnable, OUTPUT);
    #if defined(ARDUINO_ARCH_ESP32)
      // Optional: Setup ESP32 LEDC if preferred over analogWrite for L298N EN pin
      // ledcSetup(some_channel, freq, resolution);
      // ledcAttachPin(_pinEnable, some_channel);
    #endif
  }
   // Ensure motor is stopped initially using the updated stop logic
   if (_driverType == DRIVER_TA6586) {
        analogWrite(_pinIN1, 0);
        analogWrite(_pinIN2, 0);
    } else {
        digitalWrite(_pinIN1, LOW);
        digitalWrite(_pinIN2, LOW);
        if (_pinEnable != -1) analogWrite(_pinEnable, 0);
    }
}

// Constructor without Enable Pin (for TA6586 or jumpered L298N)
AlashMotorControl::AlashMotorControl(uint8_t pinIN1, uint8_t pinIN2, MotorDriverType driverType) {
  _pinIN1 = pinIN1;
  _pinIN2 = pinIN2;
  _pinEnable = -1; // Mark enable pin as unused
  _driverType = driverType;
  _pwmVal = (_driverType == DRIVER_L298N) ? 255 : 255; // L298N no-EN is full speed, TA6586 default 255
  _isMoving = false;
  _canMove = true;
  _lastMs = 0;
  _direction = STOP;

  pinMode(_pinIN1, OUTPUT);
  pinMode(_pinIN2, OUTPUT);
  // No setup needed for _pinEnable

   // Ensure motor is stopped initially using the updated stop logic
   if (_driverType == DRIVER_TA6586) {
        analogWrite(_pinIN1, 0);
        analogWrite(_pinIN2, 0);
    } else {
        digitalWrite(_pinIN1, LOW);
        digitalWrite(_pinIN2, LOW);
    }
}

void AlashMotorControl::setSpeed(int pwmVal) {
    // Constrain pwmVal to 0-255 range
    if (pwmVal < 0) pwmVal = 0;
    if (pwmVal > 255) pwmVal = 255;
    _pwmVal = pwmVal;

    // If the motor is already moving with L298N and EN pin, update speed immediately
    if (_driverType == DRIVER_L298N && _pinEnable != -1 && _isMoving) {
        analogWrite(_pinEnable, _pwmVal);
    }
    // For TA6586, the speed is applied during forward/backward calls
    // If moving, update speed immediately for TA6586 as well
    else if (_driverType == DRIVER_TA6586 && _isMoving) {
        if (_direction == FORWARD) {
             analogWrite(_pinIN1, _pwmVal);
             analogWrite(_pinIN2, 0); // Ensure other pin is off
        } else if (_direction == BACKWARD) {
             analogWrite(_pinIN1, 0); // Ensure other pin is off
             analogWrite(_pinIN2, _pwmVal);
        }
    }
}


unsigned short AlashMotorControl::getSpeed() {
  return this->isMoving() ? _pwmVal : 0;
}

void AlashMotorControl::forward() {
  if (_driverType == DRIVER_L298N) {
      digitalWrite(_pinIN1, HIGH);
      digitalWrite(_pinIN2, LOW);
      if (_pinEnable != -1) { // Only write to EN if it's used
          analogWrite(_pinEnable, _pwmVal);
      }
  } else if (_driverType == DRIVER_TA6586) {
      // --- Correction for TA6586 Forward ---
      analogWrite(_pinIN2, 0); // Explicitly turn OFF IN2 (PWM = 0)
      analogWrite(_pinIN1, _pwmVal); // Apply PWM speed to IN1
  }
  _direction = FORWARD;
  _isMoving = true;
}

void AlashMotorControl::backward() {
   if (_driverType == DRIVER_L298N) {
      digitalWrite(_pinIN1, LOW);
      digitalWrite(_pinIN2, HIGH);
      if (_pinEnable != -1) { // Only write to EN if it's used
          analogWrite(_pinEnable, _pwmVal);
      }
  } else if (_driverType == DRIVER_TA6586) {
      // --- Correction for TA6586 Backward ---
      analogWrite(_pinIN1, 0); // Explicitly turn OFF IN1 (PWM = 0)
      analogWrite(_pinIN2, _pwmVal); // Apply PWM speed to IN2
  }
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
    default:
      this->stop();
      break;
  }
}

// --- Timed Operations and Callbacks ---

void AlashMotorControl::runFor(unsigned long delay,
                   AlashMotorControl::Direction direction,
                   CallBackFunction callback) {
  // Only start if not already in a timed move and allowed to move
  if ((_lastMs == 0) && _canMove) {
    _lastMs = millis(); // Record start time
    this->run(direction); // Start moving in the specified direction
  }

  // Check if the delay has passed and the move hasn't been stopped/reset
  // Use >= to ensure it triggers even if loop is slow
  if (_lastMs != 0 && ((millis() - _lastMs) >= delay) && _canMove) {
    this->stop();       // Stop the motor
    _lastMs = 0;        // Reset timer flag
    _canMove = false;   // Prevent restarting until reset() is called
    callback();         // Execute the callback function
  }
}

void AlashMotorControl::runFor(unsigned long delay, AlashMotorControl::Direction direction) {
  this->runFor(delay, direction, fakeCallback); // Call the version with a dummy callback
}

void AlashMotorControl::forwardFor(unsigned long delay, CallBackFunction callback) {
  this->runFor(delay, FORWARD, callback);
}

void AlashMotorControl::forwardFor(unsigned long delay) {
  this->runFor(delay, FORWARD, fakeCallback);
}

void AlashMotorControl::backwardFor(unsigned long delay, CallBackFunction callback) {
  this->runFor(delay, BACKWARD, callback);
}

void AlashMotorControl::backwardFor(unsigned long delay) {
  this->runFor(delay, BACKWARD, fakeCallback);
}

// --- Stop Methods ---

// Coast stop (motors can spin freely)
void AlashMotorControl::stop() {
  if (_driverType == DRIVER_L298N) {
      digitalWrite(_pinIN1, LOW);
      digitalWrite(_pinIN2, LOW);
      if (_pinEnable != -1) {
          // Set EN low for L298N stop is often clearer/safer
          analogWrite(_pinEnable, 0);
      }
  } else if (_driverType == DRIVER_TA6586) {
      // --- Correction for TA6586 Stop (Coast) ---
      analogWrite(_pinIN1, 0); // Explicitly turn OFF IN1 (PWM = 0)
      analogWrite(_pinIN2, 0); // Explicitly turn OFF IN2 (PWM = 0)
  }
  _direction = STOP;
  _isMoving = false;
}

// Brake stop (motors resist spinning)
void AlashMotorControl::HardStop() {
  if (_driverType == DRIVER_L298N) {
      digitalWrite(_pinIN1, HIGH);
      digitalWrite(_pinIN2, HIGH);
       if (_pinEnable != -1) {
          // Keep EN high for braking with IN pins high
          analogWrite(_pinEnable, 255); // Or max PWM value
       }
  } else if (_driverType == DRIVER_TA6586) {
      // --- Correction for TA6586 Stop (Brake) ---
      // Setting both inputs HIGH usually causes braking.
      // Using digitalWrite ensures a definite HIGH state.
      digitalWrite(_pinIN1, HIGH);
      digitalWrite(_pinIN2, HIGH);
  }
  _direction = STOP; // Still represents a stopped state
  _isMoving = false;
}

// --- Utility Methods ---

// Allows timed runs (runFor, etc.) to execute again
void AlashMotorControl::reset() {
  _canMove = true;
  _lastMs = 0; // Reset timer flag
}

boolean AlashMotorControl::isMoving() {
   // Check if the motor state indicates movement
   // Note: If a timed move just finished but stop() hasn't executed in the loop yet,
   // this might briefly return true. This check reflects the *intended* state.
   return _isMoving;
}


AlashMotorControl::Direction AlashMotorControl::getDirection() {
  return _direction;
}

MotorDriverType AlashMotorControl::getDriverType() {
    return _driverType;
}


void AlashMotorControl::fakeCallback() {
    // Does nothing. Used as default for timed methods.
}


void AlashMotorControl::controlBySpeed(int pwmVal){
  // Constrain input
  if(pwmVal>255)pwmVal=255;
  else if(pwmVal<-255)pwmVal=-255;

  if(pwmVal>0){
    this->setSpeed(pwmVal); // Set speed first
    this->forward();       // Then move
  }
  else if(pwmVal==0){
    this->stop(); // Coast stop at speed 0
    // this->HardStop(); // Alternative: brake at speed 0
  }
  else { // pwmVal < 0
    this->setSpeed(abs(pwmVal)); // Use absolute value for speed
    this->backward();           // Then move backward
  }
}