/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidSideGitAudioProcessor::MidSideGitAudioProcessor() : m_knob1(0),
m_knob2(0)

/* #ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
*/
{
	//*******************************************************

	m_mid = 0;
	m_side = 0;

	m_mid = m_knob1;
	m_side = m_knob2;

	//*******************************************************
}
MidSideGitAudioProcessor::~MidSideGitAudioProcessor()
{
}


//*******************************************************
float MidSideGitAudioProcessor::getParameter(int index)
{
	switch (index) {
	case knob1Param: return m_knob1;
	case knob2Param: return m_knob2;
	default: return 0.0;
	}
}

void MidSideGitAudioProcessor::setParameter(int index, float newValue)
{
	switch (index) {
	case knob1Param: 
		m_knob1 = newValue;
		m_mid = m_knob1;
		break;

	case knob2Param: 
		m_knob2 = newValue;
		m_side = m_knob2;
		break;

	default: break;
	}
}

const String MidSideGitAudioProcessor::getParameterName(int index)
{
	switch (index) {
	case knob1Param: return "Mid";
	case knob2Param: return "Side";
	default: return String::empty;
	}
}

const String MidSideGitAudioProcessor::getParameterText(int index)
{
	return String(getParameter(index), 2);
}

int MidSideGitAudioProcessor::getModeType()
{
	return this->modeType;
}

void MidSideGitAudioProcessor::setModeType(int type)
{
	this->modeType = type;
}

//*******************************************************

//==============================================================================
const String MidSideGitAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidSideGitAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidSideGitAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidSideGitAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidSideGitAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidSideGitAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidSideGitAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidSideGitAudioProcessor::setCurrentProgram (int index)
{
}

const String MidSideGitAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidSideGitAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidSideGitAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	m_mid = m_knob1;
	m_side = m_knob2;
}

void MidSideGitAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidSideGitAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MidSideGitAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


		
	processMatrix(buffer, m_mid, m_side);
	
		if (getModeType() == 1)
		{
			
			
		}
		// else if (getModeType() == 2)
		{
			// processMid(buffer, m_fCutoff, m_fGain);
			
		}
		// else if (getModeType() == 3)
		{
			// processSide(buffer, m_fCutoff, m_fGain);
		}	

	for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
		buffer.clear(i, 0, buffer.getNumSamples());
}
/*
void MidSideGitAudioProcessor::processMid(AudioSampleBuffer& buffer, float midGain, float sideGain) {
	const float* mid = buffer.getReadPointer(0);
	const float* side = buffer.getReadPointer(1);

	float* outL = buffer.getWritePointer(0);
	float* outR = buffer.getWritePointer(1);

	int blockSize = buffer.getNumSamples();

	float mGain = midGain;
	float sGain = midGain;

	for (int i = 0; i < blockSize; i++) {
		float newMid = mid[i] * mGain;
		float rootTwo = sqrt(2);
		outL[i] = newMid / rootTwo;
		outR[i] = newMid / rootTwo;
	}
}

void MidSideGitAudioProcessor::processSide(AudioSampleBuffer& buffer, float midGain, float sideGain) {
	const float* mid = buffer.getReadPointer(0);
	const float* side = buffer.getReadPointer(1);

	float* outL = buffer.getWritePointer(0);
	float* outR = buffer.getWritePointer(1);

	int blockSize = buffer.getNumSamples();

	float mGain = midGain;
	float sGain = sideGain;
	float iGain = sideGain * -1.0f;

	for (int i = 0; i < blockSize; i++) {
		float posSide = side[i] * sGain;
		float negSide = side[i] * iGain;
		float rootTwo = sqrt(2);
		outL[i] = posSide / rootTwo;
		outR[i] = negSide / rootTwo;
	}
}
*/
void MidSideGitAudioProcessor::processMatrix(AudioSampleBuffer& buffer, float midGain, float sideGain) {
	int blockSize = buffer.getNumSamples();
	
	float mGain = midGain;
	float sGain = sideGain;

	buffer.applyGain(0, 0, blockSize, mGain);
	buffer.applyGain(1, 0, blockSize, sGain);
	
	const float* mid = buffer.getReadPointer(0);
	const float* side = buffer.getReadPointer(1);

	float* outL = buffer.getWritePointer(0);
	float* outR = buffer.getWritePointer(1);


	for (int i = 0; i < blockSize; i++) {
		float posSide = side[i];
		float negSide = -side[i];
		float newMid = mid[i];
		float newLeft = newMid + posSide;
		float newRight =newMid + negSide;
		float rootTwo = sqrt(2);
		outL[i] = newLeft  / rootTwo;
		outR[i] = newRight / rootTwo;
	}
}



//==============================================================================
bool MidSideGitAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidSideGitAudioProcessor::createEditor()
{
    return new MidSideGitAudioProcessorEditor (*this);
}

//==============================================================================
void MidSideGitAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidSideGitAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidSideGitAudioProcessor();
}
