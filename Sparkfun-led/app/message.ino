#include <ArduinoJson.h>

bool createMessage(char *payload)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["DeviceId"] = DEVICE_ID;
    root["PropertyName"] = "LED state";
    root["Value"] = digitalRead(LED_PIN) ? "false" : "true";

    root.printTo(payload, MESSAGE_MAX_LEN);
}
