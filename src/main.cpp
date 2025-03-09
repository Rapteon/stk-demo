#include "SineGen.h"
#include "TermInput.h"
#include <cstdlib>
#include <stk/Stk.h>

int main() {
  // stk::Stk::setSampleRate(44100);
  // stk::Stk::showWarnings(true);

  // int nFrames = 1000000;

  std::cout << "Press any char to stop.\n";
  TermInput termInput{};
  termInput.start();
  getchar();
  termInput.stop();
  // SineGen gen{};
  // termInput.registerCallback(&gen);
  return EXIT_SUCCESS;
}