#include <Arduino.h>
#include "ArduinoJson.h"
#include <motor.h>

#define ACCEL_AXIS "y"
#define DIR_AXIS "x"

Motor *mLeft, *mRight;

float lerp(float a, float b, float f) { return a * (1.0 - f) + (b * f); }

void setup() { 
  Serial.begin(9600);
  Serial.write("OK!\n");
  mLeft = new Motor(4, 5, 3);
  mRight = new Motor(6, 7, 8);
}

StaticJsonDocument<1024> doc; //declaration of the document that will be filled with the serial port data

void loop() { 
  delay(10);
  if(!Serial.available()) {
    return;
  }
  DeserializationError err = deserializeJson(doc, Serial);

  if (err == DeserializationError::Ok) {
    float xSpeed = doc[DIR_AXIS].as<float>();
    float ySpeed = doc[ACCEL_AXIS].as<float>();
    float lMult = 1, rMult = 1;

    /*
    calculates the multiplier to be passed to each engine based on the ratio between the
    acceleration on the y-axis (coming from pressing the trigger R2 of the DS4) and direction pointed in the
    x-axis (coming from DSR L3 analogue movement)
    */ 
    if (xSpeed < 0) { //L3 is being moved to the left
      lMult = 1 - abs(xSpeed);
    } else {
      lMult = 1;
    }

    if (xSpeed > 0) { //L3 is being moved to the right
      rMult = 1 - abs(xSpeed);
    } else {
      rMult = 1;
    }

    //sets the speed of each engine with their respectives multipliers
    mLeft->setSpeed(ySpeed * 127 * lMult); 
    mRight->setSpeed(ySpeed * 127 * rMult);

  } else {
    Serial.print("deserializeJson() returned ");
    Serial.println(err.c_str());
  }

  mLeft->tick();
  mRight->tick();
}
