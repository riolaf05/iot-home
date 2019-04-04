int sensor_pin = A0; // Soil Sensor input at Analog PIN A0

int output_value ;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  output_value= analogRead(sensor_pin);

   output_value = map(output_value,550,10,0,100);

   Serial.print("Mositure : ");

   Serial.print(output_value + 87);

   Serial.println("%");

   delay(1000);
    
}
