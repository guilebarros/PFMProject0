#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PFMProject0AudioProcessor::PFMProject0AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
apvts(*this, nullptr)
{

    auto shouldPlaySoundParam = std::make_unique<juce::AudioParameterBool>("ShouldPlaySoundParam", "ShouldPlaySound", false);
    
    auto* param = apvts.createAndAddParameter(std::move(shouldPlaySoundParam));
    
    shouldPlaySound = dynamic_cast<juce::AudioParameterBool*> ( param );
    
    auto bgColorParam = std::make_unique<juce::AudioParameterFloat>("Background color", "background color", 0.f, 1.f, 0.5f);
    
    param = apvts.createAndAddParameter(std::move(bgColorParam));
    
    bgColor = dynamic_cast<juce::AudioParameterFloat*>(param);
    
    apvts.state = juce::ValueTree("PFMSynthValueTree");
    
}

PFMProject0AudioProcessor::~PFMProject0AudioProcessor()
{
    
}

//==============================================================================
const juce::String PFMProject0AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PFMProject0AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PFMProject0AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PFMProject0AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PFMProject0AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PFMProject0AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PFMProject0AudioProcessor::getCurrentProgram()
{
    return 0;
}

void PFMProject0AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PFMProject0AudioProcessor::getProgramName (int index)
{
    return {};
}

void PFMProject0AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PFMProject0AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PFMProject0AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PFMProject0AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void PFMProject0AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); channel++)
        {
            if ( shouldPlaySound->get() )
            {
                buffer.setSample(channel, i, r.nextFloat());
            } else
            {
                buffer.setSample(channel, i, 0);
            }
        }
    }
}

//==============================================================================
bool PFMProject0AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PFMProject0AudioProcessor::createEditor()
{
    return new PFMProject0AudioProcessorEditor (*this);
}

//==============================================================================
void PFMProject0AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos(destData, false);
    apvts.state.writeToStream(mos);
}

void PFMProject0AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ValueTree tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if( tree.isValid() )
    {
        apvts.state = tree;
    }
}

void PFMProject0AudioProcessor::updateAutomatableParameter(juce::RangedAudioParameter* param, float value)
{
    // grava os gestos na automacao da DAW, feitas pelo mouse do usuario
    param->beginChangeGesture();
    param->setValueNotifyingHost(value);
    param->endChangeGesture();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PFMProject0AudioProcessor();
}
