# neocontrol

> NeoPixels + Homie + ESP8266

This thing uses [homie-esp8266](https://homie-esp8266.readme.io/) to control a strip of WS2812B (NeoPixel) LED's.
 
## Features
 
- As of this writing, it just cycles through the colors, but can be extended with other behaviors via [Makuna's](https://github.com/Makuna) [Task](https://github.com/Makuna/Task) module.
- You can switch it on/off and change speed via MQTT (thanks Homie!).
- Data pin, initial speed, NeoPixel type (GRB, RGB, RGBW etc), and pixel count are configurable via JSON and MQTT, as well as WiFi and MQTT config.
- Uses [PlatformIO](http://platformio.org/).
- Built for a [WeMos D1 Mini](https://www.wemos.cc/product/d1-mini.html); should work with most ESP8266 boards.
- CMake setup is for CLion.

Maybe this is good example code for somebody?

## Installation

These steps are a rough guide.  You'll probably want to get familiar with [Homie](https://github.com/marvinroger/homie), [homie-esp8266](https://homie-esp8266.readme.io/docs/), and [PlatformIO](http://docs.platformio.org).

1.  Install [PlatformIO](http://platformio.org/)
2.  Clone this repo
3.  Execute `pio install` in your working copy
4.  Create `data/homie/config.json` as per [docs](https://homie-esp8266.readme.io/docs/json-configuration-file), or use the web-based configuration tool. 
5.  Upload SPIFFS via `pio run --target uploadfs`
6.  Build & upload via `pio run --target upload`

## License

:copyright: 2016 Christopher Hiller.  Licensed MIT.


