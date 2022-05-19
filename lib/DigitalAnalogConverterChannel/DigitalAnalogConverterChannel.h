#ifndef DIGITAL_ANALOG_CONVERTER_CHANNEL_H
#define DIGITAL_ANALOG_CONVERTER_CHANNEL_H

#include <DigitalAnalogConverter.h>

class DigitalAnalogConverterChannel
{
private:
  DigitalAnalogConverter *converter;
  Channel channel;

public:
  DigitalAnalogConverterChannel(DigitalAnalogConverter *converter, Channel channel)
  {
    this->channel = channel;
    this->converter = converter;
  }

  void write(int value)
  {
    this->converter->write(this->channel, value);
  }
};

#endif
