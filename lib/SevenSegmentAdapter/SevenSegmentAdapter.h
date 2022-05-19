#ifndef SEVEN_SEGMENT_ADAPTER_H
#define SEVEN_SEGMENT_ADAPTER_H

#define BYTE_LENGTH 8

class SevenSegmentAdapter
{
public:
  virtual void write(byte segments);
};

class ShiftRegisterSevenSegment : public SevenSegmentAdapter
{
private:
  int clockPin;
  int latchPin;
  int serialDataPin;

public:
  ShiftRegisterSevenSegment(int clockPin, int latchPin, int serialDataPin) : SevenSegmentAdapter()
  {
    this->clockPin = clockPin;
    this->latchPin = latchPin;
    this->serialDataPin = serialDataPin;

    pinMode(this->clockPin, OUTPUT);
    pinMode(this->latchPin, OUTPUT);
    pinMode(this->serialDataPin, OUTPUT);
  };

  void write(byte segments)
  {
    digitalWrite(this->latchPin, LOW);

    for (int index = 0; index < BYTE_LENGTH; index++)
    {
      byte temp = B00000001 & segments >> index;
      digitalWrite(this->serialDataPin, temp);
      digitalWrite(this->clockPin, HIGH);
      digitalWrite(this->clockPin, LOW);
    }

    digitalWrite(this->latchPin, HIGH);
  }
};

#endif
