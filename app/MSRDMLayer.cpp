/*
 * MSRDMLayer.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */

#include <iostream>
#include <vector>
#include "Network.h"
#include "MSRDMLayer.h"
#include "Data.h"

using std::vector;

Network netMSRDM(2,1,1,4);

MSRDMLayer::MSRDMLayer(int layerNum) {
  if (layerNum == 1) {
    // Create Network
    Data trainData(
        "/home/sammie/eclipse-workspace/SoftDev_Robotics/Midterm/MSRDM/Data/Layer1", 0);

    vector<int> topology = trainData.read_topology();

    // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
    netMSRDM(topology[0], topology[1], topology[2], topology[3]);
    Network::train(netMSRDM, topology, trainData);
  }
  else if (layerNum == 0) {
    // Create Network
    Data trainData(
        "/home/sammie/eclipse-workspace/SoftDev_Robotics/Midterm/MSRDM/Data/Layer2", 0);

    vector<int> topology = trainData.read_topology();

    // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
    netMSRDM(topology[0], topology[1], topology[2], topology[3]);
    Network::train(netMSRDM, topology, trainData);
  }

}

int MSRDMLayer::get_MSRDM_output(std::vector<double> input) {
  vector<double> resultVals;
  netMSRDM.feed_forward(input);
  netMSRDM.get_output(resultVals);
  Data::show_vector_vals("Trained Output:", resultVals);

  return 0;
}

MSRDMLayer::~MSRDMLayer() {
  // TODO Auto-generated destructor stub
}

