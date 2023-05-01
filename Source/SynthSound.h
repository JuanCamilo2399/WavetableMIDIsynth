/*
  ==============================================================================

    SynthSound.h
    Created: 21 Mar 2023 8:03:55pm
    Author:  JUAN CAMILO

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midichannel) override { return true; }
    
};