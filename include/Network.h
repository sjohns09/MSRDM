/*
 * Network.h
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
#include "NetLayer.h"

#ifndef NETWORK_H_
#define NETWORK_H_

class Network {
 public:
  Network(int numInputs,int numOutputs,int numHidden);

  void feed_forward (std::vector<double> inputs);
  void back_prop (std::vector<double> targets);
  void get_output (std::vector<double> results);

  virtual ~Network();

 private:
   std::vector<NetLayer> layers;
   double error;
};

#endif /* NETWORK_H_ */
