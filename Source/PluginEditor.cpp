
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PFMProject0AudioProcessorEditor::PFMProject0AudioProcessorEditor (PFMProject0AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    cashedBgColor = audioProcessor.bgColor->get();

    setSize (400, 300);
    
    startTimerHz(20);
}

PFMProject0AudioProcessorEditor::~PFMProject0AudioProcessorEditor()
{
    PFMProject0AudioProcessor::updateAutomatableParameter(audioProcessor.shouldPlaySound, false);
}

void PFMProject0AudioProcessorEditor::timerCallback()
{
    update();
}

void PFMProject0AudioProcessorEditor::update()
{
    cashedBgColor = audioProcessor.bgColor->get();
    repaint();
}
//==============================================================================
void PFMProject0AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId).interpolatedWith(juce::Colours::red, cashedBgColor));

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
    lastClickPos = e.getPosition();
}

void PFMProject0AudioProcessorEditor::mouseUp(const juce::MouseEvent& e)
{
    PFMProject0AudioProcessor::updateAutomatableParameter(audioProcessor.shouldPlaySound, !audioProcessor.shouldPlaySound->get());
}

void PFMProject0AudioProcessorEditor::mouseDrag(const juce::MouseEvent& e)
{
    auto clickPos = e.getPosition();
    
    auto difY = juce::jlimit(-1.0, 1.0, (clickPos.y - lastClickPos.y) / 200.0);
    difY = juce::jmap(difY, -1.0, 1.0, 0.0, 1.0);
    
    PFMProject0AudioProcessor::updateAutomatableParameter(audioProcessor.bgColor, difY);
    update();

}
