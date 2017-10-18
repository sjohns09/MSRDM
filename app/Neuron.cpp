/*
 * Neuron.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
#include <cmath>
#include "Neuron.h"

double eta = 0.15;
double alpha = 0.5;

Neuron::Neuron(int numOutConnections, int index) {

  for (int conn = 0; conn < numOutConnections; conn++) {
    outWeights.push_back(Connections());

    outWeights.back().weight = initial_weight();
  }
  nIndex = index;

}

double Neuron::initial_weight() {
  return rand()/double(RAND_MAX);
}

void Neuron::setOutValue(double value) {
  outValue = value;
}

double Neuron::getOutValue() {
  return outValue;
}

void Neuron::feed_forward(const NetLayer& preLayer) {
  double sum = 0.0;
  for (auto neuron : preLayer) {
    sum += neuron.getOutValue()*neuron.outWeights[nIndex].weight;
  }

  outValue = transferFunc(sum);
}

double Neuron::transferFunc(double x) {
  return tanh(x);
}

double Neuron::transferFuncDX(double x) {
  return 1.0 - x*x; //1-(pow(tanh(x),2)) // or 1.0 - x*x
}

void Neuron::get_out_gradients(double targetVal) {
  double delta = targetVal - outValue;
  gradient = delta * transferFuncDX(outValue);
}

void Neuron::get_hidden_gradients(const NetLayer& nextLayer) {
  double sum = 0.0;
  for (int n = 0; n < nextLayer.size()-1; n++) {
    sum += outWeights[n].weight * nextLayer[n].gradient;
  }
  gradient = sum * transferFuncDX(outValue);
}

void Neuron::update_input_weights(NetLayer& preLayer) {
  for (int n = 0; n < preLayer.size(); n++) {
    Neuron& preNeuron = preLayer[n];
    double oldDWeight = preNeuron.outWeights[nIndex].deltaWeight;

    double newDWeight = eta * preNeuron.getOutValue() * gradient
        + alpha * oldDWeight;

    preNeuron.outWeights[nIndex].deltaWeight = newDWeight;
    preNeuron.outWeights[nIndex].weight += newDWeight;
  }
}

Neuron::~Neuron() {
  // TODO Auto-generated destructor stub
}

