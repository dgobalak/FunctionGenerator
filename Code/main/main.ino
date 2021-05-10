//Define DAC pins here
#define DAC0 2
#define DAC1 3
#define DAC2 4
#define DAC3 5
#define DAC4 6
#define DAC5 7
#define DAC6 8
#define DAC7 9

#define SINE 0
#define TRI 1
#define SAW 2
#define CUSTOM 3

byte i;
byte res = 100;   //Change this to the number of values in the array lookup tables

//Lookup tables for waveform
byte sinewave[200] = {0};
//byte triwave[101] = {0};
//byte sawwave[101] = {0};
//byte squarewave[50] = {0};

byte generated[100];    //For the generated waveform (Experimental)
                   
void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A5, INPUT);

  generateSine(sinewave);
  // put your setup code here, to run once:
  Serial.begin(9600); // Remove when adding SD functionality
  for(i=2;i<10;i++){pinMode(i,OUTPUT);}    //Set pins as outputs
}

int getWaveShape() {
  const int threshold = 700;
  if (analogRead(A0)>threshold){
    shape = SINE;
  }
  else if (analogRead(A1)>threshold){
    shape = TRI;
  }
  else if (analogRead(A2)>threshold){
    shape = SAW;
  }
  else if (analogRead(A6)>threshold){
    shape = CUSTOM;
  }  
  return shape;
}

//Write binary to output DAC pins
void output(byte value){
  digitalWrite(DAC0, (value & 0b00000001) >>0);
  digitalWrite(DAC1, (value & 0b00000010) >>1);
  digitalWrite(DAC2, (value & 0b00000100) >>2);
  digitalWrite(DAC3, (value & 0b00001000) >>3);
  digitalWrite(DAC4, (value & 0b00010000) >>4);
  digitalWrite(DAC5, (value & 0b00100000) >>5);
  digitalWrite(DAC6, (value & 0b01000000) >>6);
  digitalWrite(DAC7, (value & 0b10000000) >>7);
}


void generateSine(byte sinewave[])
{
  for (int j = 0; j < 200; j++) {
    sinewave[j] = byte(sin(map(j, 0, 200, 0, PI)));
  }
}

void loop() {
  byte *arr = sinewave; 
  // put your main code here, to run repeatedly:
  int arrSize = *(&arr + 1) - arr;
  
  for(i=0;i<arrSize;i++){        //Loop values
    output(generated[i]);
    delay(1);
  }
}
