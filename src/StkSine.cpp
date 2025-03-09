#include <stk/FileLoop.h>
#include <stk/FileWvOut.h>
#include <cstdlib>

int main() {
	stk::Stk::setSampleRate(44100.0);

	stk::FileLoop input;
	stk::FileWvOut output;

	input.openFile("/usr/share/stk/rawwaves/sinewave.raw", true);

	output.openFile("./hellosine.wav", 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16);

	input.setFrequency(440.0);

	for (int i{0}; i < 40000; i++) {
		output.tick(input.tick());
	}

	return EXIT_SUCCESS;
}	
