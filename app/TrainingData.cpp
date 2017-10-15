/*
 * TrainingData.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: sammie
 */

#include "TrainingData.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::vector;
using std::string;
using std::stringstream;
using std::cout;

TrainingData::TrainingData(const string filename)
{
  m_trainingDataFile.open(filename.c_str());
  if (!m_trainingDataFile.is_open())
    cout << "FILE NOT OPEN" << std::endl;
}

void TrainingData::getTopology(vector<unsigned> &topology)
{
  string line;
  string label;

  getline(m_trainingDataFile, line);
  stringstream ss(line);
  ss >> label;
  if(this->isEof() || label.compare("topology:") != 0)
  {
    abort();
  }

  while(!ss.eof())
  {
    unsigned n;
    ss >> n;
    topology.push_back(n);
  }
  return;
}


unsigned TrainingData::getNextInputs(vector<double> &inputVals)
{
    inputVals.clear();

    string line;
    getline(m_trainingDataFile, line);
    stringstream ss(line);

    string label;
    ss >> label;
    if (label.compare("in:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
        }
    }

    return inputVals.size();
}

unsigned TrainingData::getTargetOutputs(vector<double> &targetOutputVals)
{
    targetOutputVals.clear();

    string line;
    getline(m_trainingDataFile, line);
    stringstream ss(line);

    string label;
    ss>> label;
    if (label.compare("out:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }

    return targetOutputVals.size();
}

