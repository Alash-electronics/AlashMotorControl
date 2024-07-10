#ifndef AlashMotorControlX2_h
#define AlashMotorControlX2_h

#include "Arduino.h"
#include "AlashMotorControl.h"

typedef void (*CallBackFunction)();

class AlashMotorControlX2{
public:
   AlashMotorControlX2(
       uint8_t pinIN1_A,
       uint8_t pinIN2_A,
       uint8_t pinEnable_A,
       uint8_t pinIN1_B,
       uint8_t pinIN2_B,
       uint8_t pinEnable_B);
   AlashMotorControlX2(uint8_t pinIN1_A,
           uint8_t pinIN2_A,
           uint8_t pinIN1_B,
           uint8_t pinIN2_B);

   //MOTOR A
   void setSpeedA(unsigned short pwmVal_A);
   unsigned short getSpeedA();
   void forwardA();
   void forwardForA(unsigned long delay_A, CallBackFunction callback_A);
   void forwardForA(unsigned long delay_A);
   void backwardA();
   void backwardForA(unsigned long delay_A, CallBackFunction callback_A);
   void backwardForA(unsigned long delay_A);
   void runA(AlashMotorControl::Direction direction_A);
   void runForA(unsigned long delay_A, AlashMotorControl::Direction direction_A);
   void runForA(unsigned long delay_A, AlashMotorControl::Direction direction_A, CallBackFunction callback_A);
   void stopA();
   void resetA();
   boolean isMovingA();
   AlashMotorControl::Direction getDirectionA();

   //MOTOR B
   void setSpeedB(unsigned short pwmVal_B);
   unsigned short getSpeedB();
   void forwardB();
   void forwardForB(unsigned long delay_B, CallBackFunction callback_B);
   void forwardForB(unsigned long delay_B);
   void backwardB();
   void backwardForB(unsigned long delay_B, CallBackFunction callback_B);
   void backwardForB(unsigned long delay_B);
   void runB(AlashMotorControl::Direction direction_B);
   void runForB(unsigned long delay_B, AlashMotorControl::Direction direction_B);
   void runForB(unsigned long delay_B, AlashMotorControl::Direction direction_B, CallBackFunction callback_B);
   void stopB();
   void resetB();
   boolean isMovingB();
   AlashMotorControl::Direction getDirectionB();

   //BOTH
   void setSpeed(unsigned short pwmVal);
   void forward();
   void forwardFor(unsigned long delay, CallBackFunction callback);
   void forwardFor(unsigned long delay);
   void backward();
   void backwardFor(unsigned long delay, CallBackFunction callback);
   void backwardFor(unsigned long delay);
   void run(AlashMotorControl::Direction direction);
   void runFor(unsigned long delay, AlashMotorControl::Direction direction);
   void runFor(unsigned long delay, AlashMotorControl::Direction direction, CallBackFunction callback);
   void stop();
   void reset();

private:
   AlashMotorControl _motorA;
   AlashMotorControl _motorB;

   unsigned long _lastMs;
   boolean _canMove;

   static void fakeCallback();
};

#endif