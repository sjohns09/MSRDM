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
  MSRDMLayer(std::string userDataFolder);

  static std::vector<double> get_MSRDM_output(Network& netState, Network& netAction, std::vector<double> input);
  void learn(Network& actionNet, std::string state, std::vector<double> removeCaseInput, std::vector<double> removeCaseOutput);
  void train(Network& myNet, std::vector<int> topology, Data& trainData);
  static std::string interpret_results(const std::vector<double> resultVector, int layerNum, std::vector<double>& result);
  static void result_satisfaction(int satisfied);
  virtual ~MSRDMLayer();

 private:
  static std::string dataFolder;

};

#endif /* MSRDMLAYER_H_ */
