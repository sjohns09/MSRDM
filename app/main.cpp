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

  MSRDMLayer stateMSRDM;
  MSRDMLayer actionMSRDM;

  // Create Network for MSRDM Layer 1
  Data trainData1("/home/sammie/eclipse-workspace/SoftDev_Robotics"
                  "/Midterm/MSRDM/Data/Layer1",
                  0);

  vector<int> topology1 = trainData1.read_topology();

  // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
  Network netState(topology1[0], topology1[1], topology1[2], topology1[3]);
  stateMSRDM.train(netState, topology1, trainData1);

  // Create Network for MSRDM Layer 2
  Data trainData2("/home/sammie/eclipse-workspace/SoftDev_Robotics"
                  "/Midterm/MSRDM/Data/Layer2",
                  0);

  vector<int> topology2 = trainData2.read_topology();

  // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
  Network netAction(topology2[0], topology2[1], topology2[2], topology2[3]);
  actionMSRDM.train(netAction, topology2, trainData2);

  // DEMO
//  cout << "Enter Input For Demo 1" << endl;  // Must press enter after each
//  string stringUserInput1;
//  string stringUserInput2;
//  vector<double> userInputs(2);
//  cin >> stringUserInput1 >> stringUserInput2;
//  userInputs[0] = std::stod(stringUserInput1);
//  userInputs[1] = std::stod(stringUserInput2);
//
//  MSRDMLayer::get_MSRDM_output(netState, netAction, userInputs);
//
//  cout << "Enter Input For Demo 2" << endl;  // Must press enter after each
//  string stringUserInput3;
//  string stringUserInput4;
//  vector<double> userInputs2(2);
//  cin >> stringUserInput3 >> stringUserInput4;
//  userInputs2[0] = std::stod(stringUserInput3);
//  userInputs2[1] = std::stod(stringUserInput4);
//
//  MSRDMLayer::get_MSRDM_output(netState, netAction, userInputs2);

  return 0;
}

