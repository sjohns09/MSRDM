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

vector<double> MSRDMLayer::get_MSRDM_output(Network& stateNet, Network& actionNet, std::vector<double> input) {
  // This takes both networks and feeds the input from the statenet to the actionnet

  vector<double> resultVals;
  //net.feed_forward(input);
  //net.get_output(resultVals);
  Data::show_vector_vals("Trained Output:", resultVals);
  return resultVals;
}

void MSRDMLayer::learn(vector<double> removeCase) {
  // Takes {input,input,output} and replaces the output with another choice 1-3
  // If the output is 4 return doing nothing
}

string MSRDMLayer::interpret_results(const std::vector<double> resultVector, int layerNum, vector<int>& result) {

  string s = "";
  return s;

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

