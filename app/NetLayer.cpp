/*
 * NetLayer.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */
#include <iostream>
#include <vector>
#include "Neuron.h"
#include "NetLayer.h"

NetLayer::NetLayer(double numNeurons) {
  // TODO Auto-generated constructor stub
  layer = std::vector<Neuron>(numNeurons);


}

NetLayer::~NetLayer() {
  // TODO Auto-generated destructor stub
}

