#include <WiFi.h>

#include "esp_websocket_client.h"

// Replace with your network credentials
const char *ssid = "It hurts when IP";
const char *password = "brojevi1";

const int tqw1 = 4;
const int tqw2 = 23;

esp_websocket_client_handle_t handle;

void setup()
{
    pinMode(tqw1, PULLDOWN);
    pinMode(tqw2, PULLDOWN);
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("qqConnecting to WiFi..");
    }

    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());

    const esp_websocket_client_config_t ws_cfg = {
        .uri = "wss://ws-tutorial-sviki.herokuapp.com/",
    };

    handle = esp_websocket_client_init(&ws_cfg);
    Serial.println("izmedu1");
    esp_err_t x = esp_websocket_client_start(handle);
    Serial.println("izmedu2");
    while (esp_websocket_client_is_connected(handle) == false)
    {
        delay(200);
    }

    Serial.println("povezan");
    delay(2000);

    const char *data = "abcde";
    int output = esp_websocket_client_send(handle, data, 5, 90000);
    Serial.print("Rezultat: ");
    Serial.println(output);
    delay(200);

    bool conn = esp_websocket_client_is_connected(handle);
    Serial.print("Povezan: ");
    Serial.println(conn);
}

void loop()
{
    if(digitalRead(tqw1) == HIGH && digitalRead(tqw2) == HIGH){
        esp_websocket_client_send(handle, "PONOVI", 7, 90000);
        Serial.println("PONOVI");
    }
    else if(digitalRead(tqw1) == HIGH){
        esp_websocket_client_send(handle, "DA", 3, 90000);
        Serial.println("DA");
    }
    else if(digitalRead(tqw2) == HIGH){
        esp_websocket_client_send(handle, "NE", 3, 90000);
        Serial.println("NE");
    }

    // if(digitalRead(tqw3) == HIGH){
    //     Serial.println("TISINA");
    //     esp_websocket_client_send(handle, "TISINA", 7, 90000);
    // }
    // if(digitalRead(tqw4) == HIGH){
    //     Serial.println("NESTO");
    //     esp_websocket_client_send(handle, "PONOVI", 6, 90000);
    // }
    delay(100);
}