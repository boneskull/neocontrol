#include <Arduino.h>
#include <Homie.h>
#include <Adafruit_NeoPixel.h>
#include <Boards.h>
#include <Task.h>
#include <TaskRainbow.h>

#define PIXEL_TYPE_GRB "grb"
#define PIXEL_TYPE_RGB "rgb"
#define PIXEL_TYPE_RGBW "rgbw"

#define DEFAULT_PIXEL_KHZ NEO_KHZ800
#define DEFAULT_PIXEL_TYPE PIXEL_TYPE_GRB
#define DEFAULT_PIXEL_COUNT 9
#define DEFAULT_DATA_PIN D1
#define DEFAULT_CYCLE_SPEED 200

HomieNode stripNode("light-strip", "light-strip");
HomieSetting<long> dataPinSetting("data_pin",
  "Data pin for NeoPixels; default D1");
HomieSetting<long> speedSetting("speed", "Cycle speed");
HomieSetting<long> pixelCountSetting("pixel_count",
  "Number of pixels in strip; default 60");
HomieSetting<const char *> pixelTypeSetting("pixel_type",
  "One of 'rgb', 'grb', 'rgbw'; default 'grb'");
Adafruit_NeoPixel strip;
TaskManager taskManager;
TaskRainbow taskRainbow(strip);

neoPixelType getPixelType () {
  const char *pixelType = pixelTypeSetting.get();
  if (strcmp(pixelType, PIXEL_TYPE_RGB) == 0) {
    return NEO_RGB;
  } else if (strcmp(pixelType, PIXEL_TYPE_RGBW) == 0) {
    return NEO_RGBW;
  }
  return NEO_GRB;
}

void setupSettings () {
  dataPinSetting.setDefaultValue(DEFAULT_DATA_PIN).setValidator(
    std::function<bool (long)>([] (long value) {
      return IS_PIN_DIGITAL(value);
    }));

  pixelCountSetting.setDefaultValue(DEFAULT_PIXEL_COUNT).setValidator(
    std::function<bool (long)>([] (long value) {
      return value > 0;
    }));

  pixelTypeSetting.setDefaultValue(DEFAULT_PIXEL_TYPE).setValidator(
    std::function<bool (const char *)>([] (const char *value) {
      return strcmp(value, PIXEL_TYPE_GRB) == 0 ||
        strcmp(value, PIXEL_TYPE_RGB) == 0 ||
        strcmp(value, PIXEL_TYPE_RGBW) == 0;
    }));

  speedSetting.setDefaultValue(DEFAULT_CYCLE_SPEED).setValidator(
    std::function<bool (long)>([] (long value) {
      return value > 0;
    }));

  Serial.print("Setting speed to ");
  Serial.println(speedSetting.get());
  taskRainbow.setTimeInterval((uint32_t) speedSetting.get());
}

void setupHomie () {
  Homie_setFirmware("neocontrol", "0.1.0");
  Homie.setup();
}

void setupEvents () {
  stripNode.advertise("speed").settable(
    std::function<bool (const HomieRange &, const String &)>(
      [] (const HomieRange &range, const String &value) {
        long speed = value.toInt();
        if (speed > 0 && speed != speedSetting.get()) {
          taskRainbow.setTimeInterval((uint32_t)speed);
          stripNode.setProperty("speed").send(String(speed));
          return true;
        }
        return false;
      }));

  stripNode.advertise("on").settable(
    std::function<bool (const HomieRange &, const String &)>(
      [] (const HomieRange &range, const String &value) {
        if (value.equalsIgnoreCase("true") || value.equals("1")) {
          if (taskManager.StatusTask(&taskRainbow) != TaskState_Running) {
            stripNode.setProperty("on").send("true");
            taskManager.StartTask(&taskRainbow);
          }
        } else {
          if (taskManager.StatusTask(&taskRainbow) == TaskState_Running) {
            stripNode.setProperty("on").send("false");
            taskManager.StopTask(&taskRainbow);
          }
        }
        return true;
      }));
}

void setupStrip () {
  strip.setPin((uint8_t) dataPinSetting.get());
  strip.updateType((neoPixelType) (getPixelType() + DEFAULT_PIXEL_KHZ));
  strip.updateLength((uint16_t) pixelCountSetting.get());
  strip.begin();
}

void setup () {
  Serial.begin(115200);
  Serial << endl << endl;
  setupSettings();
  Serial.println("Settings configured");
  setupHomie();
  Serial.println("Homie configured");
  setupStrip();
  Serial.println("Strip configured");
  setupEvents();
  Serial.println("Events configured");
  taskManager.StartTask(&taskRainbow);
}

void loop () {
  Homie.loop();
  taskManager.Loop();
}
