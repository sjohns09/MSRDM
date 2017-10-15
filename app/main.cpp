#include <iostream>
#include <lib.hpp>
#include "Network.h"
#include "NetLayer.h"
#include "Neuron.h"
#include "Data.h"
#include "MSRDMLayer.h"
#include <vector>

using std::vector;

int main() {

  int numInputs, numOutputs, numHiddenLayers; // Taken from file
  vector<double> inputs, targets, results;

  numInputs = 3;
  numOutputs = 4;
  numHiddenLayers = 2;

  Network myNet(numInputs, numOutputs, numHiddenLayers);
  myNet.feed_forward(inputs);
//  myNet.back_prop(targets);
//  myNet.get_output(results);

  return 0;
}
