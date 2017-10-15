/*
 * Neuron.h
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
//#include "NetLayer.h"
#include "Network.h"

#ifndef APP_NEURON_H_
#define APP_NEURON_H_

typedef std::vector<Neuron> NetLayer;

class Neuron {
 public:
  Neuron(int numOutConnections, int index);
  void setOutValue (double value);
  double getOutValue ();
  void feed_forward (const NetLayer& preLayer);
  void get_out_gradients (double targetVal);
  void get_hidden_gradients (const NetLayer& nextLayer);
  void update_input_weights (NetLayer& preLayer);

  virtual ~Neuron();

private:
  struct Connections {
    double weight;
    double deltaWeight;
  };

  double initial_weight ();
  static double transferFunc (double x);
  static double transferFuncDX (double x);
  double outValue;
  std::vector<Connections> outWeights;
//  std::vector<double> deltaWeights;
  double gradient;
  int nIndex;
};

#endif /* APP_NEURON_H_ */
