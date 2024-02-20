#define INT 2
#define M_IO 51
#define ALE 49
#define WRITE 45
#define READ 43
int ad[8] = {38,40,42,44,46,48,50,52};

//reset control signals
void initialControl() {
  digitalWrite(ALE, LOW);
  digitalWrite(WRITE, HIGH);
  digitalWrite(READ, HIGH);
  digitalWrite(M_IO, HIGH);
}

//set pins to output
void pinOUT() {
  for (int i = 0; i < 8; i++) {
    pinMode(ad[i], OUTPUT);
    delay(100);
  }
}

//set pins to input
void pinIN() {
  for (int i = 0; i < 8; i++) {
    pinMode(ad[i], INPUT);
    delay(100);
  }
}

//select address location
void selectAddress(byte address) {
  pinOUT();
  digitalWrite(ALE, HIGH);
  //Address generation
  for(int i = 0; i < 8; i++) {
    digitalWrite(ad[i], bitRead(address, i));
    delay(100);
  }
  delay(500);
  digitalWrite(ALE, LOW);
  delay(500);
}

//write to IO
void IOWrite(byte data) {
  pinOUT();
  //ALE already low from selectAddress()
  digitalWrite(WRITE, LOW);
  delay(500);
  for(int i = 0; i < 8; i++) {
    digitalWrite(ad[i], bitRead(data, i));
    delay(100);
  }
  digitalWrite(WRITE, HIGH);
  delay(500);
}

byte IORead() {
  byte data = 0b00000000;
  pinIN();
  delay(500);
  digitalWrite(READ, LOW);
  // if (1), set that pin to 1, otherwise, leave as 0 (from byte data = 0x00)
  for (int i = 0; i < 8; i++) {
    if (digitalRead(ad[i])) {
      bitSet(data, i);
    }
  }
  delay(500);
  digitalWrite(READ, HIGH);
  delay(500);
  return data;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
  
  Serial.println("Initialzing initial control signals...");
  pinMode(ALE, OUTPUT);
  pinMode(WRITE, OUTPUT);
  pinMode(READ, OUTPUT);
  pinMode(M_IO, OUTPUT);
  initialControl();  

  //CS, control register A1 = 1, A0 = 1
  //C = 0, B = 0, A = 0
  //A7 = 0, A6 = 0, A5 = 0, A4,3,2 on arduino connected to nothing, A1 = 1, A0 = 1 for control register
  selectAddress(0b00000011);
  //mode 0, port A out, port b in, port c don't care
  IOWrite(0b10000010);

  //CS, port A, A1 = 0, A0 = 0
  //C = 0, B = 0, A = 0
  //A7 = 0, A6 = 0, A5 = 0, A4,3,2 on arduino connected to nothing, A1 = 0, A0 = 0 for port A
  selectAddress(0b00000000);
  //write to port 5 0x55
  IOWrite(0x5A); // 

  
  byte portB_data = IORead();
  Serial.println("Value of B: ");
  Serial.print(portB_data, BIN);

}

void loop() {
  // put your main code here, to run repeatedly:

}