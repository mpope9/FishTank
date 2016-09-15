/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "../modules/juce_audio_processors/utilities/juce_AudioParameterFloat.h"

//==============================================================================
/**
*/
class FishTankAudioProcessor  : public AudioProcessor
{
public:
	//==============================================================================
	FishTankAudioProcessor();
	~FishTankAudioProcessor();

	//==============================================================================
	void prepareToPlay (double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
	bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

	void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

	//==============================================================================
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram (int index) override;
	const String getProgramName (int index) override;
	void changeProgramName (int index, const String& newName) override;

	//==============================================================================
	void getStateInformation (MemoryBlock& destData) override;
	void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================
	/* My Methods */
	float  calculate(float input);
	void  setLowPassSmoothingRate(float lpsm);
	float getLowPassSmoothingRate();
	void  setSampleRate(float ssr);
	float getSampleRate();
	void  setWetDry(float swd);
	float getWetDry();
	float getA();
	void setA(float a);
	float getB();
	void setB(float b);
	float getC();
	void setC(float c);

private:

	/*
	// I thought that I was all cool and could use all this jazz.
	// Think again, hot shot.  You'll get it eventually.
	juce::AudioParameterFloat* m_a;
	juce::AudioParameterFloat* m_b;
	float m_c;
	juce::AudioParameterFloat* m_lowPassSmoothingRate;
	juce::AudioParameterFloat* m_sampleRate;
	juce::AudioParameterFloat* m_wetDry;
	*/
	float m_a;
	float m_b;
	float m_c;
	float m_lowPassSmoothingRate;
	float m_sampleRate;
	float m_wetDry;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FishTankAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
