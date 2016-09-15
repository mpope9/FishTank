/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#define _USE_MATH_DEFINES
#include <math.h>

//==============================================================================
FishTankAudioProcessor::FishTankAudioProcessor()
{
	// If the sample rate cannot be found, set it to 44.1 kHz; its the most common.
	// Add functionality for sending a message to the user somehow, stating so.
	float aExp;
	float sampRate = AudioProcessor::getSampleRate();

	/*
	// Okay, funny guy.  Fix this when you get everything working with floats fist.

	// Get rid of this when you figure out how to fix the getSampleRate.
	//addParameter(m_sampleRate = new juce::AudioParameterFloat("m_sampleRate", "Sample Rate", 0.0f, 1000.0f, sampRate));
	addParameter(m_sampleRate = new juce::AudioParameterFloat("m_sampleRate", "Sample Rate", 0.0f, 1000.0f, 44.1f));
	addParameter(m_wetDry = new juce::AudioParameterFloat("m_wetDry", "Wet/Dry", 0.0f, 100.0f, 0.0f));
	addParameter(m_lowPassSmoothingRate = new juce::AudioParameterFloat("m_lowPassSmoothingRate", "Smoothing Rate", 1.0f, 1000.0f, 100.0f));
	addParameter(m_a = new juce::AudioParameterFloat("m_a", "a", -100.0f, 100.0f, 0.0f));
	addParameter(m_b = new juce::AudioParameterFloat("m_b", "b", -1.0f, 1.0f, 1.0f - m_a->get()));
	m_c = 0.0f;
	*/
	m_sampleRate = 44.1f;
	m_wetDry = 0.0f;
	m_lowPassSmoothingRate = 100.0f;
	m_a = 0.0f;
	m_b = 0.0f;
	m_c = 0;
}

FishTankAudioProcessor::~FishTankAudioProcessor()
{
}

//==============================================================================


const String FishTankAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool FishTankAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
	return true;
   #else
	return false;
   #endif
}

bool FishTankAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
	return true;
   #else
	return false;
   #endif
}

double FishTankAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int FishTankAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int FishTankAudioProcessor::getCurrentProgram()
{
	return 0;
}

void FishTankAudioProcessor::setCurrentProgram (int index)
{
}

const String FishTankAudioProcessor::getProgramName (int index)
{
	return String();
}

void FishTankAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FishTankAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void FishTankAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FishTankAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
	// Reject any bus arrangements that are not compatible with your plugin

	const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
	if (numChannels != 0)
		return false;
   #elif JucePlugin_IsSynth
	if (isInput || (numChannels != 1 && numChannels != 2))
		return false;
   #else
	if (numChannels != 1 && numChannels != 2)
		return false;

	if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
		return false;
   #endif

	return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

float FishTankAudioProcessor::calculate(float input)
{
	float test = m_sampleRate;

	float aExp = (-2 * M_PI) / (m_lowPassSmoothingRate * 1000.0f * m_sampleRate);
	m_a = exp(aExp);
	m_b = 1.0f - m_a;
	m_c = (input * m_b) + (m_c * m_a);
	return m_c;
}

/*
 * This is where the audio processing happens.  Right now all there is is
 * a low pass filter that is applied across all channels and samples evenly.
 * TODO: Impliment a "spike" at 500kHz.
 *       Make the spike adjustable by the user.
 *       Toss in the chorus/flanger.
*/
void FishTankAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	const int totalNumInputChannels  = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();

	// If it ever becomes the point that there are more ouputs then inputs,
	// Then regenerate this file, and see what they did for that sitch :)

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...

	// Set up variables
	float sample = 0;
	float newVal = 0;

	AudioSampleBuffer mainInputOutput = busArrangement.getBusBuffer(buffer, true, 0);

	float sr = m_sampleRate;

	for (int chan = 0; chan < mainInputOutput.getNumChannels(); chan++)
	{
		for (int samp = 0; samp < mainInputOutput.getNumSamples(); samp++)
		{
			// Test values
			float testReadPointer = *mainInputOutput.getReadPointer(chan, samp);
			float testValue = calculate(*mainInputOutput.getReadPointer(chan, samp));

			// Actual code.
			*mainInputOutput.getWritePointer(chan, samp) = calculate(*mainInputOutput.getReadPointer(chan, samp));
		}
	}

}

//==============================================================================
bool FishTankAudioProcessor::hasEditor() const
{
	return true;
}

AudioProcessorEditor* FishTankAudioProcessor::createEditor()
{
	return new FishTankAudioProcessorEditor (*this);
}

//==============================================================================
void FishTankAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	/*
	MemoryOutputStream(destData, true).writeFloat(*m_sampleRate);
	MemoryOutputStream(destData, true).writeFloat(*m_lowPassSmoothingRate);
	MemoryOutputStream(destData, true).writeFloat(*m_wetDry);
	MemoryOutputStream(destData, true).writeFloat(*m_a);
	MemoryOutputStream(destData, true).writeFloat(*m_b);
	*/
}

void FishTankAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	/*
	// This is for when you can be a big boy
	m_sampleRate->setValueNotifyingHost(MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat());
	m_lowPassSmoothingRate->setValueNotifyingHost(MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat());
	m_wetDry->setValueNotifyingHost(MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat());
	m_a->setValueNotifyingHost(MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat());
	m_b->setValueNotifyingHost(MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat());
	*/
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new FishTankAudioProcessor();
}

/*
* Function to get the Low Pass Smoothing Rate
*/
float FishTankAudioProcessor::getLowPassSmoothingRate()
{
	//return m_lowPassSmoothingRate->get();
	return m_lowPassSmoothingRate;
}

/*
 * Function to set the Low Pass Smoothing Rate
*/
void FishTankAudioProcessor::setLowPassSmoothingRate(float lpsm)
{
	m_lowPassSmoothingRate = (lpsm);
}

/*
* Function to get the sample rate.
*/
float FishTankAudioProcessor::getSampleRate()
{
	//return m_sampleRate->get();
	return m_sampleRate;
}

/*
 * Function to set the sample rate, if it is not detected
*/

void FishTankAudioProcessor::setSampleRate(float ssr)
{
	m_sampleRate = (ssr);
}

/*
* Method to get the Wet/Dry ratio
* Should I make the ratio here??
*/
float FishTankAudioProcessor::getWetDry()
{
	//return m_wetDry->get();
	return m_wetDry;
}

/*
 * Method to set the Wet/Dry ratio
 */
void FishTankAudioProcessor::setWetDry(float swd)
{
	m_wetDry = (swd);
}

/*
 * Method to get a, an element of the low pass filter.
 */
float FishTankAudioProcessor::getA() {
	//return m_a->get();
	return m_a;
}

/*
 * Method to set a.
 */
void FishTankAudioProcessor::setA(float a)
{
	m_a = (a);
}

/*
 * Method to get b, an element of the low pass filter.
 */
float FishTankAudioProcessor::getB()
{
	//return m_b->get();
	return m_b;
}

/*
 * Method to set b.
 */
void FishTankAudioProcessor::setB(float b)
{
	m_b = (b);
}

/*
 * Method to get c, an element of the low pass filter.
 */
float FishTankAudioProcessor::getC()
{
	//return m_c;
	return m_c;
}

/*
 * Method to set c.
 */
void FishTankAudioProcessor::setC(float c) {
	m_c = c;
}