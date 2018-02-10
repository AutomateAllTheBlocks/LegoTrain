#include "LegoTrain.h"

typedef void (*CallBackFunction) ();

LegoTrain::LegoTrain(byte pinSpeed, byte pinForward, byte pinBackward) {
  _pinSpeed =    pinSpeed;
  _pinForward =  pinForward;
  _pinBackward = pinBackward;

  pinMode(_pinSpeed,    OUTPUT);
  pinMode(_pinForward,  OUTPUT);
  pinMode(_pinBackward, OUTPUT);

  stop();

  _lastMs = 0;
}


void LegoTrain::changeSpeed(byte speed) {
  if (speed != _speed) {
    _speed = speed;
    analogWrite(_pinSpeed, _speed);
  }
}

unsigned short LegoTrain::getSpeed() {
  return _speed;
}

void LegoTrain::move(byte speed, LegoTrain::State state) {
  if (_state != state) {
    this->stop();

    byte pinForwardValue = LOW;
    if (state == LegoTrain::State::FORWARD) {
      pinForwardValue = HIGH;
    }

    byte pinBackwardValue = LOW;
    if (state == LegoTrain::State::BACKWARD) {
      pinBackwardValue = HIGH;
    }

    digitalWrite(_pinForward,  pinForwardValue);
    digitalWrite(_pinBackward, pinBackwardValue);

    _state = state;
  }

  this->changeSpeed(speed);
}

void LegoTrain::moveFor(byte speed, unsigned long delay, CallBackFunction callback, LegoTrain::State state) {
  if ((_lastMs == 0) && canMove()) {
    _lastMs = millis();
    this->move(speed, state);
  }

  if (((millis() - _lastMs) > delay) && canMove()) {
    this->stop();
    _lastMs = 0;
    _state = STOPPED_FOR;

    callback();
  }
}

void LegoTrain::forward(byte speed){
  this->move(speed, LegoTrain::State::FORWARD);
}

void LegoTrain::forwardFor(byte speed, unsigned long delay, CallBackFunction callback) {
  this->moveFor(speed, delay, callback, LegoTrain::State::FORWARD);
}

void LegoTrain::forwardFor(byte speed, unsigned long delay) {
  this->forwardFor(speed, delay, fakeCallback);
}


void LegoTrain::backward(byte speed) {
  this->move(speed, LegoTrain::State::BACKWARD);
}

void LegoTrain::backwardFor(byte speed, unsigned long delay, CallBackFunction callback) {
  this->moveFor(speed, delay, callback, LegoTrain::State::BACKWARD);
}

void LegoTrain::backwardFor(byte speed, unsigned long delay) {
  this->backwardFor(speed, delay, fakeCallback);
}


void LegoTrain::stop() {
  digitalWrite(_pinForward, LOW);
  digitalWrite(_pinBackward, LOW);

  this->changeSpeed(LOW);

  _state = LegoTrain::State::STOPPED;
}

void LegoTrain::reset() {
  if (_state == STOPPED_FOR) {
    this->stop();
  }
}

LegoTrain::State LegoTrain::getState() {
  return _state;
}

boolean LegoTrain::isMovingForward() {
  return _state == LegoTrain::State::FORWARD;
}

boolean LegoTrain::isMovingBackward() {
  return _state == LegoTrain::State::BACKWARD;
}

boolean LegoTrain::isStopped() {
  return _state == LegoTrain::State::STOPPED || _state == LegoTrain::State::STOPPED_FOR;
}

boolean LegoTrain::canMove() {
  return _state != LegoTrain::State::STOPPED_FOR;
}

void LegoTrain::fakeCallback() {

}
