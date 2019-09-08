//Making a water and air pump turn on and off with a delay.

//Initiailising paramerters
int i;
int sun = A0;
int pump = 8;
int air = 9;
int show;
int swtch= 10;
int switchstate;


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



        digitalWrite(pump, HIGH);// MAKES SURE IT STARTS AT 0
        digitalWrite(air,LOW);
        delay(1800000); // waits 30 min
        digitalWrite(pump, LOW); //pump turns on
        digitalWrite(air,HIGH); //air turns off
        //digitalWrite(LED_BUILTIN, LOW);
        delay(120000);// runs 2 min
        digitalWrite(pump, HIGH);//pump turns off}
}
