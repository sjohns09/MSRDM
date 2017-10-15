/*
 * Data.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
#include <string>
#include "Data.h"

Data::Data(std::string folderPath) {
  dataFolder = folderPath;
  trainingFile = dataFolder + "/TrainingData";
  weightsFile = dataFolder + "/WeightsData";

}

void Data::create_new_training_set() {

}

Data::~Data() {
  // TODO Auto-generated destructor stub
}

