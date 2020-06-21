//multiplexer control
int MultiplexerControl4 = 2; //D4
int MultiplexerControl3 = 0; //D3
int MultiplexerControl2 = 4; //D2

float moistureSensor(char inputPin){
    int dryValue = 1023;
    int wetValue = 0;
    int friendlyDryValue = 0;
    int friendlyWetValue = 100;
    //function which calculates the moisture sensor output value
    int rawValue = analogRead(inputPin); //Read the analog value
    int percentage_value = map(rawValue, dryValue, wetValue, friendlyDryValue, friendlyWetValue); //Calibrazione sensore: https://greensense.github.io/Blog/2017/02/17/Arduino-Soil-Moisture-Sensor-Calibration/
    Serial.print("Moisture pecentage: ");
    Serial.print(percentage_value);
    Serial.println("%");
    return percentage_value;
}


void setup() {
  Serial.begin(115200);
  pinMode(MultiplexerControl4, OUTPUT);
  pinMode(MultiplexerControl3, OUTPUT);
  pinMode(MultiplexerControl2, OUTPUT);
  
}

void loop() {
  digitalWrite(MultiplexerControl4, HIGH); //A
  digitalWrite(MultiplexerControl3, HIGH); //B
  digitalWrite(MultiplexerControl2, LOW); //C
  float moisture_value = moistureSensor(A0);
  char cstr[16];


}
