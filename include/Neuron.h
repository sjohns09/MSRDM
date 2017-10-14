/*
 * Neuron.h
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
#include "NetLayer.h"

#ifndef APP_NEURON_H_
#define APP_NEURON_H_

class Neuron {
 public:
  Neuron(double nextLayerNeurons);
  void setOutValue (double value);
  double getOutValue ();
  void feed_forward (NetLayer preLayer);
  void get_out_gradients (double targetVal);
  void get_hidden_gradients (NetLayer nextLayer);

  virtual ~Neuron();

private:
  double initial_weight ();
  double transferFunc (double x);
  double transferFuncDX (double x);
  double outValue;
  std::vector<double> outWeights;
  std::vector<double> deltaWeights;
  double gradient;
  int nIndex;


};

#endif /* APP_NEURON_H_ */
