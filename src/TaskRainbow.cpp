//
// Created by Christopher Hiller on 11/24/16.
//

#include "TaskRainbow.h"

TaskRainbow::TaskRainbow (Adafruit_NeoPixel &neoPixelStrip)
  : Task(MsToTaskTime(0)), strip(neoPixelStrip), position(0) {
}

void TaskRainbow::OnUpdate (uint32_t deltaTime) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, wheel((byte) (i + position)) & 255);
  }
  strip.show();
  position = (byte) (position < 256 ? position + 1 : 0);
}

bool TaskRainbow::OnStart () {
  return true;
}

void TaskRainbow::OnStop () {
  strip.clear();
  strip.show();
}

uint32_t TaskRainbow::wheel (byte position) {
  position = (byte) (255 - position);
  if (position < 85) {
    return strip.Color((uint8_t) (255 - position * 3), 0,
      (uint8_t) (position * 3));
  }
  if (position < 170) {
    position -= 85;
    return strip.Color(0, (uint8_t) (position * 3),
      (uint8_t) (255 - position * 3));
  }
  position -= 170;
  return strip.Color((uint8_t) (position * 3), (uint8_t) (255 - position * 3),
    0);
}
