#ifndef SINEGEN_H
#define SINEGEN_H

#include "TermInput.h"
#include "SynthConfig.h"
#include <cstdlib>
#include <rtaudio/RtAudio.h>
#include <stk/RtAudio.h>
#include <stk/RtWvOut.h>
#include <stk/SineWave.h>
#include <stk/Instrmnt.h>

class SineGen : public TermInput::CallbackInterface
{
public:
  SineGen();
  ~SineGen();
  void setFrequency(int frequency);
  void play(int nFrames);
  virtual void hasEvent(char ch) override
  {
    std::cout << "I got: " << ch << '\n';
    switch (ch)
    {
    case 'A':
      setFrequency(440);
      break;
    case 'B':
      setFrequency(466);
      break;
    case 'C':
      setFrequency(493);
      break;
    case 'D':
      setFrequency(523);
      break;
    case 'E':
      setFrequency(554);
      break;
    case 'F':
      setFrequency(587);
      break;
    case 'G':
      setFrequency(622);
      break;
    case 'H':
      setFrequency(659);
      break;
    case 'I':
      setFrequency(698);
      break;
    case 'J':
      setFrequency(739);
      break;
    case 'K':
      setFrequency(783);
      break;
    case 'L':
      setFrequency(830);
      break;
    case 'M':
      setFrequency(880);
      break;
    default:
      return;
    }
    play(100);
  }

private:
  stk::SineWave sine;
  RtAudio dac;
  RtAudio::StreamParameters parameters;
  TickData data;
};
#endif
