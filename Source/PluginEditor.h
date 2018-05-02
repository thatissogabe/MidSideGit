/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class MidSideGitAudioProcessorEditor : public AudioProcessorEditor,
	Slider::Listener,
	ComboBox::Listener,
	Timer
{
public:
    MidSideGitAudioProcessorEditor (MidSideGitAudioProcessor&);
    ~MidSideGitAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void timerCallback()override;

	void sliderValueChanged(Slider* sliderThatWasChanged) override;
	void comboBoxChanged(ComboBox* box) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidSideGitAudioProcessor& processor;

	ScopedPointer<Slider> knob1;
	ScopedPointer<Slider> knob2;
	ComboBox modeSelection;
	Label modeLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidSideGitAudioProcessorEditor)

	MidSideGitAudioProcessor& getProcessor() const
	{
		return static_cast<MidSideGitAudioProcessor&> (processor);
	}
};
