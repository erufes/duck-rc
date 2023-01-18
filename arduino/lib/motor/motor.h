#include <Arduino.h>

// TODO: TEST THIS
#define FORWARD 0
#define BACKWARD 1
#define BRAKE 2
#define COAST 3

#define LEFT 0
#define RIGHT 1

class Motor {
  uint8_t directionA;
  uint8_t directionB;
  uint8_t power; // probably unused for now

  uint8_t direction;
  uint8_t side;

  uint16_t curSpeed;

  void updateDirectionPins();

public:
  Motor(uint8_t directionA, uint8_t directionB, uint8_t power);

  // sets the motor speed.  The sign of 'speed' determines the direction
  // and the magnitude determines the speed.  limits: -128 <= speed < 128
  // |speed| = 128 produces the maximum speed while speed = 0 is full brake.
  void setSpeed(int16_t speed);

  void coast();
  void brake();
  void forward();
  void backward();

  uint16_t getSpeed() { return this->curSpeed; };

  void tick();
};
