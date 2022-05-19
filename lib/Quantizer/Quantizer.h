#ifndef QUANTIZER_H
#define QUANTIZER_H

#include <DigitalAnalogConverterChannel.h>
#include <ScaleSelector.h>
#include <Scale.h>

class Quantizer
{
private:
  DigitalAnalogConverterChannel *converter;
  ScaleSelector *scaleSelector;
  int cvPin;

  void writeOutput()
  {
    int controlVoltage = this->readCv();
    Scale scale = Scale(controlVoltage);
    if (isScaleNote(scale, controlVoltage))
    {
      float quantizedValue = quantized(scale, controlVoltage);
      this->converter->write(quantizedValue);
    }
  }

  int readCv()
  {
    return map(analogRead(this->cvPin), 0, 1023, 1, 60);
  }

public:
  Quantizer(ScaleSelector *scaleSelector, DigitalAnalogConverterChannel *converter, int cvPin)
  {
    this->scaleSelector = scaleSelector;
    this->converter = converter;
    this->cvPin = cvPin;
    pinMode(this->cvPin, INPUT);
  }

  void loop()
  {
    this->writeOutput();
  }
};
#endif
