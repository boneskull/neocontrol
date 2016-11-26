#ifndef NEOCONTROL_TASKRAINBOW_H
#define NEOCONTROL_TASKRAINBOW_H

#include <Arduino.h>
#include <Task.h>
#include <Homie.h>
#include <Adafruit_NeoPixel.h>

class TaskRainbow : public Task {
public:
  TaskRainbow (Adafruit_NeoPixel &neoPixelStrip);
private:
  Adafruit_NeoPixel &strip;
  bool forwards;
  byte position;

  virtual bool OnStart ();

  virtual void OnStop ();

  virtual void OnUpdate (uint32_t deltaTime);

  uint32_t wheel (byte pos);
};

#endif //NEOCONTROL_TASKRAINBOW_H
