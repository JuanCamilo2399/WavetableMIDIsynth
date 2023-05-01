/*
  ==============================================================================

    WavetableOscillator.h
    Created: 21 Mar 2023 8:40:28pm
    Author:  JUAN CAMILO

  ==============================================================================
*/

#pragma once
#include <juceheader.h>
#include <vector>
#include <cmath>
class WavetableOscillator
{
public:
    WavetableOscillator(double SampleRate);
    void setFrequency(float frequency); //Incremento
    float  WavetableInterLineal(); //Realizar Interpolacion linear
    float getSample(); // obtener la muestra de la tabla interpolada
    void stop(); //verificar si hay alguna nota sonando
    bool isplaying(); //Verificar si se esta reproduciendo el oscilador
    std::vector<float> getTypeWaveTable(const int value);
    void setTypeWaveTable(int type);
    void setSampleRate(float newSampleRate);

private:
    std::vector<float> waveTable;
    double SampleRate;
    float index = 0.f;
    float indexIncrement = 0.f;
};