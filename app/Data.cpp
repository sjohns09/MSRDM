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

Data::Data(string folderPath, int createNewData) {
  dataFolder = folderPath;
  trainingFile = dataFolder + "/TrainingData.txt";

  trainingDataFile.open(trainingFile.c_str());
  if (!trainingDataFile.is_open()) {
    cout << "FILE CHECK DID NOT PASS - Check that filepath exists" << std::endl;
  }
  trainingDataFile.close();

  if (createNewData == 1) {
    create_new_training_set();
  }
}

void Data::create_new_training_set() {
  //Random training sets for XOR -- two inputs and one output

  trainingDataFile.open(trainingFile.c_str());
  trainingDataFile << "topology: 2 4 1" << endl;
  for (int i = 2000; i >= 0; --i) {
    int n1 = (int) (2.0 * rand() / double(RAND_MAX));
    int n2 = (int) (2.0 * rand() / double(RAND_MAX));
    int t = n1 ^ n2;  // should be 0 or 1
    trainingDataFile << "in: " << n1 << ".0 " << n2 << ".0 " << endl;
    trainingDataFile << "out: " << t << ".0" << endl;
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

