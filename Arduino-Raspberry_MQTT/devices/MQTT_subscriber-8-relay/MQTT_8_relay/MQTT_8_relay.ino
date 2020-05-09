#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <DHT.h>        // DHT11 temperature and humidity sensor Predefined library

#define DHTTYPE DHT22
#define PUMP D7
#define dht_dpin D3

const int ledPin = 0; // This code uses the built-in led for visual feedback that the button has been pressed
const int buttonPin = 13; // Connect your button to pin #13
float t =0.0;

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "FASTWEB-D82B93";
const char* wifi_password = "W1JA3M3R2A";

// MQTT
// Make sure to update this for your own MQTT Broker!
// TODO: externalize parameters!!!
const char* mqtt_server = "192.168.1.0";
const char* mqtt_moisture_topic = "moisture";
const char* mqtt_temperature_topic = "temperature";
const char* mqtt_sub_topic = "pump_activation";
const char* status_topic = "smart_garden_status";
const char* mqtt_username = "rio";
const char* mqtt_password = "onslario89";
const int mqtt_port = 1883; //choose K8s MQTT port
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "ClientID";
const char* ok_message = "ON";

int RelayControl1 = 4; // Digital Arduino Pin used to control the motor
int RelayControl2 = 5;
int RelayControl3 = 6;
int RelayControl4 = 7;

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(dht_dpin, DHTTYPE);

 
void callback(char* topic, byte* payload, unsigned int length) {
  String string = "";
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    string.concat((char)payload[i]);
  }
  switch (string) {
  case "11":
    digitalWrite(RelayControl1,HIGH);// NO1 and COM1 Connected (LED on)
    delay(1000);
    break;
  case "12":
    digitalWrite(RelayControl2,HIGH);
    delay(10000);
    digitalWrite(RelayControl2,LOW);
  case "13":
    digitalWrite(RelayControl3,HIGH);
    delay(10000);
    digitalWrite(RelayControl3,HIGH);
  case "14":
    digitalWrite(RelayControl4,HIGH);
    delay(10000);
    digitalWrite(RelayControl4,LOW);
  case "15":
    digitalWrite(RelayControl5,HIGH);
    delay(10000);
    digitalWrite(RelayControl5,LOW);
    break;
  default:
    delay(1000);
    break;
}
}


void setup() {
  //configuring Serial, WIFI, outputs
  Serial.begin(115200);
  WiFi.begin(ssid, wifi_password);
  pinMode(PUMP, OUTPUT);       //D7 as output
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  
  //Configuring MQTT client
   Serial.println("Configuring MQTT client..");
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqtt_username, mqtt_password )) {
      Serial.println("connected");  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  
  //Subscribing to MQTT queue
  client.subscribe("pump_activation");

  //Itilializing relay outputs
  pinMode(RelayControl1, OUTPUT);
  pinMode(RelayControl2, OUTPUT);
  pinMode(RelayControl3, OUTPUT);
  pinMode(RelayControl4, OUTPUT);
  
}

void loop() {
  Serial.println("Checking pump activation..");
  client.loop();
  delay(5000);
}
