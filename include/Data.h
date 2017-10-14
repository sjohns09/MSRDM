/*
 * Data.h
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <vector>
#include <string>
#include <iostream>

#ifndef INCLUDE_DATA_H_
#define INCLUDE_DATA_H_

class Data {
 public:
  Data(std::string file);

  std::vector<double> read_weights();
  std::vector<double> read_training_data();
  std::vector<double> read_topology();
  void write_weights();
  void edit_training_data(std::string caseToRemove);

  virtual ~Data();
};

#endif /* INCLUDE_DATA_H_ */
