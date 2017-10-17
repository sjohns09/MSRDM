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

  static std::vector<double> get_MSRDM_output(Network& netState, Network& netAction, std::vector<double> input);
  void learn(std::vector<double> removeCase);
  void train(Network& myNet, std::vector<int> topology, Data& trainData);
  static std::string interpret_results(const std::vector<double> resultVector, int layerNum, std::vector<int>& result);
  static void result_satisfaction(int satisfied);
  virtual ~MSRDMLayer();

};

#endif /* MSRDMLAYER_H_ */
