#ifndef AlashMotorControl_h
#define AlashMotorControl_h

#include "Arduino.h"

typedef void (*CallBackFunction)();

class AlashMotorControl{
public:
   typedef enum
   {
      FORWARD = 0,
      BACKWARD = 1,
      STOP = -1
   } Direction;

   AlashMotorControl(uint8_t pinIN1, uint8_t pinIN2, uint8_t pinEnable);
   AlashMotorControl(uint8_t pinIN1, uint8_t pinIN2);
   void setSpeed(int pwmVal);
   unsigned short getSpeed();
   void forward();
   void forwardFor(unsigned long delay, CallBackFunction callback);
   void forwardFor(unsigned long delay);
   void backward();
   void backwardFor(unsigned long delay, CallBackFunction callback);
   void backwardFor(unsigned long delay);
   void controlBySpeed(int pwmVal);
   void run(AlashMotorControl::Direction direction);
   void runFor(unsigned long delay, AlashMotorControl::Direction direction);
   void runFor(unsigned long delay, AlashMotorControl::Direction direction, CallBackFunction callback);
   void stop();
   void HardStop();
   void reset();
   boolean isMoving();
   Direction getDirection();

private:
   byte _pinEnable;
   byte _pinIN1;
   byte _pinIN2;
   int _pwmVal;
   unsigned long _lastMs;
   boolean _canMove;
   boolean _isMoving;
   AlashMotorControl::Direction _direction;
   static void fakeCallback();
};

#endif