/** @file Network.cpp
 * @brief This class utilizes the functionality of the network of a Neural Net
 *
 * @author Samantha Johnson
 * @date October 17, 2017
 * @copyright [2017] <Samantha Johnson>
 *
 * @details Represents the network of a neural net and performs the looping and processing
 * necessary to train the network and get results from it.
 *
 * This class utilized the training video by David Miller (https://vimeo.com/19569529)
 * called "Neural Net in C++ Tutorial", to develop the neural net framework.
 * All code was written by the author of this document.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "Network.h"
#include "Neuron.h"
#include "Data.h"

using std::vector;
using std::cout;
using std::endl;

Network::Network(int numInputs, int numOutputs, int numHiddenLayers,
                 int numHiddenNeuron) {
  numLayers = numHiddenLayers + 2;  // Hidden Layers + In and Out Layer
  outputNum = numOutputs + 1;  // includes bias neuron
  inputNum = numInputs + 1;  // includes bias neuron
  hiddenNum = numHiddenNeuron + 1;  // includes bias neuron
  int numOutConnections;

  for (int layerNum = 0; layerNum < numLayers; layerNum++) {
    layers.push_back(NetLayer());

    if (layerNum < numLayers - 2)
      numOutConnections = hiddenNum;
    else if (layerNum == numLayers - 2)
      numOutConnections = outputNum;
    else
      numOutConnections = 0;

    if (layerNum != numLayers - 1 && layerNum != 0) {  // Hidden
      for (int i = 0; i < hiddenNum; i++) {
        layers[layerNum].push_back(Neuron(numOutConnections, i));
      }
    } else if (layerNum == 0) {  // input
      for (int i = 0; i < inputNum; i++) {
        layers[layerNum].push_back(Neuron(numOutConnections, i));
      }
    } else {  // output
      for (int i = 0; i < outputNum; i++) {
        layers[layerNum].push_back(Neuron(numOutConnections, i));
      }
    }
    // Bias Neuron constant output of 1.0
    layers.back().back().setOutValue(1.0);
  }
  errorRMS = 0.0;
}

void Network::feed_forward(const vector<double>& inputs) {
  int i = 0;
  for (auto input : inputs) {
    layers[0][i].setOutValue(input);  // Set rand input weights to input layer
    i++;
  }

  // Loop through each layer - then loop through each neuron and feed forward
  for (int layerNum = 1; layerNum < numLayers; layerNum++) {
    NetLayer& preLayer = layers[layerNum - 1];
    for (int n = 0; n < layers[layerNum].size() - 1; n++) {
      layers[layerNum][n].feed_forward(preLayer);
    }
  }
}

void Network::back_prop(const std::vector<double>& targets) {
  NetLayer& outputLayer = layers.back();
  errorRMS = 0.0;

  // Get RMS error
  for (int n = 0; n < outputNum - 1; n++) {
    double delta = targets[n] - outputLayer[n].getOutValue();
    errorRMS += pow(delta, 2);
  }
  errorRMS = sqrt((1 / (outputNum - 1)) * errorRMS);

  // Get output layer gradients
  for (int n = 0; n < outputNum - 1; n++) {
    outputLayer[n].get_out_gradients(targets[n]);
  }

  // Get hidden layer gradients
  int rightHiddenIndex = numLayers - 2;
  for (int l = rightHiddenIndex; l > 0; l--) {
    for (int n = 0; n < hiddenNum; n++) {
      layers[l][n].get_hidden_gradients(layers[l + 1]);
    }
  }

  // Update connection weights (not input layer)
  for (int l = numLayers - 1; l > 0; l--) {
    for (int n = 0; n < layers[l].size() - 1; n++) {
      layers[l][n].update_input_weights(layers[l - 1]);

    }
  }
}

void Network::get_output(std::vector<double>& results) {
  results.clear();

  for (int i = 0; i < outputNum - 1; i++) {
    results.push_back(layers.back()[i].getOutValue());
  }
}

Network::~Network() {
  // TODO Auto-generated destructor stub
}

