#ifndef LegoTrain_h
#define LegoTrain_h

#include "Arduino.h"


typedef void (*CallBackFunction) ();

class LegoTrain{
   public:
      typedef enum {
        STOPPED_FOR = -1,
        STOPPED     =  0,
        FORWARD     =  1,
        BACKWARD    =  2
      } State;

      LegoTrain(byte pinSpeed, byte pinForward, byte pinBackward);

      void changeSpeed(byte speed);
      unsigned short getSpeed();

      void forward(byte speed);
      void forwardFor(byte speed, unsigned long delay, CallBackFunction callback);
      void forwardFor(byte speed, unsigned long delay);
      
      void backward(byte speed);
      void backwardFor(byte speed, unsigned long delay, CallBackFunction callback);
      void backwardFor(byte speed, unsigned long delay);
      
      void stop();
 
      void reset();
      
      LegoTrain::State getState();
      boolean isMovingForward();
      boolean isMovingBackward();
      boolean isStopped();
      boolean canMove();
   private:
      LegoTrain::State _state;

      byte _pinSpeed;
      byte _pinForward;
      byte _pinBackward;

      byte _speed;
      
      unsigned long _lastMs;

      void move(byte speed, LegoTrain::State state);
      void moveFor(byte speed, unsigned long delay, CallBackFunction callback, LegoTrain::State state);
      static void fakeCallback();
};

#endif
