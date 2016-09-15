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

//[Headers] You can add your own extra header files here...
# define M_PI           3.14159265358979323846  /* pi */
#include "PluginEditor.h"

//[/Headers]

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FishTankAudioProcessorEditor::FishTankAudioProcessorEditor(FishTankAudioProcessor& owner)
	: AudioProcessorEditor(owner), processor(owner)
{
	//[Constructor_pre] You can add your own custom stuff here..
	//[/Constructor_pre]

	addAndMakeVisible (lowPassTitle = new Label ("new lowPassTitle",
												 TRANS("Low Pass Filter Settings\n")));
	lowPassTitle->setFont (Font (17.00f, Font::plain));
	lowPassTitle->setJustificationType (Justification::centredLeft);
	lowPassTitle->setEditable (false, false, false);
	lowPassTitle->setColour (TextEditor::textColourId, Colours::black);
	lowPassTitle->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

	addAndMakeVisible (lowPassSTSlider = new Slider ("new lowPassSTSlider"));
	lowPassSTSlider->setRange (0, 1000, 0);
	lowPassSTSlider->setSliderStyle (Slider::RotaryVerticalDrag);
	lowPassSTSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
	lowPassSTSlider->addListener (this);

	addAndMakeVisible (lowPassSTLabel = new Label ("new lowPassSTLabel",
												   TRANS("Smoothing Time")));
	lowPassSTLabel->setFont (Font (15.00f, Font::plain));
	lowPassSTLabel->setJustificationType (Justification::centredLeft);
	lowPassSTLabel->setEditable (false, false, false);
	lowPassSTLabel->setColour (TextEditor::textColourId, Colours::black);
	lowPassSTLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

	addAndMakeVisible (wetDrySlider = new Slider ("new wetDrySlider"));
	wetDrySlider->setTooltip (TRANS("This is how much the filter will be applied."));
	wetDrySlider->setRange (0, 100, 0);
	wetDrySlider->setSliderStyle (Slider::RotaryVerticalDrag);
	wetDrySlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
	wetDrySlider->addListener (this);

	addAndMakeVisible (wetDryLabel = new Label ("new wetDryLabel",
												TRANS("Wet/Dry")));
	wetDryLabel->setFont (Font (15.00f, Font::plain));
	wetDryLabel->setJustificationType (Justification::centredLeft);
	wetDryLabel->setEditable (false, false, false);
	wetDryLabel->setColour (TextEditor::textColourId, Colours::black);
	wetDryLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

	/* This doesn't have a listener.  Fix that eventually. */
	addAndMakeVisible (lowPassSampleRate = new TextEditor ("new lowPassSampleRate"));
	lowPassSampleRate->setTooltip (TRANS("Only change this if the sample rate is not being detected!"));
	lowPassSampleRate->setMultiLine (false);
	lowPassSampleRate->setReturnKeyStartsNewLine (false);
	lowPassSampleRate->setReadOnly (false);
	lowPassSampleRate->setScrollbarsShown (true);
	lowPassSampleRate->setCaretVisible (true);
	lowPassSampleRate->setPopupMenuEnabled (true);
	lowPassSampleRate->setText (TRANS("-1"));

	addAndMakeVisible (lowPassFRLabel = new Label ("new lowPassFRLabel",
												   TRANS("Sample Rate\n"
												   "(Optional)")));
	lowPassFRLabel->setFont (Font (15.00f, Font::plain));
	lowPassFRLabel->setJustificationType (Justification::centred);
	lowPassFRLabel->setEditable (false, false, false);
	lowPassFRLabel->setColour (TextEditor::textColourId, Colours::black);
	lowPassFRLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


	//[UserPreSize]
	//[/UserPreSize]


	//[Constructor] You can add your own custom stuff here..
	setSize(400, 200);
	setResizable(true, true);
	//setUsingNativeTitleBar(true);
	//[/Constructor]
}

FishTankAudioProcessorEditor::~FishTankAudioProcessorEditor()
{
	//[Destructor_pre]. You can add your own custom destruction code here..
	lowPassSTSlider->removeListener(this);
	wetDrySlider->removeListener(this);
	//lowPassSampleRate->removeListener(this);
	//[/Destructor_pre]

	lowPassTitle = nullptr;
	lowPassSTSlider = nullptr;
	lowPassSTLabel = nullptr;
	wetDrySlider = nullptr;
	wetDryLabel = nullptr;
	lowPassSampleRate = nullptr;
	lowPassFRLabel = nullptr;


	//[Destructor]. You can add your own custom destruction code here..
	//[/Destructor]
}

