#include<SPI.h>
//Master
#define LED 5           
int x=0;
int PWM=0;
void setup (void)
{
  Serial.begin(115200);                   //Starts Serial Communication at Baud Rate 115200 
  
                //Sets pin 2 as input 
  pinMode(LED,OUTPUT);                    //Sets pin 7 as Output
  
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
  digitalWrite(SS,HIGH);                  // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)
}
void loop(void)
{
  byte Mastersend,Mastereceive;          
 /*buttonvalue = digitalRead(ipbutton);   //Reads the status of the pin 2
  if(buttonvalue == HIGH)                //Logic for Setting x value (To be sent to slave) depending upon input from pin 2
  {
    x = 1;
  }
  else
  {
    x = 0;
  }
  */
  digitalWrite(SS, LOW);                  //Starts communication with Slave connected to master
  
  Mastersend=x;                      
  Mastereceive=SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave
  
  /*if(Mastereceive == 1)                   //Logic for setting the LED output depending upon value received from slave
  {
    digitalWrite(LED,HIGH);              //Sets pin 7 HIGH
    Serial.println("Master LED ON");
  }
  else
  {
   digitalWrite(LED,LOW);               //Sets pin 7 LOW
   Serial.println("Master LED OFF");
  }*/

//Serial.println(Mastereceive);

  if(Mastereceive==1 && PWM<225){
    PWM+=10;
  }
  if(Mastereceive==2 && PWM>0){
    PWM-=10;
  }
  Serial.println(PWM);
 analogWrite(LED,PWM);
  delay(1000);
}
