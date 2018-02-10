#include "LegoTrain.h"

const unsigned short LT_ENA = 11;
const unsigned short LT_FWD = 12;
const unsigned short LT_BKD = 13;

LegoTrain train(LT_ENA, LT_FWD, LT_BKD);

const byte trainSpeed = 80;
const long directionDelay = 1000;

void setup() {
  Serial.begin(9600);

  changeToForward();
}

void loop() {
  switch (train.getState()) {
    case LegoTrain::State::FORWARD:
      Serial.println("Moving forwards...");
      train.forwardFor(trainSpeed, directionDelay, changeToBackward);
      break;
    case LegoTrain::State::BACKWARD:
      Serial.println("Moving backwards...");
      train.backwardFor(trainSpeed, directionDelay, changeToForward);
      break;
  }

  delay(100);
}

void changeToBackward() {
  train.reset();
  train.backward(trainSpeed);
}

void changeToForward() {
  train.reset();
  train.forward(trainSpeed);
}


