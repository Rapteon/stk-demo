#ifndef SINEGEN_H
#define SINEGEN_H

#include "TermInput.h"
#include <cstdlib>
#include <stk/RtWvOut.h>
#include <stk/SineWave.h>

class SineGen : public TermInput::CallbackInterface {
public:
  SineGen();
  ~SineGen();
  void increaseFrequency();
  void play(int nFrames);
  virtual void hasEvent (char ch) override{
    std::cout << "I got: " << ch << '\n';
  }

private:
  stk::SineWave sine;
  stk::RtWvOut *dac = 0;
};
#endif