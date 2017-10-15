/*
 * Network.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
//#include "NetLayer.h"
#include "Network.h"
#include "Neuron.h"

using std::vector;
using std::cout;
using std::endl;

Network::Network(int numInputs, int numOutputs, int numHiddenLayers) {
  numLayers = numHiddenLayers + 2;  //Hidden Layers + In and Out Layer
  int numOutConnections;

  for (int layerNum = 0; layerNum < numLayers; layerNum++) {
    layers.push_back(NetLayer());
    cout << "New Layer!" << endl;

    if (layerNum < numLayers-2)
      numOutConnections = numInputs+1;
    else if (layerNum == numLayers-2)
      numOutConnections = numOutputs+1;
    else
      numOutConnections = 0;

    if (layerNum != numLayers - 1) {
      for (int i = 0; i <= numInputs; i++) {
        layers[layerNum].push_back(Neuron(numOutConnections, i));
        cout << "Neuron" << endl;
      }
    } else {
      for (int i = 0; i <= numOutputs; i++) {
        layers[layerNum].push_back(Neuron(numOutConnections, i));
        cout << "Neuron" << endl;
      }
    }
  }

  error = 0;
}

void Network::feed_forward(const vector<double>& inputs) {
  int i =0;
  for (auto input : inputs) {
    layers[0][i].setOutValue(input); //Set random input weights to input layer
    i++;
  }

  // Loop through each layer - then loop through each neuron and feed forward
  for (int layerNum = 1; layerNum < numLayers; layerNum++) {
    NetLayer preLayer = layers[layerNum-1];
    for (int n = 0; n < layers[layerNum].size(); n++) {
      layers[layerNum][n].feed_forward(preLayer);
    }
  }
}

Network::~Network()
{
  // TODO Auto-generated destructor stub
}

