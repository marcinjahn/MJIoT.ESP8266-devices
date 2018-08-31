#include <ArduinoJson.h>

bool createMessage(char *payload)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["DeviceId"] = DEVICE_ID;
    root["PropertyName"] = "Heater State";
    root["PropertyValue"] = digitalRead(RELAY_PIN) ? "false" : "true";

    root.printTo(payload, MESSAGE_MAX_LEN);
}

