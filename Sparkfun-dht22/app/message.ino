#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <DHT.h>

static DHT dht(DHT_PIN, DHT_TYPE);
void initSensor()
{
    dht.begin();
}

float readTemperature()
{
    return dht.readTemperature();
}

float readHumidity()
{
    return dht.readHumidity();
}



void createTemperatureMessage(char *payload)
{
    float temperature = readTemperature();
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["DeviceId"] = DEVICE_ID;
    root["PropertyName"] = "Temperature";
    root["PropertyValue"] = temperature;
    
    root.printTo(payload, MESSAGE_MAX_LEN);
}

void createHumidityMessage(char *payload)
{
    float humidity = readHumidity();
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    
    root["DeviceId"] = DEVICE_ID;
    root["PropertyName"] = "Humidity";
    root["PropertyValue"] = humidity;
    
    root.printTo(payload, MESSAGE_MAX_LEN);
}
