#ifndef SYNTHCONFIG_H
#define SYNTHCONFIG_H

#include <stk/Instrmnt.h>
#include <stk/Stk.h>
#include <rtaudio/RtAudio.h>

/*
Holds all class instances and data that are shared by
processing functions. This should be renamed
to SynthConfig.
*/
struct TickData
{
    TickData() : instrument{0}, scaler{1.0}, counter{0}, done{false} {}
    stk::Instrmnt *instrument;
    stk::StkFloat frequency;
    stk::StkFloat scaler;
    long counter;
    bool done;
};


// Bad practice to pass in void pointers according to the course spec.
// Also too many parameters in this function.
int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *dataPointer);
#endif