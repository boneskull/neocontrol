# neocontrol

> NeoPixels + Homie + ESP8266

This thing uses [homie-esp8266](https://homie-esp8266.readme.io/) to control a strip of WS2812B (NeoPixel) LED's.
 
## Features
 
- It just cycles through the colors, but can be extended with other behaviors via [Makuna's](https://github.com/Makuna) [Task](https://github.com/Makuna/Task) module.
- You can switch it on/off and change speed via MQTT (thanks Homie!).
- Data pin, initial speed, NeoPixel type (GRB, RGB, RGBW etc), and pixel count are configurable via JSON and MQTT, as well as WiFi and MQTT config.
- Uses [PlatformIO](http://platformio.org/).
- Built for a [WeMos D1 Mini](https://www.wemos.cc/product/d1-mini.html); should work with most ESP8266 boards.
- CMake setup is for CLion.

Maybe this is good example code for somebody?

## License

:copyright: 2016 Christopher Hiller.  Licensed MIT.


