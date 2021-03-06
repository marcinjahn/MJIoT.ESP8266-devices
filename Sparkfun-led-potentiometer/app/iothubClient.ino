static WiFiClientSecure sslClient; // for ESP8266
#include <ArduinoJson.h>

const char *onSuccess = "\"online\"";
const char *notFound = "\"No method found\"";


void SendStateToCloud(bool isLedMessage) {
    char messagePayload[MESSAGE_MAX_LEN];
    createMessage(messagePayload, isLedMessage);
    sendMessage(iotHubClientHandle, messagePayload);
}

void ledOn() {
  digitalWrite(LED_PIN, LOW);
  SendStateToCloud(true);
}

void ledOff() {
  digitalWrite(LED_PIN, HIGH);
  SendStateToCloud(true);
}


void DoAction(String value) {
  Serial.println(value);
  if (value == "true") {
    ledOn();
    Serial.println("ON");
  }
  else if (value == "false")
    ledOff();
}

 
static void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void *userContextCallback)
{
    if (IOTHUB_CLIENT_CONFIRMATION_OK == result)
    {
        Serial.println("Message sent to Azure IoT Hub.");
        //blinkLED();
    }
    else
    {
        Serial.println("Failed to send message to Azure IoT Hub.");
    }
    messagePending = false;
}

static void sendMessage(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, char *buffer)
{
    IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray((const unsigned char *)buffer, strlen(buffer));
    if (messageHandle == NULL)
    {
        Serial.println("Unable to create a new IoTHubMessage.");
    }
    else
    {
        //MAP_HANDLE properties = IoTHubMessage_Properties(messageHandle);
        //Map_Add(properties, "temperatureAlert", temperatureAlert ? "true" : "false");
        Serial.printf("Sending message: %s.\r\n", buffer);
        if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, sendCallback, NULL) != IOTHUB_CLIENT_OK)
        {
            Serial.println("Failed to hand over the message to IoTHubClient.");
        }
        else
        {
            messagePending = true;
            Serial.println("IoTHubClient accepted the message for delivery.");
        }

        IoTHubMessage_Destroy(messageHandle);
    }
}

IOTHUBMESSAGE_DISPOSITION_RESULT receiveMessageCallback(IOTHUB_MESSAGE_HANDLE message, void *userContextCallback)
{
    Serial.println("Received message");
    IOTHUBMESSAGE_DISPOSITION_RESULT result;
    const unsigned char *buffer;
    size_t size;
    if (IoTHubMessage_GetByteArray(message, &buffer, &size) != IOTHUB_MESSAGE_OK)
    {
        Serial.println("Unable to IoTHubMessage_GetByteArray.");
        result = IOTHUBMESSAGE_REJECTED;
    }
    else
    {
        /*buffer is not zero terminated*/
        char *temp = (char *)malloc(size + 1);

        if (temp == NULL)
        {
            return IOTHUBMESSAGE_ABANDONED;
        }

        strncpy(temp, (const char *)buffer, size);
        //temp[size] = '\0';
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(temp);
        const char* charValue = json["PropertyValue"];
        String value = String(charValue);

        DoAction(value);
        
        //Serial.printf(json["Property"]);
        //Serial.printf("Receive C2D message: %s.\r\n", temp);
        free(temp);
        //blinkLED();
    }
    return IOTHUBMESSAGE_ACCEPTED;
}

int deviceMethodCallback(const char *methodName, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
{
    Serial.printf("Try to invoke method %s.\r\n", methodName);
    const char *responseMessage = onSuccess;
    int result = 200;

//    if (strcmp(methodName, "start") == 0)
//    {
//        start();
//    }
//    else if (strcmp(methodName, "stop") == 0)
//    {
//        stop();
//    }
//    else
//    {
//        Serial.printf("No method %s found.\r\n", methodName);
//        responseMessage = notFound;
//        result = 404;
//    }

    *response_size = strlen(responseMessage);
    *response = (unsigned char *)malloc(*response_size);
    strncpy((char *)(*response), responseMessage, *response_size);

    return result;
}
