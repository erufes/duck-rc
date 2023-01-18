#include "./motor.h"

void handleSpeedOverflow(int &speed);
void setDirectionFromSpeed(int &speed, uint8_t &direction);

Motor::Motor(uint8_t directionA, uint8_t directionB, uint8_t power)
    : directionA(directionA), directionB(directionB), power(power) {
  pinMode(this->directionA, OUTPUT);
  pinMode(this->directionB, OUTPUT);
  pinMode(this->power, OUTPUT);

  digitalWrite(this->directionA, LOW);
  digitalWrite(this->directionB, LOW);
  digitalWrite(this->power, LOW);

  this->curSpeed = 0;
  this->direction = FORWARD;
}

void Motor::tick() { analogWrite(this->power, this->curSpeed); }

void Motor::updateDirectionPins() {
  switch (direction) {
  case FORWARD:
    digitalWrite(this->directionA, HIGH);
    digitalWrite(this->directionB, LOW);
    break;
  case BACKWARD:
    digitalWrite(this->directionA, LOW);
    digitalWrite(this->directionB, HIGH);
    break;
  case BRAKE:
    digitalWrite(this->directionA, HIGH);
    digitalWrite(this->directionB, HIGH);
    break;
  case COAST:
    digitalWrite(this->directionA, LOW);
    digitalWrite(this->directionB, LOW);
    break;
  }
}

void handleSpeedOverflow(int16_t &speed) {
  if (speed >= 127) {
    printf("[Motor] [Warning] Exceeded max speed.\n");
    speed = 127;
  } else if (speed < -128) {
    printf("[Motor] [Warning] Exceeded min speed.\n");
    speed = -128;
  }
}

void setDirectionFromSpeed(int8_t &speed, uint8_t &direction) {
  if (speed > 0) {
    direction = FORWARD;
  } else if (speed < 0) {
    direction = BACKWARD;
  } else {
    direction = BRAKE;
  }
}

void Motor::setSpeed(int16_t speed) {
  handleSpeedOverflow(speed);

  int8_t finalSpeed = speed;

  setDirectionFromSpeed(finalSpeed, this->direction);

  this->curSpeed = finalSpeed;

  updateDirectionPins();
}