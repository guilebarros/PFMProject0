#pragma once

#include <JuceHeader.h>
//#include "PluginProcessor.h"

struct PFMProject0AudioProcessor;

class PFMProject0AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    PFMProject0AudioProcessorEditor (PFMProject0AudioProcessor&);
    ~PFMProject0AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void mouseDown(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;
    void mouseDrag(const juce::MouseEvent& e) override;
    
    void timerCallback() override;

private:
    void update();
    juce::Point<int> lastClickPos;

    PFMProject0AudioProcessor& audioProcessor;
    float cashedBgColor = 0.f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PFMProject0AudioProcessorEditor)
};
