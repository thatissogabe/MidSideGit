/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
using namespace std;


//==============================================================================
MidSideGitAudioProcessorEditor::MidSideGitAudioProcessorEditor (MidSideGitAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (250, 150);
	addAndMakeVisible(knob1 = new Slider("Knob - 1"));
	addAndMakeVisible(knob2 = new Slider("Knob - 2"));

	knob1->setRange(0.0, 1.0);
	knob1->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 15);
	knob1->setTextValueSuffix("");
	knob1->setSliderStyle(Slider::LinearHorizontal);
	knob1->setColour(Slider::rotarySliderFillColourId, Colours::grey);
	knob1->setColour(Slider::rotarySliderOutlineColourId, Colours::white);
	knob1->addListener(this);
	knob1->setBounds(25, 25, 200, 50);

	
	knob2->setRange(0, 1.5);
	knob2->setTextBoxStyle(Slider::TextBoxBelow, false, 60, 15);
	knob2->setTextValueSuffix(" %");
	knob2->setSliderStyle(Slider::LinearHorizontal);
	knob2->setColour(Slider::rotarySliderFillColourId, Colours::grey);
	knob2->setColour(Slider::rotarySliderOutlineColourId, Colours::white);
	knob2->addListener(this);
	knob2->setBounds(25, 75, 200, 50);

	startTimer(50);

	//==============================================================================

	// addAndMakeVisible(modeSelection);
	modeSelection.addListener(this);
	modeLabel.setText("Choose Mode", dontSendNotification);
	modeLabel.attachToComponent(&modeSelection, true);
	modeSelection.addItem("Mid-Side", 1);
	modeSelection.addItem("Mid", 2);
	modeSelection.addItem("Side", 3);
	modeSelection.addItem("Encoder", 4);
	modeSelection.setSelectedId(1);


}

MidSideGitAudioProcessorEditor::~MidSideGitAudioProcessorEditor()
{
	knob1 = nullptr;
	knob2 = nullptr;
	modeSelection.removeListener(this);
}

void MidSideGitAudioProcessorEditor::timerCallback()
{
	knob1->setValue(processor.getParameter(MidSideGitAudioProcessor::knob1Param), NotificationType::dontSendNotification);
	knob2->setValue(processor.getParameter(MidSideGitAudioProcessor::knob2Param), NotificationType::dontSendNotification);

}

void MidSideGitAudioProcessorEditor::sliderValueChanged(Slider* sliderThatWasChanged)
{
	if (sliderThatWasChanged == knob1)
	{
		processor.setParameterNotifyingHost(MidSideGitAudioProcessor::knob1Param, (float)knob1->getValue());
	}
	else if (sliderThatWasChanged == knob2)
	{
		processor.setParameterNotifyingHost(MidSideGitAudioProcessor::knob2Param, (float)knob2->getValue());
	}

}

void MidSideGitAudioProcessorEditor::comboBoxChanged(ComboBox* box)
{
	if (box == &modeSelection)
	{
		cout << modeSelection.getSelectedItemIndex();
		this->getProcessor().setModeType(modeSelection.getSelectedItemIndex());
		// 0 (None)
		// 1 (Lowpass)
		// 2 (Highpass)ee
		// 3 (Bandpass)
	}
}




//==============================================================================
void MidSideGitAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	g.drawText("Mid-Side Matrix", 25, 0, 200, 50, Justification::horizontallyCentred, 1);
	g.drawText("Mid", 25, 25, 200, 50, Justification::bottomLeft, 1);
	g.drawText("Side", 25, 75, 200, 50, Justification::bottomLeft, 1);
}

void MidSideGitAudioProcessorEditor::resized()
{
	
	// Rectangle<int> r(getLocalBounds().reduced(8));

	// Rectangle<int> filterArea(r.removeFromBottom(30));
	// modeSelection.setBounds(filterArea.removeFromLeft(100));
	// modeSelection.setBounds(filterArea.removeFromLeft(filterArea.getWidth()));
	// r.removeFromTop(10);
	
}
