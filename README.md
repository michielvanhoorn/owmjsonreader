# owmjsonreader
JSON reader for OpenWeatherMap optimized for NodeMCU ESP 12E using Arduino

This Arduino sketch for a NodeMCU 12E allows you to read and parse JSON from Open Weather Map.

It utilized the ArduinJson library from Benoit Blanchon (https://github.com/bblanchon/ArduinoJson).

You should obtain an API key from Open Weather Map. Replace the API key placeholder [Your_API_KEY_Here].

The result should like something like this (but this is a random code):

const char* resource = "/data/2.5/weather?q=Lucca&units=metric&APPID=ahdhk0031llskdjd7xik3" 

Please make sure you understand the terms of conditionals of Open Weather Map. There are limitations on the amount of requests you can do per minute.

Look at Benoit Blancho excellent example code to learn how to use the library and select specific fields.

