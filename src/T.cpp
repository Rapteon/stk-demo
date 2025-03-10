#include <rtaudio/RtAudio.h>
#include <stk/BeeThree.h>
#include <stk/Instrmnt.h>
#include <stk/Stk.h>

/*
Holds all class instances and data that are shared by
processing functions.
*/
struct TickData {
  TickData() : instrument{0}, scaler{1.0}, counter{0}, done{false} {}
  stk::Instrmnt *instrument;
  stk::StkFloat frequency;
  stk::StkFloat scaler;
  long counter;
  bool done;
};

int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData) {
  TickData *data = (TickData *)userData;
  stk::StkFloat *samples = (stk::StkFloat *)outputBuffer;

  for (unsigned int i = 0; i < nBufferFrames; i++) {
    *samples++ = data->instrument->tick();
    if (++data->counter % 2000 == 0) {
      data->scaler += 0.025;
      data->instrument->setFrequency(data->frequency * data->scaler);
    }
  }

  if (data->counter > 80000)
    data->done = true;

  return 0;
}

int main() {
  /*
  Set the global sample rate and rawwave path before creating class
  instances.
  */
  stk::Stk::setSampleRate(44100.0);
  stk::Stk::setRawwavePath("/usr/share/stk/rawwaves/");

  TickData data;
  RtAudio dac;

  // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
  RtAudio::StreamParameters parameters;
  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 1;
  RtAudioFormat format =
      (sizeof(stk::StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
  unsigned int bufferFrames = stk::RT_BUFFER_SIZE;
  if (dac.openStream(&parameters, NULL, format, (unsigned int)stk::Stk::sampleRate(),
                     &bufferFrames, &tick, (void *)&data)) {
    std::cout << dac.getErrorText() << std::endl;
    goto cleanup;
  }

  try {
    // Define and load the BeeThree instrument
    data.instrument = new stk::BeeThree();
  } catch (stk::StkError &) {
    goto cleanup;
  }

  data.frequency = 220.0;
  data.instrument->noteOn(data.frequency, 0.5);

  if (dac.startStream()) {
    std::cout << dac.getErrorText() << std::endl;
    goto cleanup;
  }

  // Block waiting until callback signals done.
  while (!data.done)
    stk::Stk::sleep(100);

  // Shut down the callback and output stream.
  dac.closeStream();

cleanup:
  delete data.instrument;

  return 0;
}