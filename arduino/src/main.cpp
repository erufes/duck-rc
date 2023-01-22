#include <Arduino.h>
// #include <ArduinoJson.h>
// #include "../ArduinoJson/src/ArduinoJson.h"
#include "ArduinoJson.h"
#include <motor.h>

#define ACCEL_AXIS "y"
#define DIR_AXIS "x"

Motor *mLeft, *mRight;

float lerp(float a, float b, float f) { return a * (1.0 - f) + (b * f); }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.write("OK!\n");
  mLeft = new Motor(4, 5, 3);
  mRight = new Motor(6, 7, 8);
}

StaticJsonDocument<1024> doc;

void loop() {
  delay(10);
  if(!Serial.available()) {
    return;
  }
  Serial.println("loop");
  DeserializationError err = deserializeJson(doc, Serial);

  if (err == DeserializationError::Ok) {
    float xSpeed = doc[DIR_AXIS].as<float>();
    float ySpeed = doc[ACCEL_AXIS].as<float>();
    float lMult = 1, rMult = 1;

    Serial.println("Y speed = " + String(ySpeed));

    // Serial.println("xSpeed = " + String(xSpeed));

    // if (xSpeed < 0) {
    //   Serial.println("[Left]");
    // } else if (xSpeed > 0) {
    //   Serial.println("[Right]");
    // } else {
    //   Serial.println("[Straight]");
    // }

    if (xSpeed < 0) {
      lMult = 1 - abs(xSpeed);
    } else {
      lMult = 1;
    }

    if (xSpeed > 0) {
      rMult = 1 - abs(xSpeed);
    } else {
      rMult = 1;
    }

    // Serial.println("lMult = " + String(lMult));
    // Serial.println("rMult = " + String(rMult));
    // Serial.println("left = " + String(ySpeed * 127 * lMult));
    // Serial.println("right = " + String(ySpeed * 127 * rMult));

    mLeft->setSpeed(ySpeed * 127 * lMult);
    mRight->setSpeed(ySpeed * 127 * rMult);

    Serial.println("---------------------------");
  } else {
    // erro
    Serial.print("deserializeJson() returned ");
    Serial.println(err.c_str());
    // while (Serial.available() > 0)
    //   Serial.read();
  }

  mLeft->tick();
  mRight->tick();
}
