#include "SineGen.h"
#include "TermInput.h"
#include <cstdlib>
#include <stk/Stk.h>

int main() {
  stk::Stk::setSampleRate(44100);
  stk::Stk::showWarnings(true);
  stk::Stk::setRawwavePath("/usr/share/stk/rawwaves/");

  int nFrames = 1000000;

  std::cout << "Press any char to stop.\n";
  SineGen gen{};

  TermInput termInput{};
  termInput.registerCallback(&gen);
  termInput.start();
  getchar();
  termInput.stop();
  return EXIT_SUCCESS;
}