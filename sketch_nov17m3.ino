#include<SPI.h>
//Master
#define Meter 0          
int x=0;
byte send1;
byte send2;
byte clearid = B01111111;
byte id2 = B10000000;
void setup (void)
{
  Serial.begin(9600);                   //Starts Serial Communication at Baud Rate 115200 
  
                //Sets pin 2 as input 
  pinMode(Meter, INPUT);
  
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
  digitalWrite(SS,HIGH);                  // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)
}
void loop(void)
{
  x=analogRead(Meter);
  Serial.print("meter ");
  Serial.println(x);
  //delay(500);
  
  send1=(byte)(x)&clearid;  // send 1  is 7 bits and a mask 8th bit know postion
  send2=(((byte)(x>>7))&clearid)|id2;  // send 2, shifts x right 7, transforms to byte, clears the 8th byte, then writes id2
  byte Mastersend,Mastereceive;          
  SPI.begin();
  digitalWrite(SS, LOW);                  //Starts communication with Slave connected to master
  
  Mastersend=send1;                      // sets to send 1
  Mastereceive=SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave
    //Serial.print("send 1 byte ");
    //Serial.println(send1, BIN);
  delay(500);
  Mastersend=send2;                       // sets to send 2
    //Serial.print("send 2 byte ");
    //Serial.println(send2, BIN);                      
  Mastereceive=SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave
  delay(500);
  SPI.endTransaction();

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

 // delay(1000);
}
