
// we use 100 omh Resistors 
// keerat baweja, rohan chaudhry, shiven danayak 
// arduino extra credit 


byte upper_A[8]={0x18, 0x24, 0x42, 0x42, 0x7e, 0x81, 0x81, 0x81}; //A
byte heart[8]={0x66, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x0, 0x0}; //Heart
byte longhorn[8]={0x0, 0xc3, 0x3c, 0x3c, 0x18, 0x18, 0x0, 0x0}; // longhorn
byte smiley[8]={0x0, 0x24, 0x0, 0x0, 0x42, 0x42, 0x3c, 0x0}; //smiley face

// boxes 
byte box1[8]={0x0, 0x0, 0x0, 0x18, 0x18, 0x0, 0x0, 0x0};
byte box2[8]={0x0, 0x0, 0x3c, 0x24, 0x24, 0x3c, 0x0, 0x0};
byte box3[8]={0x0, 0x7e, 0x42, 0x42, 0x42, 0x42, 0x7e, 0x0};
byte box4[8]={0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff};

// moving arrow 
byte arr1[8]={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18};
byte arr2[8]={0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x3c};
byte arr3[8]={0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x3c, 0x7e};
byte arr4[8]={0x0, 0x0, 0x0, 0x18, 0x3c, 0x7e, 0x18, 0x18};
byte arr5[8]={0x0, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x18};
byte arr6[8]={0x3c, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x0, 0x0};
byte arr7[8]={0x18, 0x18, 0x18, 0x18, 0x0, 0x0, 0x0, 0x0};
byte arr8[8]={0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

//thank you message 
byte thanku[8]={0x0, 0xae, 0x44, 0x44, 0x44, 0x0, 0x0, 0x0};

// pi 
byte pi[8]={0x0, 0x0, 0x7e, 0x24, 0x24, 0x24, 0x22, 0x0};


//Hooked up to resistors, aka negative end of array board 
uint8_t colPins[8]={ 2, 3, 4, 5, 6, 7, 8, 9}; 

// IC pins, used to distribute multiple outputs from one input
#define SER_PIN 10 // techincally where data enters 
#define SCK_PIN 11 // serial clock, set to HIGH to store serial pin data 
#define RCK_PIN 12 // register clock, set to HIGH after setting pins 

float timeCount = 0; //counter used to determine which output to display 

void setup() {
  // Turn everything to low
  for(int i=0; i<8; i++) {
    pinMode(colPins[i],OUTPUT);
  }
  pinMode(SER_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(RCK_PIN, OUTPUT);
  Serial.begin(9600); // conventional start 
}

void loop() {
  timeCount += 1; 
  
  if(timeCount <  500) {
drawing(heart);
}
else if (timeCount < 1000){ 
drawing(longhorn); 
}  
else if(timeCount < 1500){
  drawing(upper_A); 
}
else if(timeCount < 2000){
  drawing(smiley); 
}

//shifting box 
else if(timeCount < 2500 ){
  drawing(box1); 
}
else if(timeCount < 2600){
  drawing(box2); 
}
else if(timeCount < 2700){
  drawing(box3); 
}
else if(timeCount < 2800){
  drawing(box4); 
}
else if(timeCount < 2900){
  drawing(box3); 
}
else if( timeCount < 3000){
  drawing(box2); 
}
else if(timeCount < 3100){
  drawing(box1); 
}

// scrolling arrow 
else if(timeCount < 3300){
  drawing(arr1); 
}
else if(timeCount < 3500){
  drawing(arr2); 
}
else if(timeCount < 3700){
  drawing(arr3); 
}
else if(timeCount < 3900){
  drawing(arr4); 
}
else if(timeCount < 4100){
  drawing(arr5); 
}
else if(timeCount < 4300){
  drawing(arr6); 
}
else if(timeCount < 4500){
  drawing(arr7); 
}
else if(timeCount < 4700){
  drawing(arr8); 
}

// thank you 
else if(timeCount < 5500){
  drawing(thanku); 
}

// repeat 
else{ 
  timeCount = 0; 
}

}

void drawing(byte gang[]){
    // iterate each row
  int index = 0;
  int rowbits = 0x80;
  for(int row=0; row<8; row++) {
    for(int k=0; k<8; k++) 
      digitalWrite(colPins[k],HIGH); // Cleanup cols
    write595(rowbits); // prepare to write the row
    for(int col=0; col<8; col++)
      digitalWrite(colPins[7-col], gang[row] & 1 << col ? LOW : HIGH);
    write595(0);
    rowbits >>= 1; 
  } 
 // delay(2000);
  

} 


void write595(byte data) {
  // write data to the serial pin, using serial clock as slcok
  // send the LSB first 
  digitalWrite(RCK_PIN, LOW);
  shiftOut(SER_PIN, SCK_PIN, LSBFIRST, data);
  digitalWrite(RCK_PIN, HIGH);
}
