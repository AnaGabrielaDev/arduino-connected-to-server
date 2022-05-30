// libs:
// https://dl.espressif.com/dl/package_esp32_index.json
// https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

#include <HTTPClient.h>
#include <WiFi.h>
 
const char* ssid = "wifi id";
const char* password =  "password";
const int BUTTON_INPUT = 2;
bool buttonState = false;
 
const String endpoint = "https://maxed-ink-production.up.railway.app";
const String key = "/events";
 
void setup() {
  pinMode(BUTTON_INPUT, INPUT_PULLUP);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
 
  Serial.println("\nConnected to the WiFi network");
 
}
 
void loop() {
  buttonState = digitalRead(BUTTON_INPUT);

  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    
    
    if(buttonState){
      Serial.println("button was press");
      HTTPClient http;
   
      http.begin(endpoint + key); //Specify the URL
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST("{\"title\": \"sandbox\", \"nickname\": \"Chegouuuu\"}");  //Make the request
   
      if (httpCode > 0) { //Check for the returning code
          String payload = http.getString();
          Serial.println(httpCode);
          Serial.println(payload);
        }
   
      else {
        Serial.println("Error on HTTP request");
      }
 
      http.end(); //Free the resources
    }
  }
}

//server: https://maxed-ink-production.up.railway.app/events