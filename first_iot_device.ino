/*This is completely developed by Koushik Samanta
 * it connect with connectionmakeeasy.tk, the site is also developed by Koushik Samanta
 * Good Luck
 * */
/*
 * About the circuit:
 * Esp is connected to 10,11
 * led indicator is 13
 */
#include<SoftwareSerial.h>
#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

dht DHT;


#define DHT11_PIN 2
#define espRx 10
#define espTx 11
SoftwareSerial esp(espRx,espTx);//connect esp 8266 tx rx with digital pin of aruino uno 2 and 3


//define all keywords here
const char busy[]="busy";
char start_instrument1_keyword[]="Main Control:";
char end_instrument1_keyword='<';
char start_instrument2_keyword[]="Fan:";
char end_instrument2_keyword='<';
char start_instrument3_keyword[]="Tube Light:";
char end_instrument3_keyword='<';
char start_instrument4_keyword[]="Light1:";
char end_instrument4_keyword='<';
char start_instrument5_keyword[]="Light2:";
char end_instrument5_keyword='<';
char start_instrument6_keyword[]="Led:";
char end_instrument6_keyword='<';
byte no_of_ins= 6;
byte count_sensor = 2;
//Fetch OK<br>Main Control:ON<br>Fan:OFF<br>Tube Light:OFF<br>Light1:OFF<br>Light2:OFF<br>Controller Led:OFF<br>
//define all variables here
String instrument_data_in;
byte starting_instrument_pin=3;//digital pin 5,6,7,8....13
float sensor[2];



//All the relay are in active low conditionn;


void setup(){
  pinMode(espTx,OUTPUT);
  pinMode(espRx,INPUT);
  
  Serial.begin(115200);
  delay(200);
  esp.begin(4800);
  delay(200);
  lcd.begin(16,2);
  Serial.println(F("Starting Engine"));
  lcd.setCursor(0,0);
  lcd.print("Starting Engine");
  delay(1000);
 
  lcd.clear();
  lcd.setCursor(0,0);
  esp.listen();

  int chk = DHT.read11(DHT11_PIN);//returns 0 if connection is sucsesfull
  if (chk == 0){
     Serial.println(F("DHT11 init success"));
     lcd.setCursor(0,0);
     lcd.print("Sensor Check");
     lcd.setCursor(0,1);
     lcd.print("Success");
  }
  else{
    Serial.println(F("DHT11 init fail\n\n"));
    lcd.print("DHT11 Fail");
  }
  delay(1000);
  
  for(byte i=0;i<no_of_ins;i++){
    pinMode(starting_instrument_pin+i,OUTPUT);
  }
  for(byte i=0;i<no_of_ins;i++){
    digitalWrite(starting_instrument_pin+i,HIGH);
  }

  
  pinMode(12,OUTPUT);//controller's led is connected to pin 12
  pinMode(9,OUTPUT);//ESP RESET PIN//making it low esp will be reset by hardware interrupt it is connected via a relay on pin 9
  digitalWrite(9,HIGH);
  digitalWrite(12,HIGH);
  delay(5000);
  dump_esp();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Checking Wifi");
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  delay(3000);
  digitalWrite(13,LOW);
  while(!esp_setup());
  lcd.setCursor(0,1);
  lcd.print("Looking Good");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Hey Koushik!");
  lcd.setCursor(0,1);
  lcd.print("I'm being Ready");
  delay(1000);
  lcd.clear();
  
  
}

void loop() {
  //I have moved this inside a loop as for memory problem,
  float Temperature=30,Humidity=50;
  
  //checking for the sensor's data
  
  int chk = DHT.read11(DHT11_PIN);//returns 0 if connection is sucsesfull
  if (chk == 0){
  Temperature = DHT.temperature-5;
  sensor[0]= Temperature;
  Humidity = DHT.humidity+10;
  sensor[1] =Humidity;
  Serial.print(F("Temperature = "));
  Serial.print((char)223);
  Serial.println(Temperature);
  Serial.print(F("Humidity = "));
  Serial.println(Humidity);
  }
  else{
    Serial.println(F("DHT is'nt Responding"));
  }
  int t,h;
  t=Temperature;h=Humidity;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.print(h);
  lcd.print("%");
  
  instrument();
  dump_esp();
  delay(5000);
  digitalWrite(13,LOW);
  delay(500);
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  if(Temperature !=30 || Humidity != 50){
    _sensor();
  }
  delay(2000);
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  dump_esp();
  
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.print(h);
  lcd.print("%");
  delay(10000);
}
