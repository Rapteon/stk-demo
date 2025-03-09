#include <cstdlib>
#include <iostream>
#include <stk/Noise.h>
#include <stk/Stk.h>

int main() {
  stk::StkFloat output;
  stk::Noise noise;

  for (unsigned int i{0}; i < 20; ++i) {
    // In STK, processing or production of values is produced on a per-sample
    // basis. Most classes have a tick() method which is used for taking or
    // returning samples.
    output = noise.tick();
    std::cout << "i = " << i << " : output = " << output << '\n';
  }

  std::cout << "Calling tick() with StkFrames, a vector type usage.\n";

  stk::StkFrames frames_output(20, 1); // Number of frames, number of channels

  noise.tick(frames_output);

  for (int i{0}; i < frames_output.size(); ++i) {
    std::cout << "i = " << i << " : output = " << frames_output[i] << '\n';
  }

  /**
  Other classes which might be useful.

  stk::Generator: source signal unit generator classes [stk::Envelope,
  stk::ADSR, stk::Asymp, stk::Noise, stk::SubNoise, stk::Modulate,
  stk::SingWave, stk::SineWave, stk::Blit, stk::BlitSaw, stk::BlitSquare,
  stk::Granulate] stk::Filter: digital filtering classes [stk::OneZero,
  stk::OnePole, stk::PoleZero, stk::TwoZero, stk::TwoPole, stk::BiQuad,
  stk::FormSwep, stk::Delay, stk::DelayL, stk::DelayA, stk::TapDelay]
  stk::Function: input to output function mappings [stk::BowTable,
  stk::JetTable, stk::ReedTable] stk::Instrmnt: sound synthesis algorithms,
  including physical, FM, modal, and particle models stk::Effect: sound
  processing effect classes [stk::Echo, stk::Chorus, stk::PitShift, stk::PRCRev,
  stk::JCRev, stk::NRev] stk::WvOut: audio data output classes [stk::FileWvOut,
  stk::RtWvOut, stk::InetWvOut] stk::WvIn: audio data input classes
  [stk::FileWvIn, stk::FileLoop, stk::RtWvIn, stk::InetWvIn]
   */

  return EXIT_SUCCESS;
}