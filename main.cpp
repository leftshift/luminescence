#define VERSION "0.0.1"

#include <Arduino.h>

#define USE_SERIAL Serial

#define WSSID "munichmakerlab"
#define PASSWORD "h4ckingr00m"

#define OTA_HOST "ardy.io"
#define OTA_URL "/luminescence/ota"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266httpUpdate.h>
#include <EEPROM.h>

void ota_update();
void serial_set_id();

unsigned char node_id;
ESP8266WiFiMulti wifiMulti;

void setup() {
    USE_SERIAL.begin(9600);
    USE_SERIAL.printf("[SETUP]\tStarting luminescence Version %s", VERSION);

    USE_SERIAL.println("[SETUP]\tReading Node ID from EEPROM...");
    EEPROM.begin(512);
    node_id = EEPROM.read(1);

    USE_SERIAL.printf("[SETUP]\tGot node id %i", node_id);

    if (node_id == 0 || node_id == 255){
        serial_set_id();
    }

    USE_SERIAL.printf("[SETUP]\tConnecting to Wifi %s...", WSSID);
    wifiMulti.addAP(WSSID, PASSWORD);
    while (not wifiMulti.run() == WL_CONNECTED) {
        USE_SERIAL.println("[SETUP]\tWaiting for Wifi...");
        delay(100);
    }

    USE_SERIAL.println("[SETUP]\tChecking for OTA Update");
    ota_update();

}

void ota_update() {
    t_httpUpdate_return ret = ESPhttpUpdate.update(OTA_HOST, OTA_URL, VERSION);
    switch (ret) {
        case HTTP_UPDATE_FAILED:
            Serial.println("[UPDATE]\tUpdate failed.");
            break;
        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("[UPDATE]\tAlready the newest version.");
            break;
        case HTTP_UPDATE_OK:
            Serial.println("[UPDATE]\tPerforming update...");
            break;
    }
}

void serial_set_id() {
    Serial.read();
    Serial.println("[SETID]\tPlease enter an ID for this node: (1-254)");
    while (Serial.available() == 0){
        delay(500);
    }
    node_id = Serial.read();
    Serial.printf("[SETID]\tSet ID to %i", node_id);
}

void loop() {
    // put your main code here, to run repeatedly:
}
