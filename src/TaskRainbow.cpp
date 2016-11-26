//
// Created by Christopher Hiller on 11/24/16.
//

#include "TaskRainbow.h"

TaskRainbow::TaskRainbow (Adafruit_NeoPixel &neoPixelStrip) : Task(
  MsToTaskTime(0)), strip(neoPixelStrip), position(0), forwards(true) {
}

void TaskRainbow::OnUpdate (uint32_t deltaTime) {
  uint16_t numPixels = strip.numPixels();
  for (uint16_t i = 0; i < numPixels; i++) {
    uint32_t color = wheel((byte) ((i + position) & 255));
    strip.setPixelColor(i, color);
  }
  strip.show();
  if (forwards) {
    if (position == 255) {
      forwards = false;
      position--;
    } else {
      position++;
    }
  } else {
    if (position == 0) {
      forwards = true;
      position++;
    } else {
      position--;
    }
  }
}

bool TaskRainbow::OnStart () {
  Serial.println("Rainbow starting");
  strip.clear();
  strip.show();
  return true;
}

void TaskRainbow::OnStop () {
  Serial.println("Rainbow stopping");
  strip.clear();
  strip.show();
}

uint32_t TaskRainbow::wheel (byte pos) {
  pos = (byte) (255 - pos);
  if (pos < 85) {
    return strip.Color((uint8_t) (255 - pos * 3), 0, (uint8_t) (pos * 3));
  }
  if (pos < 170) {
    pos -= 85;
    return strip.Color(0, (uint8_t) (pos * 3), (uint8_t) (255 - pos * 3));
  }
  pos -= 170;
  return strip.Color((uint8_t) (pos * 3), (uint8_t) (255 - pos * 3), 0);
}
