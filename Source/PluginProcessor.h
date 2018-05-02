/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class MidSideGitAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MidSideGitAudioProcessor();
    ~MidSideGitAudioProcessor();

	//*******************************************************
	float getParameter(int index);
	void setParameter(int index, float newValue);
	const String getParameterName(int index);
	const String getParameterText(int index);

	int getModeType();
	void setModeType(int type);

	//*******************************************************
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

	void processMatrix(AudioSampleBuffer& buffer, float midGain, float sideGain);
	// void processMid(AudioSampleBuffer& buffer, float midGain, float sideGain);
	// void processSide(AudioSampleBuffer& buffer, float midGain, float sideGain);
	
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	enum Parameters {
		knob1Param,
		knob2Param
	};

	float m_mid;
	float m_side;


private:
    //==============================================================================


	//*******************************************************
	float m_knob1;
	float m_knob2;


	int modeType;
	//*******************************************************
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidSideGitAudioProcessor)
};
