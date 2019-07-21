#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Vodafone-A41502247";
const char* password =  "s3wv93bx9pkwd3m5";
const char* mqttServer = "192.168.1.0";
const int mqttPort = 1883;
const char* mqttUser = "rio";
const char* mqttPassword = "onslario89";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);

  //Wi-Fi Connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  void callback(char* topic, byte* payload, unsigned int length);
  //The callback function is executed when a message is received for a subscribed topic. 
  //The arguments of this callback function are the name of the topic, 
  //the payload (in bytes) and the length of the message received. The message should also return void.

  //MQTT Broker Connection
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
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

  Serial.print("Ready to receive messages..");
  client.subscribe("test");
 
}
 
void loop() {
  client.loop();
}



  
