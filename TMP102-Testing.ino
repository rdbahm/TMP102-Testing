#include <Wire.h>
const int tmp102Address = 0x48;

float min_temp = 100;
float max_temp = 0;

void setup(){
  Serial.begin(9600);
  Wire.begin();
}

void loop(){
  float this_temperature = getTemperature();

  if(this_temperature > max_temp)
  {
    max_temp = this_temperature;
  }
  if(this_temperature < min_temp)
  {
    min_temp = this_temperature;
  }
  Serial.print(millis());
  Serial.print(",");
  Serial.print(this_temperature);
  Serial.print(",");
  Serial.print(min_temp);
  Serial.print(",");
  Serial.println(max_temp);
  
  delay(5000);
}

float getTemperature(){
  Wire.requestFrom(tmp102Address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  float fahrenheit = (1.8 * celsius) + 32;  
  return fahrenheit;
}
