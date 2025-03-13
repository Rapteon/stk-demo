#include "SynthConfig.h"
#include <rtaudio/RtAudio.h>
#include <stk/SineWave.h>

// TODO: Refactor this method, if possible.
// Because it's bad practice to pass in void pointers.
// Also too many parameters in this function.
// Might need to support other types of instruments as well, so use
// this should set parameters of the data which are shared among
// instruments.
int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData)
{

    TickData *data = (TickData *)userData;
    stk::StkFloat *samples = (stk::StkFloat *)outputBuffer;

    for (unsigned int i = 0; i < nBufferFrames; i++)
    {
        *samples++ = data->instrument->tick();
        if (++data->counter % 2000 == 0)
        {
            data->scaler += 0.025;
            data->instrument->setFrequency(data->frequency * data->scaler);
        }
    }

    if (data->counter > 80000)
        data->done = true;

    return 0;
}