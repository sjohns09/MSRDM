#include <iostream>
#include <lib.hpp>
#include "Network.h"
#include "Neuron.h"
#include "Data.h"
#include "MSRDMLayer.h"
#include "TrainingData.h"
#include <vector>
#include <cassert>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;

void showVectorVals(string label, vector<double> &v)
{
  cout << label << " ";
  for(unsigned i = 0; i < v.size(); ++i)
  {
    cout << v[i] << " ";
  }
  cout << endl;
}

int main() {

// Testing ANN functionality with test code
  TrainingData trainData("/home/sammie/eclipse-workspace/SoftDev_Robotics/Midterm/MSRDM/Data/TrainingData.txt");
  //e.g., {3, 2, 1 }
  vector<unsigned> topology;
  //topology.push_back(3);
  //topology.push_back(2);
  //topology.push_back(1);

  trainData.getTopology(topology);
  Network myNet(topology[0], topology[1], topology[2], topology[3]);

  vector<double> inputVals, targetVals, resultVals;
  int trainingPass = 0;
  while(!trainData.isEof())
  {
    ++trainingPass;
    cout << endl << "Pass" << trainingPass;

    // Get new input data and feed it forward:
    if(trainData.getNextInputs(inputVals) != topology[0])
      break;
    showVectorVals(": Inputs :", inputVals);
    myNet.feed_forward(inputVals);

    // Collect the net's actual results:
    myNet.get_output(resultVals);
    showVectorVals("Outputs:", resultVals);

    // Train the net what the outputs should have been:
    trainData.getTargetOutputs(targetVals);
    showVectorVals("Targets:", targetVals);
    assert(targetVals.size() == topology[1]);

    myNet.back_prop(targetVals);

    // Report how well the training is working, average over recnet
    cout << "Net recent average error: "
         << myNet.getRecentAverageError() << endl;
  }

cout << endl << "Done Training" << endl;

cout << "Enter Input For Demo" << endl;
string stringUserInput1;
string stringUserInput2;
//string::size_type sz;
vector<double> userInputs(2);
cin >> stringUserInput1 >> stringUserInput2;
userInputs[0] = std::stod(stringUserInput1);
userInputs[1] = std::stod(stringUserInput2);

myNet.feed_forward(userInputs);
myNet.get_output(resultVals);
showVectorVals("Trained Output:", resultVals);

// Random training sets for XOR -- two inputs and one output

//  cout << "topology: 2 4 1" << endl;
//  for(int i = 2000; i >= 0; --i)
//  {
//    int n1 = (int)(2.0 * rand() / double(RAND_MAX));
//    int n2 = (int)(2.0 * rand() / double(RAND_MAX));
//    int t = n1 ^ n2; // should be 0 or 1
//    cout << "in: " << n1 << ".0 " << n2 << ".0 " << endl;
//    cout << "out: " << t << ".0" << endl;
//}


//  int numInputs, numOutputs, numHiddenLayers; // Taken from file
//  vector<double> inputs, targets, results;
//
//  numInputs = 3;
//  numOutputs = 4;
//  numHiddenLayers = 2;
//
//  // Tunable Parameters

//
//  Network myNet(numInputs, numOutputs, numHiddenLayers);
//  myNet.feed_forward(inputs);
//  myNet.back_prop(targets);
//  myNet.get_output(results);

  return 0;
}


