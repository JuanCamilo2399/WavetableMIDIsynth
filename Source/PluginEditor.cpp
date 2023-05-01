/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WavetableSynthAudioProcessorEditor::WavetableSynthAudioProcessorEditor (WavetableSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
      
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 320);

    addAndMakeVisible(TypeWave);
    TypeWave.addItem("Sinusoidal", 1);
    TypeWave.addItem("Cuadrada", 2);
    TypeWave.addItem("Triangular", 3);
    TypeWave.addItem("Diente de sierra", 4);
    TypeWave.addItem("Nunis Onda", 5);

    TypeWave.onChange = [this]
    {
        switch (TypeWave.getSelectedId())
        {
        case 1:
            TypeWave.setSelectedId(1);
            audioProcessor.changeWaveform(TypeWave.getSelectedId());
            break;
        case 2:
            TypeWave.setSelectedId(2);
            audioProcessor.changeWaveform(TypeWave.getSelectedId());
            break;
        case 3:
            TypeWave.setSelectedId(3);
            audioProcessor.changeWaveform(TypeWave.getSelectedId());
            break;
        case 4:
            TypeWave.setSelectedId(4);
            audioProcessor.changeWaveform(TypeWave.getSelectedId());
            break;
        case 5:
            TypeWave.setSelectedId(5);
            audioProcessor.changeWaveform(TypeWave.getSelectedId());
            break;
        default:

            break;
        }
    };

    addAndMakeVisible(Gain);
    Gain.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    Gain.setRange(-96, 0);
    Gain.setSkewFactorFromMidPoint(-6);
    Gain.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::aqua);
    Gain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    Gain.onValueChange = [this]
    {
        audioProcessor.changeGain(juce::Decibels::decibelsToGain(Gain.getValue()));
    };

    addAndMakeVisible(gain);
    gain.setFont(juce::Font(16.0f));
    gain.setText("Gain", juce::dontSendNotification);
    gain.setColour(juce::Label::ColourIds::textColourId , juce::Colours::whitesmoke);
    gain.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(choose);
    choose.setFont(juce::Font(16.0f));
    choose.setText("Wave Type", juce::dontSendNotification);
    choose.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke);
    choose.setJustificationType(juce::Justification::centred);

    
    

}

WavetableSynthAudioProcessorEditor::~WavetableSynthAudioProcessorEditor()
{
}

//==============================================================================
void WavetableSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Wavetable", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);;
}

void WavetableSynthAudioProcessorEditor::resized()
{
    const auto paddingX = 50;
    const auto paddingY = 75;
    const auto paddingY2 = 235;
    const auto width = 100;
    const auto height = 100;
    const auto labelYoffset = 20;

    Gain.setBounds(paddingX, paddingY, width, height);
    gain.setBounds(Gain.getX(), paddingY - labelYoffset, width, 20);
    TypeWave.setBounds(paddingX, paddingY + 120, width, height / 4);
    choose.setBounds(TypeWave.getX(), paddingY + 120 - labelYoffset, width, 20);
}
