// JSON reader for OpenWeatherMap optimized for NodeMCU ESP 12E
// by Michiel van Hoorn - 2016 - http://stuffingpi.azurewebsites.net/


// MIT License
// Copyright (c) 2016 Michiel van Hoorn
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// Refer to http://openweathermap.org/api for API information and details

// Using Arduino JSON library by Benoit Blanchon
// https://github.com/bblanchon/ArduinoJson


#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char* ssid     = "Your_SSID_here";           // insert your SSID
const char* password = "Your_WIFI_Password_here";   // insert your password

WiFiClient client;

const char* server = "api.openweathermap.org";  // server's address
const char* resource = "/data/2.5/weather?q=Lucca&units=metric&APPID=[Your_API_KEY_Here]"; // insert your API key

char response[600]; // this fixed sized buffers works well for this project using the NodeMCU.

void setup(){
    delay(3000);
    // initialize serial
    Serial.begin(9600);
    while(!Serial){
        delay(100);
        }
      
    // initialize WiFi
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
    }
   
}



void loop(){
    
        // connect to server  
        bool ok = client.connect(server, 80);
        
        while(!ok){
            //Serial.print(".");
            delay(500);        
        }
    
        delay(500);
    
        //Send request to resource
        client.print("GET ");
        client.print(resource);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.println("Connection: close");
        client.println();
    
        delay(100);
    
        //Reading stream and remove headers
        client.setTimeout(10000);
   
        bool ok_header = ok_header = client.find("\r\n\r\n");
    
        while(!ok_header){
        // wait
        }
         
        client.readBytes(response, 800);
        
        // uncomment line below to see data received for debugging purposes or just fun    
        // Serial.println(response); 
        
        // process JSON
        DynamicJsonBuffer jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(response);
        
        if (!root.success()) {
        Serial.println("JSON parsing failed!");
        } 
        else {
        //Serial.println("JSON parsing worked!");
        }
        
        const char* location = root["name"]; 
        const char* weather = root["weather"][0]["description"];
        double temp = root["main"]["temp"];
        
        // Print data to Serial
        Serial.print("*** ");
        Serial.print(location);
        Serial.println(" ***");
        Serial.print("Type: ");
        Serial.println(weather);
        Serial.print("Temp ");
        Serial.print(temp);
        Serial.println("C");
        Serial.println("----------"); 
     
        client.stop(); // disconnect from server
    
        for(int x=0; x<10; x++){ // wait for new connection with progress indicator
            Serial.print(".");
            delay(99999);
        }
        
        Serial.println("");
     
    }
