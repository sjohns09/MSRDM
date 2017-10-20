/** @file main.cpp
 * @brief The Mental State Reactionary Decision Maker
 *
 * @author Samantha Johnson
 * @date October 17, 2017
 * @copyright [2017] <Samantha Johnson>
 *
 * @details Allows for a robot to interact with a human and determine the human's state
 * and the robot to then choose an action based on that state. There is also a demo that
 * shows functionality when this program is run.
 *
 * All code was written by the author of this document.
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
//#include <boost/filesystem.hpp>
#include "Network.h"
#include "Neuron.h"
#include "Data.h"
#include "MSRDMLayer.h"

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;

int main() {

  char buff[256];
  char* c;
  c = getcwd(buff, sizeof(buff));
  cout << c << endl;
  string userDataFolder = string(c) + "/Data/";
  string layer1 = userDataFolder + "Layer1";
  string layer2 = userDataFolder + "Layer2";
  mkdir(userDataFolder.c_str(), 0700);
  mkdir(layer1.c_str(), 0700);
  mkdir(layer2.c_str(), 0700);

  // ------ Create Data Files --------
  Data::create_training_data(1, userDataFolder);
  Data::create_training_data(2, userDataFolder);
  // ---------------------------------

  MSRDMLayer stateMSRDM(userDataFolder);
  MSRDMLayer actionMSRDM(userDataFolder);

  // Create Network for MSRDM Layer 1
  Data trainData1(userDataFolder + "Layer1/");

  vector<int> topology1 = trainData1.read_topology();

  // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
  Network netState(topology1[0], topology1[1], topology1[2], topology1[3]);
  stateMSRDM.train(netState, topology1, trainData1);

  // Create Network for MSRDM Layer 2
  Data trainData2(userDataFolder + "Layer2/");

  vector<int> topology2 = trainData2.read_topology();

  // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
  Network netAction(topology2[0], topology2[1], topology2[2], topology2[3]);
  actionMSRDM.train(netAction, topology2, trainData2);

  // DEMO
  cout
      << endl
      << "---- Welcome to the Mental State Reactionary Decision Maker Demo! ----"
      << endl;
  string s;
  while (s != "DONE") {

    cout << "Enter a 0 or 1 for each sensor to show it has triggered" << endl
         << "Press Enter After Each Input" << endl
         << "Sensor 1: HeartRateElevated" << endl << "Sensor 2: Motion Low"
         << endl << "Sensor 3: Distressed Voice" << endl;  // Must press enter after each
    string s1;
    string s2;
    string s3;

    vector<double> userInputs(3);
    cin >> s1 >> s2 >> s3;
    userInputs[0] = std::stod(s1);
    userInputs[1] = std::stod(s2);
    userInputs[2] = std::stod(s3);

    MSRDMLayer::get_MSRDM_output(netState, netAction, userInputs);

    cout << endl << "Enter 'DONE' to end the demo or 'GO' to keep testing"
         << endl;
    cin >> s;
  }

  cout << endl << "---- END OF DEMO ----";
  return 0;
}

// ---------------------------------------------------------------------------

