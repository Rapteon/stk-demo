#include "SineGen.h"
#include "Utility.h"
#include <rtaudio/RtAudio.h>

SineGen::SineGen() {
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 2;

  RtAudioFormat format =
      (sizeof(stk::StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
  unsigned int bufferFrames = stk::RT_BUFFER_SIZE;
		try {
				dac.openStream(&parameters, NULL, format,
														 static_cast<unsigned int>(stk::Stk::sampleRate()),
														 &bufferFrames, &(tick), (void *)&sine);
		}
		catch(stk::StkError &) {
				//std::cout << dac.getErrorText() << std::endl;
				std::cout << "Error handling at line 19\n";
				throw "Could not opens stream\n";
		}
}

SineGen::~SineGen() { dac.closeStream(); }
void SineGen::setFrequency(int frequency) { sine.setFrequency(frequency); }

void SineGen::play(int nFrames) {

  std::cout << "Playing now\n";

	try {
		dac.startStream();
	}
	catch(stk::StkError &) {
    //std::cout << dac.getErrorText() << std::endl;
    std::cout << "Error handling at line 36.\n";
    return;
	}

  // Added this sleep here because closing the stream immediately meant
  // no audio would be played.
	std::this_thread::sleep_for(std::chrono::milliseconds(250));

	try {
		dac.stopStream();
	}
	catch(stk::StkError &) {
    //std::cout << dac.getErrorText() << std::endl;
    std::cout << "Error handling at line 45.\n";
    return;
	}
}
