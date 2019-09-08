//Creating a sensor that will tell when the sun is up by using an light dependant resistor (LDR)

//Init parameters
int i;
int sun = A0;
int pump = 8;
int air = 9;
int show;
int swtch= 10;
int switchstate;

//Setting up inputs and outputs on the arduino
void setup() {
  pinMode(pump,OUTPUT);
  pinMode(air,OUTPUT);
  pinMode(sun,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(swtch,INPUT);
  Serial.begin(9600);
}

void loop() {
sun = analogRead(A0);
switchstate = digitalRead(10);

Serial.print(sun);
 if( sun > 30)
 {
        digitalWrite(pump, HIGH);// MAKES SURE IT STARTS AT 0
        digitalWrite(air,LOW);
        delay(7200000); // waits 30 min 7200000
        digitalWrite(pump, LOW); //pump turns on
        //digitalWrite(LED_BUILTIN, LOW);
        delay(120000);// runs 2 min 120000
        digitalWrite(pump, HIGH);//pump turns off
       //digitalWrite(LED_BUILTIN, LOW);
       i++; // counts number of cycles
//       if(i==5 ||i==10 ||i==15){ //numbers are which cycles the aerator is on for.
//        digitalWrite(air,HIGH); //airpump on
//        delay(9); //wait time
//        show =2;} // debuggoing
//        else{digitalWrite(air,HIGH); //turns it off
//        show = 1; // debugging
//       }
    
  Serial.println(show);
  }
else {
  i=0;
  digitalWrite(pump, HIGH); //night time so all is off
  digitalWrite(air,LOW);
  show = 3; // debugging.
  
}
}
