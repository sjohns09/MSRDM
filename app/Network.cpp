/*
 * Network.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
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

Network::Network(int numInputs, int numOutputs, int numHiddenLayers, int numHiddenNeuron) {
  numLayers = numHiddenLayers + 2;  //Hidden Layers + In and Out Layer
  outputNum = numOutputs + 1; // includes bias neuron
  inputNum = numInputs + 1; //includes bias neuron
  hiddenNum = numHiddenNeuron + 1; //includes bias neuron
  int numOutConnections;

  for (int layerNum = 0; layerNum < numLayers; layerNum++) {
    layers.push_back(NetLayer());
    cout << "New Layer!" << endl;


    if (layerNum < numLayers-2)
      numOutConnections = hiddenNum;
    else if (layerNum == numLayers-2)
      numOutConnections = outputNum;
    else
      numOutConnections = 0;

    if (layerNum != numLayers - 1 && layerNum != 0) { //Hidden
      for (int i = 0; i < hiddenNum; i++) {
        layers[layerNum].push_back(Neuron(numOutConnections, i));
        cout << "Neuron" << endl;
      }
    } else if (layerNum == 0) { //input
      for (int i = 0; i < inputNum; i++) {
        layers[layerNum].push_back(Neuron(numOutConnections, i));
        cout << "Neuron" << endl;
      }
    }
    else { //output
      for (int i = 0; i < outputNum; i++) {
        layers[layerNum].push_back(Neuron(numOutConnections, i));
        cout << "Neuron" << endl;
      }
    }
    // Bias Neuron constant output of 1.0
    layers.back().back().setOutValue(1.0);
  }
  errorRMS = 0.0;
  recentAverageSmoothingFactor = 100.0;
  recentAverageError = 0;
}

void Network::feed_forward(const vector<double>& inputs) {
  int i =0;
  for (auto input : inputs) {
    layers[0][i].setOutValue(input); //Set rand input weights to input layer
    i++;
  }

  // Loop through each layer - then loop through each neuron and feed forward
  for (int layerNum = 1; layerNum < numLayers; layerNum++) {
    NetLayer& preLayer = layers[layerNum-1];
    for (int n = 0; n < layers[layerNum].size()-1; n++) {
      layers[layerNum][n].feed_forward(preLayer);
    }
  }
}

void Network::back_prop (const std::vector<double>& targets) {
  NetLayer& outputLayer = layers.back();
  errorRMS = 0.0;

  //Get RMS error
  for (int n = 0; n < outputNum-1; n++) {
    double delta = targets[n]-outputLayer[n].getOutValue();
    errorRMS += pow(delta,2);
  }
  errorRMS = sqrt((1/(outputNum-1))*errorRMS);

  //Get Recent Error
  recentAverageError =
        (recentAverageError * recentAverageSmoothingFactor + errorRMS)
  / (recentAverageSmoothingFactor + 1.0);

  // Get output layer gradients
  for (int n = 0; n < outputNum-1; n++) {
    outputLayer[n].get_out_gradients(targets[n]);
  }

  // Get hidden layer gradients
  int rightHiddenIndex = numLayers-2;
  for (int l = rightHiddenIndex; l > 0; l--) {
    for (int n = 0; n < hiddenNum; n++) {
      layers[l][n].get_hidden_gradients(layers[l+1]);
    }
  }

  // Update connection weights (not input layer)
  for (int l = numLayers-1; l > 0; l--){
    for (int n = 0; n < layers[l].size()-1; n++) {
      layers[l][n].update_input_weights(layers[l-1]);

    }
  }
}

void Network::get_output(std::vector<double>& results) {
  results.clear();

  for (int i = 0; i < outputNum -1; i++) {
    results.push_back(layers.back()[i].getOutValue());
  }
}

void Network::train(Network& myNet, vector<int> topology, Data& trainData) {

    vector<double> inputVals, targetVals, resultVals;
    int trainingPass = 0;
    while(!trainData.isEof())
    {
      ++trainingPass;
      cout << endl << "Pass" << trainingPass;

      // Get new input data and feed it forward:
      inputVals = trainData.get_next_inputs();
      if(inputVals.size() != topology[0])
        break;
      Data::show_vector_vals(": Inputs :", inputVals);
      myNet.feed_forward(inputVals);

      // Collect the net's actual results:
      myNet.get_output(resultVals);
      Data::show_vector_vals("Outputs:", resultVals);

      // Train the net what the outputs should have been:
      targetVals = trainData.get_target_outputs();
      Data::show_vector_vals("Targets:", targetVals);
      assert(targetVals.size() == topology[1]);

      myNet.back_prop(targetVals);

      // Report how well the training is working, average over recent
      cout << "Net recent average error: "
           << myNet.get_recent_error() << endl;
    }

  cout << endl << "Done Training" << endl;
}

Network::~Network()
{
  // TODO Auto-generated destructor stub
}

