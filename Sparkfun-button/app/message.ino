#include <ArduinoJson.h>

bool createMessage(char *payload)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["DeviceId"] = DEVICE_ID;
    root["PropertyName"] = "Switch state";
    root["PropertyValue"] = digitalRead(buttonPin) ? "true" : "false";

    root.printTo(payload, MESSAGE_MAX_LEN);
}
