/*
 * MSRDMLayer.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <string>
#include <algorithm>
#include "Network.h"
#include "Neuron.h"
#include "Data.h"
#include "MSRDMLayer.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;

MSRDMLayer::MSRDMLayer() {

}

vector<double> MSRDMLayer::get_MSRDM_output(Network& stateNet,
                                            Network& actionNet,
                                            std::vector<double> input) {
  // This takes both networks and feeds the input from the statenet to the actionnet

  vector<double> stateResultVals;
  stateNet.feed_forward(input);
  stateNet.get_output(stateResultVals);

  vector<double> stateResultInts(4);

  string stateString = interpret_results(stateResultVals, 1,
                                          stateResultInts);
  cout << endl << "Human State: " << stateString << endl;
  Data::show_vector_vals("Raw State Output:", stateResultVals);
  Data::show_vector_vals("Normalized State Output:", stateResultInts);

  vector<double> actionResultVals;
  actionNet.feed_forward(stateResultInts);
  actionNet.get_output(actionResultVals);

  vector<double> actionResultInts(4);

  string actionString = interpret_results(actionResultVals, 2,
                                          actionResultInts);

  cout << endl << "Robot Action Decision: " << actionString << endl;

  Data::show_vector_vals("Raw Action Output:", actionResultVals);
  Data::show_vector_vals("Normalized Action Output:", actionResultInts);

  return actionResultVals;
}

void MSRDMLayer::learn(vector<double> removeCase) {
  // Takes {input,input,output} and replaces the output with another choice 1-3
  // If the output is 4 return doing nothing
}

string MSRDMLayer::interpret_results(const vector<double> resultVector,
                                     int layerNum, vector<double>& result) {

  string stringResult;

  if (layerNum == 1) {
    auto maxElement = *std::max_element(std::begin(resultVector),
                                        std::end(resultVector));
    int maxIndex;

    for (int i = 0; i < resultVector.size(); i++) {
      if (resultVector[i] == maxElement) {
        result[i] = 1;
        maxIndex = i;
      } else
        result[i] = 0;
    }
    if (maxIndex == 0)
      stringResult = "ANXIOUS";
    else if (maxIndex == 1)
      stringResult = "SAD";
    else if (maxIndex == 2)
      stringResult = "LETHARGIC";
    else if (maxIndex == 3)
      stringResult = "CRITICAL";
  }

  if (layerNum == 2) {
    auto maxElement = *std::max_element(std::begin(resultVector),
                                        std::end(resultVector));
    int maxIndex;

    for (int i = 0; i < resultVector.size(); i++) {
      if (resultVector[i] == maxElement) {
        result[i] = 1;
        maxIndex = i;
      } else
        result[i] = 0;
    }
    if (maxIndex == 0)
      stringResult = "COMFORT";
    else if (maxIndex == 1)
      stringResult = "PLAY";
    else if (maxIndex == 2)
      stringResult = "MOTIVATE";
    else if (maxIndex == 3)
      stringResult = "EMERGENCY";
  }

  return stringResult;

}

void MSRDMLayer::train(Network& myNet, vector<int> topology, Data& trainData) {

  trainData.trainingDataFile.open(trainData.trainingFile.c_str());

  vector<double> inputVals, targetVals, resultVals;
  int trainingPass = 0;
  while (!trainData.isEof()) {
    ++trainingPass;
    cout << endl << "Pass" << trainingPass;

    // Get new input data and feed it forward:
    inputVals = trainData.get_next_inputs();
    if (inputVals.size() != topology[0])
      break;
    Data::show_vector_vals(": Inputs :", inputVals);
    myNet.feed_forward(inputVals);

    // Collect the net's actual results:
    myNet.get_output(resultVals);
    Data::show_vector_vals("Outputs:", resultVals);

    // Train the net what the outputs should have been:
    targetVals = trainData.get_target_outputs();
    Data::show_vector_vals("Targets:", targetVals);
    assert(targetVals.size() == topology[1]);

    myNet.back_prop(targetVals);

    // Report how well the training is working, average over recent
    cout << "Net recent average error: " << myNet.get_recent_error() << endl;
  }

  cout << endl << "Done Training" << endl;

  trainData.trainingDataFile.close();
}

MSRDMLayer::~MSRDMLayer() {
// TODO Auto-generated destructor stub
}

