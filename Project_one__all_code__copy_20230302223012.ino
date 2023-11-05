#include "Adafruit_seesaw.h" //importing library

Adafruit_seesaw ss;//ss is the declared shortcut like in python u could do with the imported files and use the abrevation (like: import matplotlib.pyplot as plt)

int photodiode_value = A0; //pin where photoresitor is communicating with arduino (not nessesary to declare this could just use A0 in code and not have this)
int sensorvalue; // declare variable

void setup() {
  Serial.begin(115200); //communication with the serial monitor(where we saw our current and capacitance readings) (can use any baud but 115200 is preffered for speed)
  //serial monitor can be found in tools and once ur board is connected u will see options for baud in this case u would choose 115200 but u can change this to 96000

  Serial.println("seesaw Soil Sensor example!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
  pinMode(2, OUTPUT); //pump connection at pin 2
  pinMode(photodiode_value, INPUT);//photoresistor connection (can be written as pinMode(A0, INPUT))
  pinMode(7,OUTPUT);// led lights at pin 7
}

void loop() {
  float tempC = ss.getTemp();//useless in this code since we didnt use it
  uint16_t capread = ss.touchRead(0);
  int sensorvalue = analogRead(photodiode_value); // reads the values of photoresitor (from pin A0)

  if (capread >= 530){
    
    digitalWrite(2, LOW);//turn off pump because of high capacitance (pressure of soil on sensore)

    }
  else if (capread < 530){
    digitalWrite(2,HIGH);//turn on pump bc of low capacitance
    
    }
    
  if (capread < 530){
    digitalWrite(7,LOW);//turns off led to make them not run at the same time as pump lights will only turn on when pump is off (to avoid overloading the system)
  }
  else if (sensorvalue >= 300){//too much light turn off led 
    digitalWrite(7,LOW);
    }
  else if (sensorvalue < 300) {//turns led on (condition only met when pump is off and light around is providing less that 300 milliamps i think but could be wrong)
    digitalWrite(7,HIGH);
    }
    

  Serial.print("Capacitive: "); Serial.println(capread);//prints capacitance from soil sensor on serial monitor
  Serial.print("Current:"); Serial.println(sensorvalue);//prints current from photoresistor to serial monitor
  delay(1000);
}
//dry soil 597-602 or at 1/2inch 542-550
//wet soil 620-655
//very wet soil 660>
//can include temperature for soil sensor