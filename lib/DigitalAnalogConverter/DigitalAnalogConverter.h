#ifndef DIGITAL_ANALOG_CONVERTER_H
#define DIGITAL_ANALOG_CONVERTER_H

#include <Arduino.h>
#include <SPI.h>

#define REFERENCE_VOLTAGE 5.03
#define REFERENCE_FACTOR 4096

enum Channel
{
  ChannelA,
  ChannelB
};
class DigitalAnalogConverter
{
private:
  int selectPin;

  byte primaryByte(Channel channel, int value)
  {
    byte registerBit = 0b00110000;
    byte primaryByte = (value >> 8) | registerBit;
    switch (channel)
    {
    case ChannelA:
      return primaryByte &= ~(1 << 7);
    default:
      return primaryByte |= (1 << 7);
    }
  }

  byte secondaryByte(int value)
  {
    int secondaryByteMask = 0b0000000011111111;
    return value & secondaryByteMask;
  }

  void transferSpi(byte primaryByte, byte secondaryByte)
  {
    noInterrupts();
    digitalWrite(this->selectPin, LOW);
    SPI.transfer(primaryByte);
    SPI.transfer(secondaryByte);
    digitalWrite(this->selectPin, HIGH);
    interrupts();
  }

public:
  DigitalAnalogConverter(int selectPin)
  {
    this->selectPin = selectPin;
    digitalWrite(this->selectPin, HIGH);
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
  }
  void write(Channel channel, int targetVoltage)
  {
    int newValue = (targetVoltage / REFERENCE_VOLTAGE) * REFERENCE_FACTOR;
    byte primaryByte = this->primaryByte(channel, newValue);
    byte secondaryByte = this->secondaryByte(newValue);

    this->transferSpi(primaryByte, secondaryByte);
  }
};

#endif
