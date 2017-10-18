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
  Data(std::string folderPath);

  static void create_training_data(int layerNum, std::string userDataFolderPath);
  static int edit_training_data(std::vector<double> removeCaseInput, std::vector<double> removeCaseOutput, int casePrefer);
  std::vector<double> get_next_inputs();
  std::vector<double> get_target_outputs();
  std::vector<int> read_topology();
  static void show_vector_vals(std::string label, std::vector<double> v);
  bool isEof(void);
  std::fstream trainingDataFile;
  std::string trainingFile;
  static std::string dataFolder;

  virtual ~Data();

 private:

};

#endif /* INCLUDE_DATA_H_ */
