const int strobe = 7;
const int clock = 9;
const int data = 8;

void sendCommand(uint8_t value)
{
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, value);
  digitalWrite(strobe, HIGH);
}

void reset()
{
  sendCommand(0x40); // set auto increment mode
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xc0);   // set starting address to 0
  for(uint8_t i = 0; i < 16; i++)
  {
    shiftOut(data, clock, LSBFIRST, 0x00);
  }
  digitalWrite(strobe, HIGH);
}

void setup()
{
  pinMode(strobe, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);

  sendCommand(0x8f);  // activate
  reset();
}

void loop()
{
  sendCommand(0x44);  // set single address

  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xc0); // 1st digit
  shiftOut(data, clock, LSBFIRST, 0xff);
  digitalWrite(strobe, HIGH);

  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xc5); // 3rd LED
  shiftOut(data, clock, LSBFIRST, 0x01);
  digitalWrite(strobe, HIGH);

  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xcb); // 3rd LED
  shiftOut(data, clock, LSBFIRST, 0x01);
  digitalWrite(strobe, HIGH);

  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xce); // last digit
  shiftOut(data, clock, LSBFIRST, 0xff);
  digitalWrite(strobe, HIGH);
}
