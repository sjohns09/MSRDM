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
  MSRDMLayer(int layerNum); // Creates a Network and Trains it

  void train(std::string dataFile);
  int get_MSRDM_output(std::vector<double> input);
  void learn(std::vector<double> removeCase);
  virtual ~MSRDMLayer();

 private:
  //Network netMSRDM(2,1,1,4);


};

#endif /* MSRDMLAYER_H_ */
