/** @file MSRDM.cpp
 * @brief This class is the backbone of the MSRDM module
 *
 * @author Samantha Johnson
 * @date October 17, 2017
 * @copyright [2017] <Samantha Johnson>
 *
 * @details Utilizes the neural net classes to create a robot that is capable of training
 * on a set of input to provide suitable actions for its human user, and also learning
 * how to improve those actions based on feedback from the human.
 *
 * Parts of this class utilized the training video by David Miller (https://vimeo.com/19569529)
 * called "Neural Net in C++ Tutorial", to develop the neural net framework.
 * All code was written by the author of this document.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "Network.h"
#include "Neuron.h"
#include "Data.h"
#include "MSRDMLayer.h"

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using std::ifstream;
using std::ofstream;

string MSRDMLayer::dataFolder;

MSRDMLayer::MSRDMLayer(string userDataFolder) {
  dataFolder = userDataFolder;

}

vector<double> MSRDMLayer::get_MSRDM_output(Network& stateNet,
                                            Network& actionNet,
                                            std::vector<double> input) {

  vector<double> stateResultVals;
  stateNet.feed_forward(input);
  stateNet.get_output(stateResultVals);

  vector<double> stateResultInts(4);

  string stateString = interpret_results(stateResultVals, 1, stateResultInts);
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

  MSRDMLayer learner(MSRDMLayer::dataFolder);
  learner.learn(actionNet, stateString, stateResultInts, actionResultInts);

  return actionResultVals;
}

void MSRDMLayer::learn(Network& actionNet, string stateString,
                       vector<double> caseIn, vector<double> caseOut) {

  string prefer;
  cout << endl << "Are You Happy With Your Results? (Y/N)" << endl;
  prefer = read_user_input();
  if (prefer == "N" || prefer == "n") {
    cout << endl << "Which action would you prefer for state " << stateString
         << "?" << endl;
    if (stateString == "CRITICAL") {
      cout << "---- For your safety this action cannot be re-learned ----"
           << endl;
    } else {
      cout << " Enter the number 1 (Comfort), 2 (Play), or 3 (Motivate)"
           << endl;
      prefer = read_user_input();

      int done = Data::edit_training_data(caseIn, caseOut, stoi(prefer));

      if (done == 1) {
        MSRDMLayer learner(MSRDMLayer::dataFolder);
        Data learnData(MSRDMLayer::dataFolder + "Layer2/");
        vector<int> topology = { 4, 4, 1, 8 };
        learner.train(actionNet, topology, learnData);
        cout << "Learning Complete!" << endl;
      } else {
        cout << "Learning Failed..." << endl;
      }
    }
  } else {
    cout << "Yay!" << endl;
  }

}

string MSRDMLayer::read_user_input() {
  string s;
  cin >> s;
  return s;

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
      } else {
        result[i] = 0;
      }
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
      } else {
        result[i] = 0;
      }
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

    // Get new input data and feed it forward:
    inputVals = trainData.get_next_inputs();
    if (inputVals.size() != topology[0])
      break;
    myNet.feed_forward(inputVals);

    // Collect the net's actual results:
    myNet.get_output(resultVals);

    // Train the net what the outputs should have been:
    targetVals = trainData.get_target_outputs();
    assert(targetVals.size() == topology[1]);

    myNet.back_prop(targetVals);
  }

  cout << endl << "Done Training" << endl;

  trainData.trainingDataFile.close();
}

MSRDMLayer::~MSRDMLayer() {
// TODO Auto-generated destructor stub
}

