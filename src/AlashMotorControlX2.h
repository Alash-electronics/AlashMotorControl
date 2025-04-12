#ifndef AlashMotorControlX2_h
#define AlashMotorControlX2_h

#include "Arduino.h"
#include "AlashMotorControl.h"
#include "AlashMotorDriverType.h" // Include the driver type enum

typedef void (*CallBackFunction)();

class AlashMotorControlX2{
public:
   // Constructor with Enable pins (L298N style)
   AlashMotorControlX2(
       uint8_t pinIN1_A, uint8_t pinIN2_A, uint8_t pinEnable_A,
       uint8_t pinIN1_B, uint8_t pinIN2_B, uint8_t pinEnable_B,
       MotorDriverType driverTypeA = DRIVER_L298N, // Default to L298N for A
       MotorDriverType driverTypeB = DRIVER_L298N  // Default to L298N for B
   );

   // Constructor without Enable pins (TA6586 style or jumpered L298N)
   AlashMotorControlX2(
       uint8_t pinIN1_A, uint8_t pinIN2_A,
       uint8_t pinIN1_B, uint8_t pinIN2_B,
       MotorDriverType driverTypeA = DRIVER_L298N, // Default to L298N for A
       MotorDriverType driverTypeB = DRIVER_L298N  // Default to L298N for B
   );

   // --- Methods remain the same, operating on _motorA and _motorB ---

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
   void HardStopA(); // Added HardStop for consistency
   void resetA();
   boolean isMovingA();
   AlashMotorControl::Direction getDirectionA();
   MotorDriverType getDriverTypeA(); // Added getter for driver type

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
    void HardStopB(); // Added HardStop for consistency
   void resetB();
   boolean isMovingB();
   AlashMotorControl::Direction getDirectionB();
   MotorDriverType getDriverTypeB(); // Added getter for driver type

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
   void HardStop(); // Added HardStop for consistency
   void reset();

private:
   AlashMotorControl _motorA; // Instance of the base class for Motor A
   AlashMotorControl _motorB; // Instance of the base class for Motor B

   // State variables for combined timed moves
   unsigned long _lastMs;
   boolean _canMove;

   // Internal helper
   static void fakeCallback();
};

#endif // AlashMotorControlX2_h