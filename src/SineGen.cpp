#include "SineGen.h"
#include "Utility.h"
#include <rtaudio/RtAudio.h>

SineGen::SineGen() {
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 2;
}

SineGen::~SineGen() { dac.closeStream(); }
void SineGen::setFrequency(int frequency) { sine.setFrequency(frequency); }

void SineGen::play(int nFrames) {
  RtAudioFormat format =
      (sizeof(stk::StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
  unsigned int bufferFrames = stk::RT_BUFFER_SIZE;
  if (dac.openStream(&parameters, NULL, format,
                     static_cast<unsigned int>(stk::Stk::sampleRate()),
                     &bufferFrames, &(tick), (void *)&sine)) {
    std::cout << dac.getErrorText() << std::endl;
    return;
  }

  sine.setFrequency(440.0);

  if (dac.startStream()) {
    std::cout << dac.getErrorText() << std::endl;
    return;
  }
}
