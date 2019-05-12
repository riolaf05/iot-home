#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char* ssid = "Vodafone-A41502247";
const char* wifi_password =  "s3wv93bx9pkwd3m5";
// MQTT
// TODO: externalize parameters!!!
const char* mqttServer = "192.168.1.9";
const int mqttPort = 1883;
const char* mqttUser = "rio";
const char* mqttPassword = "onslario89";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, wifi_password);

  //Wi-Fi Connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);

  //MQTT Broker Connection
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP32");
 
}
 
void loop() {
  client.loop();
}
