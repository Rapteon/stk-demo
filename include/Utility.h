#ifndef UTILITY_H
#define UTILITY_H

#include <rtaudio/RtAudio.h>

// Bad practice to pass in void pointers according to the course spec.
// Also too many parameters in this function.
int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *dataPointer);

#endif