#include <ESP8266WiFi.h>
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include "DHT.h"

//topics
#define MQTT_PUB_TEMP "dh22/temp"
#define MQTT_PUB_HUM "dh22/hum"

// Uncomment one of the lines below for whatever DHT sensor type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

/*Put your SSID & Password*/
const char* ssid = "FASTWEB-D82B93";  // Enter SSID here
const char* password = "W1JA3M3R2A";  //Enter Password here

// MQTT
// Make sure to update this for your own MQTT Broker!
const char* mqtt_server = "192.168.1.124";
const char* mqtt_username = "rio";
const char* mqtt_password = "onslario89";
const char* clientID = "Client ID";

// DHT Sensor
uint8_t DHTPin = 4; 
               
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);

  dht.begin();              

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  // Initialise the WiFi and MQTT Client objects
  WiFiClient wifiClient;
  PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
  
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  Serial.println(Temperature);
  Serial.println(Humidity);
  
  if (client.publish(MQTT_PUB_TEMP, String(Temperature).c_str())) {
    Serial.println("Temp sent to MQTT topic!");
  }
  delay(2000);
  if (client.publish(MQTT_PUB_HUM, String(Humidity).c_str())) {
    Serial.println("Humidity sent to MQTT topic!");
  }
  delay(2000);

  ESP.deepSleep(3600e6);

}

void loop() {

}
