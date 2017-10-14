/*
 * MSRDMLayer_test.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */

#include <gtest/gtest.h>
#include <string>
#include "MSRDMLayer.h"

using std::string;

TEST(MSRDMLayer_test, testTrainMSRDMLayer1) { //Need to Fix Test Names!
  // Set training weights to all 0 and then check that the
  //weights are all changed after training
}

TEST(MSRDMLayer_test, testTrainMSRDMLayer2) { //Need to Fix Test Names!
  // Set training weights to all 0 and then check that the
  //weights are all changed after training
}

TEST(MSRDMLayer_test, testGetOutputFromMSRDMLayer1) { //Need to Fix Test Names!
  // Send in sensor input to layer 1 and receive correct output of state
}

TEST(MSRDMLayer_test, testGetOutputFromMSRDMLayer2) { //Need to Fix Test Names!
  // Send in state input to layer 2 and receive correct output of action
}

TEST(MSRDMLayer_test, testLearningForMSRDMLayer2) { //Need to Fix Test Names!
  // Give negative feedback on action and re-learn.
  // Send in same input state and make sure a different action is chosen
}
