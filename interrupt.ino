#define INT 2
#define M_IO 51
#define ALE 49
#define WRITE 45
#define READ 43
int ad[8] = {38,40,42,44,46,48,50,52};


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

  //mode 0, port A output, port B input
  setModeControlWord(0,'o','dontcare',0,'i','dontcare');
  delay(10);
  IOWrite('A', 0b00001111);
  attachInterrupt(digitalPinToInterrupt(INT), keyDetect, RISING);
}

void loop() {
  //put your main code here, to run repeatedly:
  keyDetect();
}

void keyDetect() {
  byte col = IORead('B');
  byte row = 0b1000;
  do {
    IOWrite('A', row);
    delay(10);
    col = IORead('B');
    delay(10);
    if (col > 0) {
      Serial.print("Key: ");
      Serial.print(keyIdentify(row, col));
      Serial.println();
      delay(250);
      return;
    }
    if (row == 1) {
      row = 0b1000;
    } else {
      row = row/2;
    }
  } while (true);
}

char keyIdentify(byte aPin, byte bPin) {

  //row vs row
  if (aPin == 0b1000) {
    switch (bPin) {
      case 0b1000:
        return 'D';
      case 0b0100:
        return '#';
      case 0b0010:
        return '0';
      case 0b0001:
        return '*';
      default:
        return;
    }
  }
  else if (aPin == 0b0100) {
    switch (bPin) {
      case 0b1000:
        return 'C';
      case 0b0100:
        return '9';
      case 0b0010:
        return '8';
      case 0b0001:
        return '7';
      default:
        return;
    }
  }
  else if (aPin == 0b0010) {
    switch (bPin) {
      case 0b1000:
        return 'B';
      case 0b0100:
        return '6';
      case 0b0010:
        return '5';
      case 0b0001:
        return '4';
      default:
        return;
    }
  }
  else if (aPin == 0b0001) {
    switch (bPin) {
      case 0b1000:
        return 'A';
      case 0b0100:
        return '3';
      case 0b0010:
        return '2';
      case 0b0001:
        return '1';
      default:
        return;
    }
  }
}

void setModeControlWord(int paMode, char paIO, char pcIOUpper, int pb_mode, char pbIO, char pcIOLower) {
  byte controlWord = 0b10000000;
  switch (paMode) {
    case 1:
      bitSet(controlWord, 5);
      break;
    case 2:
      bitSet(controlWord, 6);
      break;
    default:
      break;
  }
  switch (paIO) {
    case 'i':
      bitSet(controlWord, 4);
      break;
    default:
      break;
  }
  switch (pcIOUpper) {
    case 'i':
      bitSet(controlWord, 3);
      break;
    default:
      break;
  }
  switch (pb_mode) {
    case 1:
      bitSet(controlWord, 2);
      break;
    default:
      break;
  }
  switch (pbIO) {
    case 'i':
      bitSet(controlWord, 1);
      break;
    default:
      break;
  }
  switch (pcIOUpper) {
    case 'i':
      bitSet(controlWord, 0);
      break;
    default:
      break;
  }
  delay(10);
  IOWrite('W', controlWord);
}

void IOWrite(char port, byte data) {
  byte address;
  switch (port) {
    case 'A':
      address = 0;
      break;
    case 'B':
      address = 0b00000001;
      break;
    case 'C':
      address = 0b00000010;
      break;
    default:
      address = 0b00000011;
      break;
  }
  digitalWrite(M_IO, LOW);
  selectAddress(address);

  digitalWrite(WRITE, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(ad[i], bitRead(data, i));
  }
  delay(10);
  digitalWrite(WRITE, HIGH);
}

byte IORead(char port) {
  byte data = 0b00000000;
  byte address;
  switch (port) {
    case 'A':
      address = 0b00000000;
      break;
    case 'B':
      address = 0b00000001;
      break;
    case 'C':
      address = 0b00000010;
      break;
    default:
      address = 0b00000011;
      break;
  }
  //IO space
  digitalWrite(M_IO, LOW);
  selectAddress(address);

  pinIN();
  delay(10);
  digitalWrite(READ, LOW);
  for (int i = 0; i < 8; i++) {
    if (digitalRead(ad[i])) {
      bitSet(data, i);
    }
  }
  delay(10);
  digitalWrite(READ, HIGH);
  return data;
} 

void selectAddress(byte address) {
  pinOUT();
  digitalWrite(ALE, HIGH);
  //Address generation
  for(int i = 0; i < 8; i++) {
    digitalWrite(ad[i], bitRead(address, i));
  }
  delay(10);
  digitalWrite(ALE, LOW);
  delay(10);
}

void initialControl() {
  digitalWrite(ALE, LOW);
  digitalWrite(WRITE, HIGH);
  digitalWrite(READ, HIGH);
  digitalWrite(M_IO, HIGH);
}

void pinOUT() {
  for (int i = 0; i < 8; i++) {
    pinMode(ad[i], OUTPUT);
  }
}

void pinIN() {
  for (int i = 0; i < 8; i++) {
    pinMode(ad[i], INPUT);
  }
}