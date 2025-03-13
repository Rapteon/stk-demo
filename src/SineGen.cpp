#include "SineGen.h"
#include "Utility.h"
#include <stk/BeeThree.h>
#include <rtaudio/RtAudio.h>

SineGen::SineGen()
{
	parameters.deviceId = dac.getDefaultOutputDevice();
	parameters.nChannels = 2;

	RtAudioFormat format =
		(sizeof(stk::StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = stk::RT_BUFFER_SIZE;
	try
	{
		dac.openStream(&parameters, NULL, format,
					   static_cast<unsigned int>(stk::Stk::sampleRate()),
					   &bufferFrames, &(tick), (void *)&data);
	}
	catch (stk::StkError &)
	{
		// std::cout << dac.getErrorText() << std::endl;
		std::cout << "Error handling at line 19\n";
		throw "Could not opens stream\n";
	}

	try
	{
		data.instrument = new stk::BeeThree();
	}
	catch (stk::StkError &)
	{
		std::cout << "Could not initialise instrument.\n";
		throw "Could not initialise instrument.\n";
	}
	data.frequency = 220;
}

SineGen::~SineGen()
{
	dac.closeStream();
	delete data.instrument;
}
void SineGen::setFrequency(int frequency)
{
	data.frequency = frequency;
}

void SineGen::play(int nFrames)
{

	std::cout << "Playing now\n";

	std::cout << data.frequency << '\n';
	data.instrument->noteOn(data.frequency, 0.5);
	try
	{
		dac.startStream();
	}
	catch (stk::StkError &)
	{
		// std::cout << dac.getErrorText() << std::endl;
		std::cout << "Error handling at line 36.\n";
		return;
	}

	while (!data.done)
	{
		stk::Stk::sleep(100);
	}
	data.done = false;

	// Added this sleep here because closing the stream immediately meant
	// no audio would be played.
	// std::this_thread::sleep_for(std::chrono::milliseconds(250));

	try
	{
		dac.stopStream();
	}
	catch (stk::StkError &)
	{
		// std::cout << dac.getErrorText() << std::endl;
		std::cout << "Error handling at line 45.\n";
		return;
	}
}
