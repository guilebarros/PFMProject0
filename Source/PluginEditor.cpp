
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PFMProject0AudioProcessorEditor::PFMProject0AudioProcessorEditor (PFMProject0AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

PFMProject0AudioProcessorEditor::~PFMProject0AudioProcessorEditor()
{
}

//==============================================================================
void PFMProject0AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void PFMProject0AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void PFMProject0AudioProcessorEditor::mouseDown(const juce::MouseEvent& e)
{
    //DBG ("mouse down");
//    audioProcessor.shouldPlaySound = true;
    
}
void PFMProject0AudioProcessorEditor::mouseUp(const juce::MouseEvent& e)
{
    if (audioProcessor.shouldPlaySound)
    {
        audioProcessor.shouldPlaySound = false;
    }
    else
    {
        audioProcessor.shouldPlaySound = true;
    }
}
