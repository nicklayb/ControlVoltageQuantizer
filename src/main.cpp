#include <Arduino.h>
#include <Quantizer.h>
#include <DigitalAnalogConverter.h>
#include <DigitalAnalogConverterChannel.h>
#include <SevenSegmentAdapter.h>
#include <ScaleSelector.h>

#define DAC_SELECT_PIN 10

#define SEVEN_SEGMENT_A_CLOCK 2
#define SEVEN_SEGMENT_A_LATCH 3
#define SEVEN_SEGMENT_A_SERIAL 4
#define SCALE_A_PIN A0
#define CV_A_PIN A2

#define SEVEN_SEGMENT_B_CLOCK 5
#define SEVEN_SEGMENT_B_LATCH 6
#define SEVEN_SEGMENT_B_SERIAL 7
#define SCALE_B_PIN A1
#define CV_B_PIN A3

ScaleSelector *scaleSelector;
Quantizer *quantizerA;
Quantizer *quantizerB;

void setup()
{
  DigitalAnalogConverter *converter = new DigitalAnalogConverter(DAC_SELECT_PIN);
  DigitalAnalogConverterChannel *channelA = new DigitalAnalogConverterChannel(converter, ChannelA);
  DigitalAnalogConverterChannel *channelB = new DigitalAnalogConverterChannel(converter, ChannelB);
  SevenSegmentAdapter *sevenSegment = new ShiftRegisterSevenSegment(SEVEN_SEGMENT_A_CLOCK, SEVEN_SEGMENT_A_LATCH, SEVEN_SEGMENT_A_SERIAL);
  scaleSelector = new ScaleSelector(sevenSegment, SCALE_A_PIN);
  quantizerA = new Quantizer(scaleSelector, channelA, CV_A_PIN);
  quantizerB = new Quantizer(scaleSelector, channelB, CV_B_PIN);
}

void loop()
{
  scaleSelector->loop();
  quantizerA->loop();
  quantizerB->loop();
}
