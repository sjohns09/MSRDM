/*
 * Data.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Data.h"

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::stringstream;

Data::Data(string folderPath) {
  dataFolder = folderPath;
  trainingFile = dataFolder + "/TrainingData.txt";

  trainingDataFile.open(trainingFile.c_str());
  if (!trainingDataFile.is_open()) {
    cout << "FILE CHECK DID NOT PASS - Check that filepath exists" << std::endl;
  }
  trainingDataFile.close();
}

vector<int> Data::read_topology() {

  trainingDataFile.open(trainingFile.c_str());

  string line;
  string label;
  vector<int> topology;

  getline(trainingDataFile, line);
  stringstream sStream(line);
  sStream >> label;
  if (sStream.eof() || label.compare("topology:") != 0) {
    abort();
  }

  while (!sStream.eof()) {
    int n;
    sStream >> n;
    topology.push_back(n);
  }
  trainingDataFile.close();

  return topology;
}

vector<double> Data::get_next_inputs() {

  vector<double> nextInputs;
  string line;

  getline(trainingDataFile, line);
  string c(1, line[0]);

  if (c.compare("t") == 0) {
    getline(trainingDataFile, line);
  }

  stringstream sStream(line);
  string label;
  sStream >> label;

  if (label.compare("in:") == 0) {
    double n;
    while (sStream >> n) {
      nextInputs.push_back(n);
    }
  }
  return nextInputs;
}

vector<double> Data::get_target_outputs() {

  vector<double> targetOutputVals;
  string line;
  getline(trainingDataFile, line);
  stringstream sStream(line);

  string label;
  sStream >> label;
  if (label.compare("out:") == 0) {
    double n;
    while (sStream >> n) {
      targetOutputVals.push_back(n);
    }
  }
  return targetOutputVals;
}

void Data::show_vector_vals(string label, vector<double> v)
{
  cout << label << " ";
  for(unsigned i = 0; i < v.size(); ++i)
  {
    cout << v[i] << " ";
  }
  cout << endl;
}

bool Data::isEof()
{
  bool isEof = trainingDataFile.eof();
  return isEof;
}

Data::~Data() {
  trainingDataFile.close();
}

