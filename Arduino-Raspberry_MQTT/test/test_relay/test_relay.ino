
#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <DHT.h>        // DHT11 temperature and humidity sensor Predefined library

#define DHTTYPE DHT22
#define dht_dpin 0
float t =0.0;

////////////////////////////////////////////// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "Vodafone-A41502247";
const char* wifi_password = "s3wv93bx9pkwd3m5";

////////////////////////////////////////////// MQTT
// Make sure to update this for your own MQTT Broker!
// TODO: externalize parameters!!!
const char* mqtt_server = "192.168.1.0";
const char* mqtt_moisture_topic = "moisture";
const char* mqtt_sub_topic = "pump_activation";
const char* mqtt_username = "rio";
const char* mqtt_password = "onslario89";
const int mqtt_port = 1883; //choose K8s MQTT port
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "ClientID";
const char* ok_message = "ON";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(dht_dpin, DHTTYPE);
 

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, wifi_password);
  dht.begin();
  pinMode(D7, OUTPUT);       //D7 as output
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  //client.setServer(mqtt_server, mqtt_port);
  //client.setCallback(callback);
}

void loop() {

  Serial.println("LED ON");
  digitalWrite(D7, HIGH);
  delay(2000);
  Serial.println("LED OFF");
  digitalWrite(D7, LOW);
  delay(5000);
}
