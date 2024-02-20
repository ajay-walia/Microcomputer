#define PIN_INT 2
#define PIN_M_IO 51

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World!");

  //AD0..7 instantiation
  int ad[8] = {38, 40, 42, 44, 46, 48, 50, 52};
  int a[8] = {23, 25, 27, 29, 31, 33, 35};

  Serial.println("Setting AD0..7 as output\n");
  //AD as output 
  pinMode(ad[0],OUTPUT);
  pinMode(ad[1],OUTPUT);
  pinMode(ad[2],OUTPUT);
  pinMode(ad[3],OUTPUT);
  pinMode(ad[4],OUTPUT);
  pinMode(ad[5],OUTPUT);
  pinMode(ad[6],OUTPUT);
  pinMode(ad[7],OUTPUT);

  Serial.println("Setting ALE as output\n");
  //ALE as output
  pinMode(49,OUTPUT);

  Serial.println("ALE set to HIGH (1)(Address Latching)\n");
  //ALE setup: address latch
  digitalWrite(49,HIGH);

  Serial.println("AD0..7 set to 1\n");
  //AD setup: address latch
  digitalWrite(ad[0],HIGH);
  digitalWrite(ad[1],HIGH);
  digitalWrite(ad[2],HIGH);
  digitalWrite(ad[3],HIGH);
  digitalWrite(ad[4],HIGH);
  digitalWrite(ad[5],HIGH);
  digitalWrite(ad[6],HIGH);
  digitalWrite(ad[7],HIGH);

/*  
  Serial.println("Setting A0..7 as input for test\n");
  //AD as output 
  pinMode(a[0],INPUT);
  pinMode(a[1],INPUT);
  pinMode(a[2],INPUT);
  pinMode(a[3],INPUT);
  pinMode(a[4],INPUT);
  pinMode(a[5],INPUT);
  pinMode(a[6],INPUT);
  pinMode(a[7],INPUT);
  for(int i = 0; i < 8; i++){
        
  }
  */
  

  //delay
  delay(5000);

  Serial.println("ALE set to LOW (0)(Data Bus)\n");
  //ALE setup: data setup
  digitalWrite(49,LOW);

  Serial.println("AD0..7 set to 0\n");
  //AD setup: data setup
  digitalWrite(ad[0],LOW);
  digitalWrite(ad[1],LOW);
  digitalWrite(ad[2],LOW);
  digitalWrite(ad[3],LOW);
  digitalWrite(ad[4],LOW);
  digitalWrite(ad[5],LOW);
  digitalWrite(ad[6],LOW);
  digitalWrite(ad[7],LOW);

  delay(5000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
