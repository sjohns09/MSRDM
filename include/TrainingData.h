/*
 * TrainingData.h
 *
 *  Created on: Oct 15, 2017
 *      Author: sammie
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#ifndef APP_TRAININGDATA_H_
#define APP_TRAININGDATA_H_

class TrainingData
{
public:
  TrainingData(const std::string filename);
  bool isEof(void)
  {
    return m_trainingDataFile.eof();
  }
  void getTopology(std::vector<unsigned> &topology);

  // Returns the number of input values read from the file:
  unsigned getNextInputs(std::vector<double> &inputVals);
  unsigned getTargetOutputs(std::vector<double> &targetOutputVals);

private:
  std::fstream m_trainingDataFile;
};

#endif /* APP_TRAININGDATA_H_ */
