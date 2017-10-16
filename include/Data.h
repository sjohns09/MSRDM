/*
 * Data.h
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifndef INCLUDE_DATA_H_
#define INCLUDE_DATA_H_

class Data {
 public:
  Data(std::string folderPath, int createNewData);

  std::vector<double> read_training_data();
  std::vector<double> get_next_inputs();
  std::vector<double> get_target_outputs();
  std::vector<int> read_topology();
  void edit_training_data(std::string caseToRemove);
  static void show_vector_vals(std::string label, std::vector<double> v);
  bool isEof(void);

  virtual ~Data();

 private:
  std::string dataFolder;
  std::string trainingFile;
  std::fstream trainingDataFile;
  void create_new_training_set();
};

#endif /* INCLUDE_DATA_H_ */
