/*
  ==============================================================================

    SynthVoice.h
    Created: 21 Mar 2023 8:03:43pm
    Author:  JUAN CAMILO

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Wavetableoscillator.h"
class SynthVoice : public juce::SynthesiserVoice 
{
public:
    SynthVoice();
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void changeGain(float newGain);
    void changeWaveform(int nWaveForm);
private:
    std::atomic<float> gain = 1.0f;
    int type = 1;
    WavetableOscillator waveOsc;
    
};