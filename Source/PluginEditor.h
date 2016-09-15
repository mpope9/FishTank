/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_F1B68972952BE4__
#define __JUCE_HEADER_F1B68972952BE4__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "../modules/juce_audio_processors/processors/juce_AudioProcessorEditor.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
																	//[Comments]
	An auto-generated component, created by the Projucer.

	Describe your class and how it works here!
																	//[/Comments]
*/
class FishTankAudioProcessorEditor : public AudioProcessorEditor,
					  public SliderListener
{
public:
	//==============================================================================
	FishTankAudioProcessorEditor (FishTankAudioProcessor& owner);
	~FishTankAudioProcessorEditor();

	//==============================================================================
	//[UserMethods]     -- You can add your own custom methods in this section.
	//[/UserMethods]

	void paint (Graphics& g) override;
	void resized() override;
	void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
	//[UserVariables]   -- You can add your own custom variables in this section.
	FishTankAudioProcessor& processor;
	//[/UserVariables]

	//==============================================================================
	ScopedPointer<Label> lowPassTitle;
	ScopedPointer<Slider> lowPassSTSlider;
	ScopedPointer<Label> lowPassSTLabel;
	ScopedPointer<Slider> wetDrySlider;
	ScopedPointer<Label> wetDryLabel;
	ScopedPointer<TextEditor> lowPassSampleRate;
	ScopedPointer<Label> lowPassFRLabel;


	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FishTankAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_F1B68972952BE4__
