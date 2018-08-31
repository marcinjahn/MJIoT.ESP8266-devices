#include <ArduinoJson.h>

bool createServoMessage(char *payload, int value)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["DeviceId"] = DEVICE_ID;
    root["PropertyName"] = "Servo Position";
    root["PropertyValue"] = value;
    
    root.printTo(payload, MESSAGE_MAX_LEN);
}

bool createSensorMessage(char *payload, bool value)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["DeviceId"] = DEVICE_ID;
    root["PropertyName"] = "Light State";
    root["PropertyValue"] = value;
    
    root.printTo(payload, MESSAGE_MAX_LEN);
}
