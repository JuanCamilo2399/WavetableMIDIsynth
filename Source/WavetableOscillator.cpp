/*
  ==============================================================================

    WavetableOscillator.cpp
    Created: 21 Mar 2023 8:40:28pm
    Author:  JUAN CAMILO

  ==============================================================================
*/

#include "WavetableOscillator.h"

WavetableOscillator::WavetableOscillator(double SampleRate = 44100.0) :
SampleRate{ SampleRate }
{
    waveTable.resize(1024, 0);
    waveTable = getTypeWaveTable(1);
}

void WavetableOscillator::setFrequency(float frequency)
{
    // se genera el incremento en frecuencia con la formula de wavetable
    indexIncrement = frequency * static_cast<float>(waveTable.size()) / static_cast<float>(SampleRate);

}

// Interpolacion de muestras
float WavetableOscillator::WavetableInterLineal()
{

    auto tableSize = waveTable.size();

    auto index0 = (unsigned int)index;
    auto index1 = index0 == (tableSize - 1) ? (unsigned int)0 : index0 + 1;

    auto frac = index - (float)index0;

    auto sample = waveTable[index0] + frac * (waveTable[index1] - waveTable[index0]);

    return sample;

}
// Se toma la muestra interpolada
float WavetableOscillator::getSample()
{
    const auto sample = WavetableInterLineal();
    index += indexIncrement;
    index = std::fmod(index, static_cast<float>(waveTable.size()));

    return sample;
}


void WavetableOscillator::stop()
{
    index = 0.f;
    indexIncrement = 0.f;
}

bool WavetableOscillator::isplaying()
{
    return indexIncrement != 0.f;
}

std::vector<float> WavetableOscillator::getTypeWaveTable(int value)
{
    std::vector<float> newWaveTable;

    switch (value)
    {
    case 1: // seno
        for (int i = 0; i < waveTable.size(); ++i)
        {
            newWaveTable.push_back(std::sin(2.0 * juce::MathConstants<float>::pi * i / waveTable.size()));
        }
        break;

    case 2: // cuadrada
        for (int i = 0; i < waveTable.size(); ++i)
        {
            newWaveTable.push_back(i < waveTable.size() / 2 ? 1.0f : -1.0f);
        }
        break;

    case 3: // triangular
        for (int i = 0; i < waveTable.size(); ++i)
        {
            newWaveTable.push_back(i < waveTable.size() / 2 ? (-1.0f + 2.0f * i / waveTable.size()) : (1.0f - 2.0f * (i - waveTable.size() / 2) / waveTable.size()));
        }
        break;

    case 4: // diente de sierra
        for (int i = 0; i < waveTable.size(); ++i)
        {
            newWaveTable.push_back(-1.0f + 2.0f * i / waveTable.size());
        }
        break;

    case 5: // NunisWave
        for (int i = 0; i < waveTable.size(); ++i)
        {
            newWaveTable.push_back(std::sin(2.0 * juce::MathConstants<float>::pi * i / waveTable.size()) * (i % 10 == 0 ? 1.0f : 0.0f));
        }
        break;

    default: 
        newWaveTable = waveTable;
        break;
    }

    return newWaveTable;
}

void WavetableOscillator::setTypeWaveTable(int type)
{
    auto newTable = getTypeWaveTable(type);
    if (!newTable.empty())
    {
        waveTable = newTable;
        index = 0.f;
    }
        
}

void WavetableOscillator::setSampleRate(float newSampleRate)
{
    SampleRate = newSampleRate;
}


