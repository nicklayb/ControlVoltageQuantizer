#ifndef SCALE_SELECTOR_H
#define SCALE_SELECTOR_H

#include <SevenSegmentAdapter.h>
#include <Scale.h>

#define SCALE_COUNT 9
class ScaleSelector
{
private:
  SevenSegmentAdapter *sevenSegment;
  int scalePin;
  Scale scale = Major;

  void readScale()
  {
    int scaleValue = map(analogRead(this->scalePin), 0, 1023, 0, SCALE_COUNT);
    this->scale = Scale(scaleValue);
  };

  void writeSevenSegment()
  {
    byte scaleDisplay = scalesDisplay[this->scale];
    this->sevenSegment->write(scaleDisplay);
  };

public:
  ScaleSelector(SevenSegmentAdapter *sevenSegment, int scalePin)
  {
    this->scalePin = scalePin;
    this->sevenSegment = sevenSegment;
  };

  void loop()
  {
    this->readScale();
    this->writeSevenSegment();
  };
};

#endif
