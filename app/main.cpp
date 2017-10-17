#include <iostream>
#include <lib.hpp>
#include "Network.h"
#include "Neuron.h"
#include "Data.h"
#include "MSRDMLayer.h"
#include <vector>
#include <cassert>
#include <fstream>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;

int main() {

  MSRDMLayer stateMSRDM;
  MSRDMLayer actionMSRDM;

  // Create Network for MSRDM Layer 1
  Data trainData1("/home/sammie/eclipse-workspace/SoftDev_Robotics"
                  "/Midterm/MSRDM/Data/Layer1");

  vector<int> topology1 = trainData1.read_topology();

  // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
  Network netState(topology1[0], topology1[1], topology1[2], topology1[3]);
  stateMSRDM.train(netState, topology1, trainData1);

  // Create Network for MSRDM Layer 2
  Data trainData2("/home/sammie/eclipse-workspace/SoftDev_Robotics"
                  "/Midterm/MSRDM/Data/Layer2");

  vector<int> topology2 = trainData2.read_topology();

  // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
  Network netAction(topology2[0], topology2[1], topology2[2], topology2[3]);
  actionMSRDM.train(netAction, topology2, trainData2);

  // DEMO
  cout << "Enter Input For Demo 1" << endl;  // Must press enter after each
  string s1;
  string s2;
  string s3;

  vector<double> userInputs(3);
  cin >> s1 >> s2 >> s3;
  userInputs[0] = std::stod(s1);
  userInputs[1] = std::stod(s2);
  userInputs[2] = std::stod(s3);

  MSRDMLayer::get_MSRDM_output(netState, netAction, userInputs);

  return 0;
}

// ---------------------------------------------------------------------------
// USED TO CREATE TEST DATA FILES (commented out because only needed to run once)
//  // Create Test Data File For Layer1
//  fstream trainingDataFile;
//  trainingDataFile.open("/home/sammie/eclipse-workspace/SoftDev_Robotics/Midterm/MSRDM/Data/Layer1/TrainingData.txt");
//  if (!trainingDataFile.is_open())
//    cout << "CANT FIND FILE";
//
//  trainingDataFile << "topology: 3 4 1 6" << endl;
//
//  for (int i = 0; i <= 300; i++) {
//    trainingDataFile << "in: 1 0 0" << endl;
//    trainingDataFile << "out: 1 0 0 0" <<  endl;
//
//    trainingDataFile << "in: 0 1 0" << endl;
//    trainingDataFile << "out: 0 0 1 0" <<  endl;
//
//    trainingDataFile << "in: 0 0 1" << endl;
//    trainingDataFile << "out: 0 1 0 0" <<  endl;
//
//    trainingDataFile << "in: 1 1 1" << endl;
//    trainingDataFile << "out: 0 0 0 1" <<  endl;
//
//    trainingDataFile << "in: 1 1 0" << endl;
//    trainingDataFile << "out: 1 0 0 0" <<  endl;
//
//    trainingDataFile << "in: 1 0 1" << endl;
//    trainingDataFile << "out: 0 1 0 0" <<  endl;
//
//    trainingDataFile << "in: 0 1 1" << endl;
//    trainingDataFile << "out: 0 1 0 0" <<  endl;
//
//  }
//  trainingDataFile.close();
//

//  // Create Test Data File For Layer2
//  fstream trainingDataFile;
//  trainingDataFile.open("/home/sammie/eclipse-workspace/SoftDev_Robotics/Midterm/MSRDM/Data/Layer2/TrainingData.txt");
//  if (!trainingDataFile.is_open())
//    cout << "CANT FIND FILE";
//
//  trainingDataFile << "topology: 4 4 1 8" << endl;
//
//  for (int i = 0; i <= 500; i++) {
//    trainingDataFile << "in: 1 0 0 0" << endl;
//    trainingDataFile << "out: 1 0 0 0" <<  endl;
//
//    trainingDataFile << "in: 0 1 0 0" << endl;
//    trainingDataFile << "out: 0 1 0 0" <<  endl;
//
//    trainingDataFile << "in: 0 0 1 0" << endl;
//    trainingDataFile << "out: 0 0 1 0" <<  endl;
//
//    trainingDataFile << "in: 0 0 0 1" << endl;
//    trainingDataFile << "out: 0 0 0 1" <<  endl;
//
//
//  }
//  trainingDataFile.close();

