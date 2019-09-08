//***********************************************************************************************************************************************************************************************************
//This code for the hyrdoponics system integrates a variety of sensors. this would be brought in late in the term. it uses an ldr to ensure that the system does not run at night cause root rot. 
//The ldr also resets the time variables everyday to prevent overflow.
//The code also uses two temprature sesnsors. thes monitor water and atmostpheric temproture. As an advance project these could be used not only as display and warnign paramitors but as a way to regulate
//the time between cycles.
//The moisture sensor is used to check that the pump is actualy filling the hydroponics tub and that that the sump has enough water in it.
//The screen allows users to see what is going on with the system.
//A further addition would be to add the ph sesor to a display showing how much of each solution to add to the sump. 
//***************************************************************************************************************************************************************************************************


//need to include these librarys to be able to refer to the functions they contain.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;// this is a paremitor tha makes the screen work.

// defines the parimotrs and input out put pins.
int relay = 13; //this is the main relay.
int i = 0; // a counter variable
unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false; // true if still waiting for delay to finish
unsigned long previousMillis=0; // a paremtor for resteting the coutn timer.

const int ldrPin = A3; // this is the signal pin of the ldr.

int ThermistorPin1 = A0;//anolog input from temprature sensor
int Vo1;
float R1 = 10000;
float logR2, R2, T1;

void setup() {
  Serial.begin(9600);// begines baude rate for debugging.

  lcd.init();
  lcd.backlight();
  
  pinMode(relay, OUTPUT);   // initialize the digital pin as an output.
  digitalWrite(relay, HIGH); // turn led on

  delayStart = millis();   // start delay
  delayRunning = true; // not finished yet

  lcd.begin(16,2);
  lcd.clear();

  pinMode(ldrPin, INPUT);

  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

  
  Vo1 = analogRead(ThermistorPin1);
  R2 = R1 * (1023.0 / (float)Vo1 - 1.0);
  logR2 = log(R2);
  T1 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T1 = T1 - 273.15;

  while(i < 2000){ //180000
       digitalWrite(relay, LOW); // turn relay on
    
       lcd.setCursor(0,0); //Set the cursor on the first column and first row.
       lcd.print("Jacks Hydroponics"); //Print the string "Hello World!"
       lcd.setCursor(2,1); //Set the cursor on the third column and the second row (counting starts at 0!.
       lcd.print("Pump On");
       
       i++;
      
  }

  digitalWrite(relay, HIGH); // turn relay off

}
//this is where the main loop begins.
void loop() {
//the loope readin in peramiters for this cycle.
  int ldrStatus = analogRead(ldrPin);
  Vo1 = analogRead(ThermistorPin1);
  R2 = R1 * (1023.0 / (float)Vo1 - 1.0);
  logR2 = log(R2);
  T1 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T1 = T1 - 273.15;


/*  Serial.print("Temperature 1: "); 
  Serial.print(T1);
  Serial.println(" C"); 
*/

//This secotion contolls if the system runs based on daylight
if (ldrStatus > 100){
  
  
    lcd.clear();
    lcd.setCursor(0,0); //Set the cursor on the first column and first row.
    lcd.print("Temp 1: "); //Print the string "Hello World!"
    lcd.print(T1);
    lcd.print(" C");
    lcd.setCursor(2,1); //Set the cursor on the third column and the second row (counting starts at 0!.
    lcd.print("Pump Off :)");

 

//thi section acts at a timer schedualing th epump runs. if more complety was wanted these times could become formuals driven by input sensors but we belive
//this will be beyond the scope of most school term sessions.
  // check if delay has timed out after 10sec == 10000mS
  if (delayRunning && ((millis() - delayStart) >= 7200000)) { //7200000
    delayRunning = false; // // prevent this code being run more then once
    lcd.clear();
    ldrStatus = analogRead(ldrPin);
    Serial.println(ldrStatus);
    while(i < 2000){ //180000
       digitalWrite(relay, LOW); // turn relay on
 
       lcd.setCursor(0,0); //Set the cursor on the first column and first row.
       lcd.print("Jacks Hydroponics"); //Print the string "Hello World!"
       lcd.setCursor(2,1); //Set the cursor on the third column and the second row (counting starts at 0!.
       lcd.print("Pump On :D");
       
       i++;
       ldrStatus = analogRead(ldrPin);
      }
    
    digitalWrite(relay, HIGH); // turn relay off
    delayRunning = true; //Start the delay again
    i = 0; //reset varibles
    delayStart = millis();
    ldrStatus = analogRead(ldrPin);
  }

}else{
        

    lcd.clear();
    lcd.setCursor(0,0); //Set the cursor on the first column and first row.
    lcd.print("SunsAway PumpOff"); //Print the string "Hello World!   
    lcd.setCursor(0,1); //Set the cursor on the first column and first row.
    lcd.print("Temp1: "); //Print the string "Hello World!"
    lcd.print(T1);
    lcd.print("C");      
  
}

}
