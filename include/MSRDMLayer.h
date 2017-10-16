/*
 * MSRDMLayer.h
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Network.h"

#ifndef MSRDMLAYER_H_
#define MSRDMLAYER_H_

class MSRDMLayer {
 public:
  MSRDMLayer();

  void get_MSRDM_output(Network& net, std::vector<double> input);
  void learn(std::vector<double> removeCase);
  void train(Network& myNet, std::vector<int> topology, Data& trainData);
  virtual ~MSRDMLayer();

};

#endif /* MSRDMLAYER_H_ */
