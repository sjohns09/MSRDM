/*
 * Network.h
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
#include "Data.h"

#ifndef NETWORK_H_
#define NETWORK_H_

class Neuron;

typedef std::vector<Neuron> NetLayer;

class Network {
 public:
  Network();
  Network(int numInputs,int numOutputs,int numHiddenLayers, int numHiddenNeuron);


  void feed_forward (const std::vector<double>& inputs);
  void back_prop (const std::vector<double>& targets);
  void get_output (std::vector<double>& results);
  double get_recent_error() {return recentAverageError;}
  static void train(Network& net, std::vector<int> topology, Data& trainData);

  virtual ~Network();

 private:
   std::vector<NetLayer> layers;
   int numLayers;
   double errorRMS;
   int outputNum;
   int inputNum;
   int hiddenNum;
   double recentAverageError;
   double recentAverageSmoothingFactor;
};

#endif /* NETWORK_H_ */
