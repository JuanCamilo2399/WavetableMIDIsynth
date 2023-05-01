/*
  ==============================================================================

    SynthVoice.cpp
    Created: 21 Mar 2023 8:03:43pm
    Author:  JUAN CAMILO

  ==============================================================================
*/

#include "SynthVoice.h"

SynthVoice::SynthVoice():
    waveOsc(44100)
{
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*> (sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{

    waveOsc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    waveOsc.setTypeWaveTable(type);
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    if (allowTailOff) 
    {
        waveOsc.stop();
        clearCurrentNote();
    }
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    for (int sample = 0; sample < numSamples; ++sample)
    {
        auto SampleValue = waveOsc.getSample() * gain;

        for (int channel = 0; channel < outputBuffer.getNumChannels() ; ++channel)
        {
            outputBuffer.addSample(channel, startSample + sample, SampleValue);
        }
    }
}

void SynthVoice::changeGain(float newGain)
{
    gain = newGain;
}

void SynthVoice::changeWaveform(int nWaveForm)
{
    type = nWaveForm;
}


