/*
 * MSRDMLayer_test.cpp
 *
 *  Created on: Oct 14, 2017
 *      Author: sammie
 */

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "MSRDMLayer.h"
#include "Network.h"
#include "Data.h"

using std::string;
using std::vector;
TEST(MSRDMLayer_test, testTrainMSRDMLayer1) {  //Need to Fix Test Names!
  // Verify the average error is < 5% - use layer 1 topology and data

  vector<int> topology = { 2, 1, 1, 4 };
  Network testNet(topology);
  Data testData("/home/sammie/eclipse-workspace/SoftDev_Robotics/"
                "Midterm/MSRDM/Data/Test",
                0);
  Network::train(testNet, topology, testData);

  double error = testNet.get_recent_error();

  EXPECT_NEAR(0, error, 0.05);

}

TEST(MSRDMLayer_test, testTrainMSRDMLayer2) {  //Need to Fix Test Names!
  // Verify the average error is < 5% - use layer 2 topology and data
  vector<int> topology = { 2, 1, 1, 4 };
  Network testNet(topology);
  Data testData("/home/sammie/eclipse-workspace/SoftDev_Robotics/"
                "Midterm/MSRDM/Data/Test",
                0);
  Network::train(testNet, topology, testData);

  double error = testNet.get_recent_error();

  EXPECT_NEAR(0, error, 0.05);
}

TEST(MSRDMLayer_test, testGetOutputFromMSRDMLayer1) {  //Need to Fix Test Names!
  // Send in sensor input to layer 1 and receive correct
  // output of state
  // Use layer 1 topology and data

  vector<int> topology = { 2, 1, 1, 4 };
  Network testNet(topology);
  Data testData("/home/sammie/eclipse-workspace/SoftDev_Robotics/"
                "Midterm/MSRDM/Data/Test",
                0);
  Network::train(testNet, topology, testData);

  vector<double> inputVector;
  MSRDMLayer layer1;
  int outState = layer1.get_MSRDM_output(inputVector);

  EXPECT_EQ("1", outState); // Anxious
}

TEST(MSRDMLayer_test, testGetOutputFromMSRDMLayer2) {  //Need to Fix Test Names!
  // Send in state input to layer 2 and receive correct output of action
}

TEST(MSRDMLayer_test, testLearningForMSRDMLayer2) {  //Need to Fix Test Names!
  // Give negative feedback on action and re-learn.
  // Send in same input state and make sure a different action is chosen
}
