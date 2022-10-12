#include<SPI.h>   // inluding 
//Slave

void(* resetFunc) (void)=0; 
volatile boolean received1;
volatile boolean received2;
volatile byte Slavereceived,Slavesend;
int meter;
volatile byte store1;
volatile byte store2;
//byte chkmask= B10000000;
//byte id1chk = B00000000;
//byte id2chk = B10000000;
byte idremv = B01111111;

//void(* resetFunc) (void)=0; //declare rest function
void setup()
{
  Serial.begin(9600);
  Serial.println("You hit the restart button---------------------------------------------");
  pinMode(MISO,OUTPUT);                   //Sets MISO as OUTPUT (Have to Send data to Master IN 
  SPCR |= _BV(SPE);                       //Turn on SPI in Slave Mode
  received1 = false;
  received2 = false;
  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
  
}
ISR (SPI_STC_vect)                        //Interrrput routine function 
{
  //Serial.println(millis());
  //Serial.println(SPDR, BIN);
  if(0==SPDR>>7){                  //check which byte was sent   
    store1 = SPDR&idremv;                        // Value received from master if store in variable slavereceived
    received1 = true;                     // recieved 1st bit
    }
  if(1==SPDR>>7){
    store2 = SPDR&idremv;
    received2 = true;                     //recieved 2nd bit
    }
 /*   Serial.println(SPDR&chkmask, BIN); 
    Serial.println(id2chk, BIN); 
  Serial.println(received1);  
  Serial.println(received2);
  */
  }


void loop()
{ 
  
 if(received1&received2)                            //Logic to SET LED ON OR OFF depending upon the value recerived from master
 {
     received1 = false;
     received2 = false;
     //Serial.println(millis());
     //Serial.print("Store1:");
     // Serial.println(store1, BIN);
     //Serial.print("Store2:");
     //Serial.println(store2 ,BIN);
     meter=(int)((store2<<7)+store1);
if(meter>=1024){
   Serial.println("error");
   delay(200);
   resetFunc();
}
     Serial.print("Meter:");
     Serial.println(meter);
    // received1 = false;
     //received2 = false;
//Serial.println(Slavereceived);


      
  //Slavesend=buttonvalue;                             
  //SPDR = Slavesend;                           //Sends the button value to master via SPDR 
}
}
