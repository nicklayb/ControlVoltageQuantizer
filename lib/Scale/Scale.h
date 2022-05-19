#ifndef SCALE_H
#define SCALE_H
#include <Arduino.h>

#define VOLTAGE_FACTOR 0.0833
#define MAJOR B11111010
#define MINOR B01100000
#define MINOR_PENTATONIC B11011100
#define BLUES B11110100
#define MAJOR_PENTATONIC B01100110
#define PHRYGIAN B10110110
#define LYDIAN B10111110
#define MIXOLYDIAN B11100000
#define LOCRIAN B11111110

byte scalesDisplay[] = {MAJOR, MINOR, MINOR_PENTATONIC, BLUES, MAJOR_PENTATONIC, PHRYGIAN, LYDIAN, MIXOLYDIAN, LOCRIAN};

enum Scale
{
  Major,
  Minor,
  MinorPentatonic,
  Blues,
  MajorPentatonic,
  Phrygian,
  Lydian,
  Mixolydian,
  Locrian
};

float quantized(Scale scale, int inputValue)
{
  return (inputValue - 1) * VOLTAGE_FACTOR;
};

bool isScaleNote(Scale scale, int inputValue)
{
  int note = inputValue % 12;
  switch (scale)
  {
  case Major:
    return note == 1 || note == 3 || note == 5 || note == 6 || note == 8 || note == 10 || note == 12;
  case Minor:
    return note == 1 || note == 3 || note == 4 || note == 6 || note == 8 || note == 9 || note == 11;
  case MinorPentatonic:
    return note == 1 || note == 4 || note == 6 || note == 8 || note == 11;
  case Blues:
    return note == 1 || note == 3 || note == 4 || note == 6 || note == 7 || note == 8 || note == 11;
  case MajorPentatonic:
    return note == 1 || note == 3 || note == 5 || note == 8 || note == 10;
  case Phrygian:
    return note == 1 || note == 2 || note == 5 || note == 6 || note == 8 || note == 9 || note == 11;
  case Lydian:
    return note == 1 || note == 3 || note == 5 || note == 7 || note == 8 || note == 10 || note == 11;
  case Mixolydian:
    return note == 1 || note == 3 || note == 5 || note == 6 || note == 8 || note == 10 || note == 11;
  case Locrian:
    return note == 1 || note == 2 || note == 4 || note == 6 || note == 7 || note == 9 || note == 11;
  default:
    return false;
  }
};

#endif
