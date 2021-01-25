#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <DHT.h>;

#define MQTT_PUB_TEMP "dh22/temp"
#define MQTT_PUB_HUM "dh22/hum"

#define DHTPIN 4     // Digital pin D2
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "FASTWEB-D82B93";
const char* wifi_password = "W1JA3M3R2A";

// MQTT
// Make sure to update this for your own MQTT Broker!
const char* mqtt_server = "192.168.1.124";
const char* mqtt_username = "rio";
const char* mqtt_password = "onslario89";
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "Client ID";

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

void setup() {

  Serial.begin(9600);

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

  //Initializing DH22
  dht.begin();

  delay(2000);
  
  Serial.println("Publishing on MQTT broker..");
  
  if (client.publish(MQTT_PUB_TEMP, String(temp).c_str())) {
    Serial.println("Temp sent to MQTT topic!");
  }
  delay(2000);
  if (client.publish(MQTT_PUB_HUM, String(hum).c_str())) {
    Serial.println("Humidity sent to MQTT topic!");
  }
  delay(2000);
  ESP.deepSleep(30e6); 

}

void loop() {

  
}
