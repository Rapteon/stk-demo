#include <stk/SineWave.h>
#include <stk/RtWvOut.h>
#include <cstdlib>
#include <stk/Stk.h>

void cleanup(stk::RtWvOut* dac) {
    delete dac;
}


int main() {
    stk::Stk::setSampleRate(44100.0);
    stk::Stk::showWarnings(true);

    constexpr int N_FRAMES {100'000};
    constexpr int N_CHANNELS {2};
    stk::SineWave sine;

    stk::RtWvOut *dac = 0;

    try {
        // Open default realtime output device for  1-channel playback.
        dac = new stk::RtWvOut(N_CHANNELS);
    }
    catch (stk::StkError &) {
        return EXIT_FAILURE;
    }

    sine.setFrequency(441);

    stk::StkFrames frames (N_FRAMES, N_CHANNELS);
    try {
        dac->tick(sine.tick(frames));
    }
    catch (stk::StkError &) {
        cleanup(dac);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
