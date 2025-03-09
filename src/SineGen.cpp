#include "SineGen.h"

SineGen::SineGen() {
  std::cout << "Created SineGen\n";

  try {
    dac = new stk::RtWvOut(1);
  } catch (stk::StkError &) {
    throw "Could not initialise SineGen";
  }

  sine.setFrequency(440);
}

SineGen::~SineGen() {
  if (dac != nullptr)
    delete dac;
}
void SineGen::increaseFrequency() { std::cout << "Increase frequency\n"; }

void SineGen::play(int nFrames) {
  std::cout << "Play\n";
  stk::StkFrames frames(nFrames, 1);
  try {
    dac->tick(sine.tick(frames));
  } catch (stk::StkError &) {
    std::cerr << "StkError during sine tick.\n";
  }
}
