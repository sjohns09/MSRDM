/*
 * MSRDMLayer.h
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */

#include <iostream>
#include <vector>
#include "Network.h"

#ifndef MSRDMLAYER_H_
#define MSRDMLAYER_H_

class MSRDMLayer {
 public:
  MSRDMLayer(Network network);

  void train(std::string dataFile);
  double get_output(double input);
  void learn(std::vector<double> removeCase);

  virtual ~MSRDMLayer();
};

#endif /* MSRDMLAYER_H_ */
