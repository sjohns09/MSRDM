/*
 * Neuron.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
#include <cmath>
#include "NetLayer.h"
#include "Neuron.h"

Neuron::Neuron(int numOutConnections, int index) {

  for (int conn = 0; conn < numOutConnections; conn++) {
    outWeights.push_back(Connections());

    outWeights.back().weight = initial_weight();
  }
  nIndex = index;
  std::cout << numOutConnections << std::endl;
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

void Neuron::feed_forward(NetLayer preLayer) {
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
  return 1-(pow(tanh(x),2)); // or 1.0 - x*x
}

Neuron::~Neuron() {
  // TODO Auto-generated destructor stub
}

