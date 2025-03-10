#include "Utility.h"
#include <rtaudio/RtAudio.h>
#include <stk/SineWave.h>

// Bad practice to pass in void pointers according to the course spec.
// Also too many parameters in this function.
int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *dataPointer) {

  stk::SineWave *sine = (stk::SineWave *)dataPointer;
  stk::StkFloat *samples = (stk::StkFloat *)outputBuffer;

  for (unsigned int i = 0; i < nBufferFrames; i++)
    *samples++ = sine->tick();

  return 0;
}