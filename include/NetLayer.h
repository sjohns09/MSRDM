/*
 * NetLayer.h
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
//#include "Neuron.h"

#ifndef NETLAYER_H_
#define NETLAYER_H_

class Neuron;

class NetLayer {
 public:
  NetLayer(double numNeurons);

  std::vector<Neuron> layer;

  virtual ~NetLayer();
};

#endif /* NETLAYER_H_ */
