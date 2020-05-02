#include <WiFiEspClient.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include "SoftwareSerial.h"

#define WIFI_AP "Vodafone-A41502247"
#define WIFI_PASSWORD "s3wv93bx9pkwd3m5"

// Initialize the Ethernet client object
WiFiEspClient espClient;

SoftwareSerial soft(2, 3); // RX, TX

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  InitWiFi();
}

void loop() {

}


void InitWiFi() {
  // initialize serial for ESP module
  soft.begin(9600);
  // initialize ESP module
  WiFi.init(&soft);
  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(WIFI_AP);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    delay(500);
  }
  Serial.println("Connected to AP");
}
