#include <ArduinoJson.h>

bool createMessage(char *payload, bool isLedMessage)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["DeviceId"] = DEVICE_ID;
    if (isLedMessage) {
      root["PropertyName"] = "LED State";
      root["PropertyValue"] = digitalRead(LED_PIN) ? "false" : "true";
    }
    else {
      root["PropertyName"] = "Potentiometer Value";
      root["PropertyValue"] = analogRead(A0);
    }
    
    root.printTo(payload, MESSAGE_MAX_LEN);
}
