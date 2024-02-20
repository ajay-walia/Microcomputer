//AD0..7 instantiation
//52 = AD7 = 1D
//...
//38 = AD0 = 8D
int ad[8] = {38, 40, 42, 44, 46, 48, 50, 52};

void initialControl() {
  digitalWrite(49, LOW);
  digitalWrite(45, HIGH);
  digitalWrite(43, HIGH);
  digitalWrite(51, HIGH);
}

void pinOUT() {
  for (int i = 0; i < 8; i++)
    pinMode(ad[i], OUTPUT);
}

void pinIN() {
  for (int i = 0; i < 8; i++)
    pinMode(ad[i], INPUT);
}

void MemWrite(byte address, byte data){
  pinOUT();
  //ALE enabled
  //Address bus enable
  digitalWrite(51, HIGH);
  digitalWrite(49, HIGH);

  //Initialize address to B0000 0000 (input address)
  for(int i = 0; i < 8; i++)
    digitalWrite(ad[i], bitRead(address, i));

  //ALE disabled
  //Data bus enable
  delay(1000);
  digitalWrite(49, LOW);
  delay(1000);

  //Initalize data to B0000 0001 (input data)
  for(int i = 0; i < 8; i++)
    digitalWrite(ad[i], bitRead(data,i));
    //Write enabled
  digitalWrite(45, LOW);
  delay(1000);
  digitalWrite(45,HIGH); //WRITE Disabled 
  
}

byte MemRead(byte address){
  byte newData = 0b00000000;

  pinOUT();
  //ALE enabled
  //Address bus enable
  digitalWrite(51, HIGH);
  digitalWrite(49, HIGH);

  //Initialize address to B0000 0000 (input)
  for(int i = 0; i < 8; i++){
    digitalWrite(ad[i], bitRead(address, i));
  }

  //ALE disabled
  //Data bus enable
  delay(1000);
  digitalWrite(49, LOW);
  
  //Read enabled
  delay(1000);
  pinIN();
  delay(1000);
  digitalWrite(43, LOW);
  delay(1000);

  //Read data
  for (int i = 0; i < 8; i++) {
    if (digitalRead(ad[i])) {
      bitSet(newData, i);
    }
  }

  //RD Disabled
  digitalWrite(43, HIGH);
  return newData;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World!");
  
  byte address_SRAM1 = 0b00000000;
  byte address_SRAM2 = 0b00000100;

  Serial.println("Setting ALE, M/IO*, RD, and WR as output\n");
  pinMode(49,OUTPUT); //ALE
  pinMode(51,OUTPUT); //M/IO*
  pinMode(45,OUTPUT); //WR
  pinMode(43,OUTPUT); //RD
  initialControl();

  //WR
  MemWrite(address_SRAM1, 0xFF);
  MemWrite(address_SRAM2, 0xAA);

  //RD
  byte data_SRAM1 = MemRead(address_SRAM1);
  byte data_SRAM2 = MemRead(address_SRAM2);

  Serial.println("Data from SRAM1 is as follows: ");
  Serial.println(data_SRAM1, BIN);

  Serial.println("\nData from SRAM2 is as follows: ");
  Serial.println(data_SRAM2, BIN);
      

}

void loop() {
  // put your main code here, to run repeatedly:

}