//==============================================================================
void FishTankAudioProcessorEditor::paint (Graphics& g)
{
	//[UserPrePaint] Add your own custom painting code here..
	//[/UserPrePaint]

	g.fillAll (Colours::white);

	g.setColour (Colours::lightblue);
	g.fillRoundedRectangle (4.0f, 4.0f, 368.0f, 124.0f, 10.000f);

	//[UserPaint] Add your own custom painting code here..
	//[/UserPaint]
}

void FishTankAudioProcessorEditor::resized()
{
	//[UserPreResize] Add your own custom resize code here..
	//[/UserPreResize]

	lowPassTitle->setBounds (88, 16, 184, 24);
	lowPassSTSlider->setBounds (16, 80, 112, 24);
	lowPassSTLabel->setBounds (16, 48, 120, 24);
	wetDrySlider->setBounds (160, 80, 112, 24);
	wetDryLabel->setBounds (168, 48, 72, 24);
	lowPassSampleRate->setBounds (296, 80, 64, 24);
	lowPassFRLabel->setBounds (280, 40, 96, 32);
	//[UserResized] Add your own custom resize handling here..
	//[/UserResized]
}

void FishTankAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
	//[UsersliderValueChanged_Pre]
	//[/UsersliderValueChanged_Pre]

	if (sliderThatWasMoved == lowPassSTSlider)
	{
		float a = lowPassSTSlider->getValue();
		processor.setLowPassSmoothingRate(lowPassSTSlider->getValue());
	}
	else if (sliderThatWasMoved == wetDrySlider)
	{
		processor.setWetDry(wetDrySlider->getValue());
	}

	//[UsersliderValueChanged_Post]
	//[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

	This is where the Projucer stores the metadata that describe this GUI layout, so
	make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
				 parentClasses="public AudioProcessorEditor" constructorParams="FishTankAudioProcessor&amp; owner"
				 variableInitialisers="AudioProcessorEditor(owner)" snapPixels="8"
				 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
				 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff">
	<ROUNDRECT pos="4 4 368 124" cornerSize="10" fill="solid: fffaffa1" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="new lowPassTitle" id="d1f79b13fcec08cb" memberName="lowPassTitle"
		 virtualName="" explicitFocusOrder="0" pos="88 16 184 24" edTextCol="ff000000"
		 edBkgCol="0" labelText="Low Pass Filter Settings&#10;" editableSingleClick="0"
		 editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
		 fontsize="17" bold="0" italic="0" justification="33"/>
  <SLIDER name="new lowPassSTSlider" id="a2d6a8bf0db8ebdb" memberName="lowPassSTSlider"
		  virtualName="" explicitFocusOrder="0" pos="16 80 112 24" min="0"
		  max="1000" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxLeft"
		  textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
		  needsCallback="1"/>
  <LABEL name="new lowPassSTLabel" id="65fb855692ffb814" memberName="lowPassSTLabel"
		 virtualName="" explicitFocusOrder="0" pos="16 48 120 24" edTextCol="ff000000"
		 edBkgCol="0" labelText="Smoothing Time" editableSingleClick="0"
		 editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
		 fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="new wetDrySlider" id="e22bde49cc2e4b22" memberName="wetDrySlider"
		  virtualName="" explicitFocusOrder="0" pos="160 80 112 24" tooltip="This is how much the filter will be applied."
		  min="0" max="100" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxLeft"
		  textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
		  needsCallback="1"/>
  <LABEL name="new wetDryLabel" id="3bad1ca41fe50de2" memberName="wetDryLabel"
		 virtualName="" explicitFocusOrder="0" pos="168 48 72 24" edTextCol="ff000000"
		 edBkgCol="0" labelText="Wet/Dry" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="15"
		 bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new lowPassSampleRate" id="feaaa18d48236eb4" memberName="lowPassSampleRate"
			  virtualName="" explicitFocusOrder="0" pos="296 80 64 24" tooltip="Only change this if the sample rate is not being detected!"
			  initialText="-1" multiline="0" retKeyStartsLine="0" readonly="0"
			  scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="new lowPassFRLabel" id="7b42c3ca5d446ab9" memberName="lowPassFRLabel"
		 virtualName="" explicitFocusOrder="0" pos="280 40 96 32" edTextCol="ff000000"
		 edBkgCol="0" labelText="Sample Rate&#10;(Optional)" editableSingleClick="0"
		 editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
		 fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
