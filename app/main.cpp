#include <iostream>
#include <lib.hpp>
#include "Network.h"
#include "Neuron.h"
#include "Data.h"
#include "MSRDMLayer.h"
#include <vector>
#include <cassert>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {

  // Training
  Data trainData(
      "/home/sammie/eclipse-workspace/SoftDev_Robotics/Midterm/MSRDM/Data", 0);

  vector<int> topology = trainData.read_topology();
  // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
  Network myNet(topology[0], topology[1], topology[2], topology[3]);
  Network::train(myNet, topology, trainData);

  // DEMO
  cout << "Enter Input For Demo" << endl;  // Must press enter after each
  string stringUserInput1;
  string stringUserInput2;
  vector<double> userInputs(2);
  cin >> stringUserInput1 >> stringUserInput2;
  userInputs[0] = std::stod(stringUserInput1);
  userInputs[1] = std::stod(stringUserInput2);

  vector<double> resultVals;
  myNet.feed_forward(userInputs);
  myNet.get_output(resultVals);
  Data::show_vector_vals("Trained Output:", resultVals);

  return 0;
}

