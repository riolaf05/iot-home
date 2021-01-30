#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "FASTWEB-D82B93";
const char* wifi_password = "W1JA3M3R2A";

int Status = 12;  // Digital pin D6
int sensor = 13;  // Digital pin D7

// MQTT
// Make sure to update this for your own MQTT Broker!
const char* mqtt_server = "ec2-13-59-218-106.us-east-2.compute.amazonaws.com";
const char* mqtt_topic = "intrusion";
const char* mqtt_username = "rio";
const char* mqtt_password = "onslario89";
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "Client ID";

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

void setup() {

  Serial.begin(9600);
  pinMode(sensor, INPUT);   // declare sensor as input
  pinMode(Status, OUTPUT);  // declare LED as output

  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }

}


void loop() {
  
  long state = digitalRead(sensor);
    if(state == HIGH) {
      digitalWrite (Status, HIGH);
      client.publish("intrusion", "ON"); //Topic name
      Serial.println("Motion detected!");
      delay(15000);
    }
    else {
      digitalWrite (Status, LOW);
      client.publish("intrusion", "OFF"); //Topic name
      Serial.println("Motion absent!");
      delay(1000);
      }
      
}
