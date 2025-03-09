#include <cstdlib>
#include <stk/FileLoop.h>
#include <stk/FileWvOut.h>
#include <stk/Stk.h>

int main() {
  stk::Stk::setSampleRate(44100.0);

  int nFrames = 100000;

  stk::FileLoop input;
  stk::FileWvOut output;

  try {
    input.openFile("/usr/share/stk/rawwaves/sinewave.raw", true);
    output.openFile("./hellosine.wav", 1, stk::FileWrite::FILE_WAV,
                    stk::Stk::STK_SINT16);
  } catch (stk::StkError &) {
    return EXIT_FAILURE;
  }

  input.setFrequency(440.0);

  stk::StkFrames frames (nFrames, 1);
  try {
	output.tick(input.tick(frames));
  }
  catch (stk::StkError &) {
	return EXIT_FAILURE;
  }

//   for (int i{0}; i < nFrames; i++) {
//     try {
//       output.tick(input.tick());
//     } catch (stk::StkError &) {
//       return EXIT_FAILURE;
//     }
//   }

  return EXIT_SUCCESS;
}
