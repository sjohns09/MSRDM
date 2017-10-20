/** @file Data.cpp
 * @brief This class reads and writes the training data for the neural net
 *
 * @author Samantha Johnson
 * @date October 17, 2017
 * @copyright [2017] <Samantha Johnson>
 *
 * @details Reads and writes training data using a specified file location.
 *
 * Parts of this class utilized the training video by David Miller (https://vimeo.com/19569529)
 * called "Neural Net in C++ Tutorial", to develop the neural net framework.
 * All code was written by the author of this document.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include "Data.h"

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::stringstream;
using std::fstream;
using std::to_string;
using std::ifstream;
using std::ofstream;

string Data::dataFolder;

Data::Data(string layerFolderPath) {
  dataFolder = layerFolderPath;
  trainingFile = dataFolder + "TrainingData.txt";

  trainingDataFile.open(trainingFile.c_str());
  if (!trainingDataFile.is_open()) {
    cout << "FILE CHECK DID NOT PASS - Check that filepath exists" << std::endl;
  }
  trainingDataFile.close();
}

void Data::create_training_data(int layerNum, string userDataFolder) {

  // Create Test Data File For Layer1
  ofstream createDataFile;

  if (layerNum == 1) {
    createDataFile.open(userDataFolder + "Layer1/TrainingData.txt");
    if (!createDataFile.is_open())
      cout << "CANT FIND FILE";

    createDataFile << "topology: 3 4 1 6" << endl;

    for (int i = 0; i <= 300; i++) {
      createDataFile << "in: 1 0 0" << endl;
      createDataFile << "out: 1 0 0 0" << endl;

      createDataFile << "in: 0 1 0" << endl;
      createDataFile << "out: 0 0 1 0" << endl;

      createDataFile << "in: 0 0 1" << endl;
      createDataFile << "out: 0 1 0 0" << endl;

      createDataFile << "in: 1 1 1" << endl;
      createDataFile << "out: 0 0 0 1" << endl;

      createDataFile << "in: 1 1 0" << endl;
      createDataFile << "out: 1 0 0 0" << endl;

      createDataFile << "in: 1 0 1" << endl;
      createDataFile << "out: 0 1 0 0" << endl;

      createDataFile << "in: 0 1 1" << endl;
      createDataFile << "out: 0 1 0 0" << endl;

    }
    createDataFile.close();
  }

  // Create Test Data File For Layer2
  if (layerNum == 2) {
    createDataFile.open(userDataFolder + "Layer2/TrainingData.txt");
    if (!createDataFile.is_open())
      cout << "CANT FIND FILE";

    createDataFile << "topology: 4 4 1 8" << endl;

    for (int i = 0; i <= 500; i++) {
      createDataFile << "in: 1 0 0 0" << endl;
      createDataFile << "out: 1 0 0 0" << endl;

      createDataFile << "in: 0 1 0 0" << endl;
      createDataFile << "out: 0 1 0 0" << endl;

      createDataFile << "in: 0 0 1 0" << endl;
      createDataFile << "out: 0 0 1 0" << endl;

      createDataFile << "in: 0 0 0 1" << endl;
      createDataFile << "out: 0 0 0 1" << endl;

    }
    createDataFile.close();
  }
}

int Data::edit_training_data(std::vector<double> caseIn,
                             std::vector<double> caseOut, int prefer) {

  if (caseIn[3] == 1) {
    return 1;
  } else {
    string ogFilePath = dataFolder + "TrainingData.txt";
    string tempFilePath = dataFolder + "Temp.txt";

    string caseReplace;
    switch (prefer) {
      case 1:
        caseReplace = "out: 1 0 0 0";
        break;
      case 2:
        caseReplace = "out: 0 1 0 0";
        break;
      case 3:
        caseReplace = "out: 0 0 1 0";
        break;
    }

    string changeIn = "in: " + to_string(static_cast<int>(caseIn[0])) + " "
        + to_string(static_cast<int>(caseIn[1])) + " " + to_string(static_cast<int>(caseIn[2])) + " "
        + to_string(static_cast<int>(caseIn[3]));
    string changeOut = "out: " + to_string(static_cast<int>(caseOut[0])) + " "
        + to_string(static_cast<int>(caseOut[1])) + " " + to_string(static_cast<int>(caseOut[2])) + " "
        + to_string(static_cast<int>(caseOut[3]));

    ifstream ogFile(ogFilePath);
    ofstream tempFile(tempFilePath);

    if (!ogFile.is_open() || !tempFile.is_open())
      cout << "Could not open training files, check file path" << endl;

    string temp;
    int i = 1;
    int line;
    while (getline(ogFile, temp)) {
      if (temp == changeIn) {
        line = i;
      }
      if (i == line + 1 && temp == changeOut) {
        temp = caseReplace;
      }
      tempFile << temp << endl;
      i++;
    }

    if (remove(ogFilePath.c_str()) == 0)
      if (rename(tempFilePath.c_str(), ogFilePath.c_str()) != 0) {
        cout << "Error Rewriting Training File" << endl;
        return 0;
      } else {
        remove(tempFilePath.c_str());
        return 1;
      }
  }
  return 0;
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

void Data::show_vector_vals(string label, vector<double> v) {
  cout << label << " ";
  for (unsigned i = 0; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << endl;
}

bool Data::isEof() {
  bool isEof = trainingDataFile.eof();
  return isEof;
}

Data::~Data() {
  trainingDataFile.close();
}

