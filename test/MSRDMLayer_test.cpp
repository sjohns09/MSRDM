/** @file MSRDMLayer_test.cpp
 * @brief The Mental State Reactionary Decision Maker Tests
 *
 * @author Samantha Johnson
 * @date October 17, 2017
 * @copyright [2017] <Samantha Johnson>
 */

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include "MSRDMLayer.h"
#include "Network.h"
#include "Data.h"

using std::string;
using std::vector;

class MSRDMLayer_test : public ::testing::Test {

 public:
  char buff[256];
  char* c = getcwd(buff, sizeof(buff));
  string folderPath = string(c) + "/Data/";

  vector<int> stateTopology = {3,4,1,6};
  vector<int> actionTopology = {4,4,1,8};

 protected:
  virtual void SetUp() {
    Data::create_training_data(1, folderPath);
    Data::create_training_data(2, folderPath);
  }
};


TEST_F(MSRDMLayer_test, testStateOutputIsCorrectForAnxious) {

  MSRDMLayer MSRDMTest(folderPath);
  vector<int> topology = stateTopology;
  Data trainData(folderPath + "Layer1/");

  Network netTest(topology[0], topology[1], topology[2], topology[3]);
  MSRDMTest.train(netTest, topology, trainData);


  vector<double> inputVector = {1,0,0}; // Set this INPUT
  vector<double> resultsVector;
  vector<double> trainedResultNum(4);
  string trainedResultString;

  netTest.feed_forward(inputVector);
  netTest.get_output(resultsVector);
  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 1, trainedResultNum);

  EXPECT_EQ(1, trainedResultNum[0]);
  EXPECT_EQ("ANXIOUS", trainedResultString);
}

TEST_F(MSRDMLayer_test, testStateOutputIsCorrectForSad) {

  Data::create_training_data(1, folderPath);
  Data::create_training_data(2, folderPath);

  MSRDMLayer MSRDMTest(folderPath);
  vector<int> topology = stateTopology;
  Data trainData(folderPath + "Layer1/");

  Network netTest(topology[0], topology[1], topology[2], topology[3]);
  MSRDMTest.train(netTest, topology, trainData);


  vector<double> inputVector = {0,0,1}; // Set this INPUT
  vector<double> resultsVector;
  vector<double> trainedResultNum(4);
  string trainedResultString;

  netTest.feed_forward(inputVector);
  netTest.get_output(resultsVector);
  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 1, trainedResultNum);

  EXPECT_EQ(1, trainedResultNum[1]);
  EXPECT_EQ("SAD", trainedResultString);
}

TEST_F(MSRDMLayer_test, testStateOutputIsCorrectForLethargic) {

  Data::create_training_data(1, folderPath);
  Data::create_training_data(2, folderPath);

  MSRDMLayer MSRDMTest(folderPath);
  vector<int> topology = stateTopology;
  Data trainData(folderPath + "Layer1/");

  Network netTest(topology[0], topology[1], topology[2], topology[3]);
  MSRDMTest.train(netTest, topology, trainData);


  vector<double> inputVector = {0,1,0}; // Set this INPUT
  vector<double> resultsVector;
  vector<double> trainedResultNum(4);
  string trainedResultString;

  netTest.feed_forward(inputVector);
  netTest.get_output(resultsVector);
  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 1, trainedResultNum);

  EXPECT_EQ(1, trainedResultNum[2]);
  EXPECT_EQ("LETHARGIC", trainedResultString);
}

TEST_F(MSRDMLayer_test, testStateOutputIsCorrectForCritical) {

  Data::create_training_data(1, folderPath);
  Data::create_training_data(2, folderPath);

  MSRDMLayer MSRDMTest(folderPath);
  vector<int> topology = stateTopology;
  Data trainData(folderPath + "Layer1/");

  Network netTest(topology[0], topology[1], topology[2], topology[3]);
  MSRDMTest.train(netTest, topology, trainData);


  vector<double> inputVector = {1,1,1}; // Set this INPUT
  vector<double> resultsVector;
  vector<double> trainedResultNum(4);
  string trainedResultString;

  netTest.feed_forward(inputVector);
  netTest.get_output(resultsVector);
  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 1, trainedResultNum);

  EXPECT_EQ(1, trainedResultNum[3]);
  EXPECT_EQ("CRITICAL", trainedResultString);
}

TEST_F(MSRDMLayer_test, testActionOutputIsComfortForAnxiousInput) {

  Data::create_training_data(1, folderPath);
  Data::create_training_data(2, folderPath);

  MSRDMLayer MSRDMTest(folderPath);
  vector<int> topology = actionTopology;
  Data trainData(folderPath + "Layer2/");

  Network netTest(topology[0], topology[1], topology[2], topology[3]);
  MSRDMTest.train(netTest, topology, trainData);


  vector<double> inputVector = {1,0,0,0}; // Set this INPUT
  vector<double> resultsVector;
  vector<double> trainedResultNum(4);
  string trainedResultString;

  netTest.feed_forward(inputVector);
  netTest.get_output(resultsVector);
  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 2, trainedResultNum);

  EXPECT_EQ(1, trainedResultNum[0]);
  EXPECT_EQ("COMFORT", trainedResultString);
}

TEST_F(MSRDMLayer_test, testActionOutputIsPlayForSadInput) {

  Data::create_training_data(1, folderPath);
  Data::create_training_data(2, folderPath);

  MSRDMLayer MSRDMTest(folderPath);
  vector<int> topology = actionTopology;
  Data trainData(folderPath + "Layer2/");

  Network netTest(topology[0], topology[1], topology[2], topology[3]);
  MSRDMTest.train(netTest, topology, trainData);


  vector<double> inputVector = {0,1,0,0}; // Set this INPUT
  vector<double> resultsVector;
  vector<double> trainedResultNum(4);
  string trainedResultString;

  netTest.feed_forward(inputVector);
  netTest.get_output(resultsVector);
  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 2, trainedResultNum);

  EXPECT_EQ(1, trainedResultNum[1]);
  EXPECT_EQ("PLAY", trainedResultString);
}

TEST_F(MSRDMLayer_test, testActionOutputIsMotivateForLethargicInput) {

  Data::create_training_data(1, folderPath);
  Data::create_training_data(2, folderPath);

  MSRDMLayer MSRDMTest(folderPath);
  vector<int> topology = actionTopology;
  Data trainData(folderPath + "Layer2/");

  Network netTest(topology[0], topology[1], topology[2], topology[3]);
  MSRDMTest.train(netTest, topology, trainData);


  vector<double> inputVector = {0,0,1,0}; // Set this INPUT
  vector<double> resultsVector;
  vector<double> trainedResultNum(4);
  string trainedResultString;

  netTest.feed_forward(inputVector);
  netTest.get_output(resultsVector);
  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 2, trainedResultNum);

  EXPECT_EQ(1, trainedResultNum[2]);
  EXPECT_EQ("MOTIVATE", trainedResultString);
}

TEST_F(MSRDMLayer_test, testActionOutputIsEmergencyForCriticalInput) {

  Data::create_training_data(1, folderPath);
  Data::create_training_data(2, folderPath);

  MSRDMLayer MSRDMTest(folderPath);
  vector<int> topology = actionTopology;
  Data trainData(folderPath + "Layer2/");

  Network netTest(topology[0], topology[1], topology[2], topology[3]);
  MSRDMTest.train(netTest, topology, trainData);


  vector<double> inputVector = {0,0,0,1}; // Set this INPUT
  vector<double> resultsVector;
  vector<double> trainedResultNum(4);
  string trainedResultString;

  netTest.feed_forward(inputVector);
  netTest.get_output(resultsVector);
  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 2, trainedResultNum);

  EXPECT_EQ(1, trainedResultNum[3]);
  EXPECT_EQ("EMERGENCY", trainedResultString);
}


// TEST_F(MSRDMLayer_test, testLearnForNegativeFeedbackOnMotivate) {
//
//  MSRDMLayer MSRDMTest(folderPath);
//  vector<int> topology = actionTopology;
//  Data trainData(folderPath + "Layer2/");
//
//  Network netTest(topology[0], topology[1], topology[2], topology[3]);
//  MSRDMTest.train(netTest, topology, trainData);
//
//  vector<double> removeCase = {0,0,1,0,0,0,1,0}; // IN: Lethargic OUT: Motivate
//  vector<double> removeCaseInput = {0,0,1,0}; // IN: Critical, Level 3 OUT: Emergency
//  vector<double> removeCaseOutput = {0,0,1,0};
//  int prefer = 1;
//  MSRDMTest.learn(removeCaseInput, removeCaseOutput, prefer);
//
//  vector<double> inputVector = {0,0,1,0}; // Set this INPUT
//  vector<double> resultsVector;
//  vector<double> trainedResultNum(4);
//  string trainedResultString;
//
//  netTest.feed_forward(inputVector);
//  netTest.get_output(resultsVector);
//  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 2, trainedResultNum);
//
//  EXPECT_NE(1, trainedResultNum[2]);
//  EXPECT_NE("MOTIVATE", trainedResultString);
//}
//
// TEST_F(MSRDMLayer_test, testLearnForNegativeFeedbackOnEmergencyDoesNotChange) {
//
//  MSRDMLayer MSRDMTest(folderPath);
//  vector<int> topology = actionTopology;
//  Data trainData(folderPath + "Layer2/");
//
//  Network netTest(topology[0], topology[1], topology[2], topology[3]);
//  MSRDMTest.train(netTest, topology, trainData);
//
//  vector<double> removeCaseInput = {0,0,0,1}; // IN: Critical, Level 3 OUT: Emergency
//  vector<double> removeCaseOutput = {0,0,0,1};
//  int prefer = 1;
//  MSRDMTest.learn(removeCaseInput, removeCaseOutput, prefer);
//
//  vector<double> inputVector = {0,0,0,1}; // Set this INPUT
//  vector<double> resultsVector;
//  vector<double> trainedResultNum(4);
//  string trainedResultString;
//
//  netTest.feed_forward(inputVector);
//  netTest.get_output(resultsVector);
//  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 2, trainedResultNum);
//
//  EXPECT_EQ(1, trainedResultNum[3]);
//  EXPECT_EQ("EMERGENCY", trainedResultString);
//}
//
// TEST_F(MSRDMLayer_test, testGetMSRDMOutputForSensorInput) {
//
//  MSRDMLayer stateMSRDM(folderPath);
//  MSRDMLayer actionMSRDM(folderPath);
//
//  // Create Network for MSRDM Layer 1
//  Data trainData1(folderPath + "Layer1/");
//
//  vector<int> topology1 = trainData1.read_topology();
//
//  // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
//  Network netState(topology1[0], topology1[1], topology1[2], topology1[3]);
//  stateMSRDM.train(netState, topology1, trainData1);
//
//  // Create Network for MSRDM Layer 2
//  Data trainData2(folderPath + "Layer2/");
//
//  vector<int> topology2 = trainData2.read_topology();
//
//  // Topology: #inputs, #outputs, #hiddenLayers, #hiddenNeurons
//  Network netAction(topology2[0], topology2[1], topology2[2], topology2[3]);
//  actionMSRDM.train(netAction, topology2, trainData2);
//
//  vector<double> inputVector = {1,1,1}; // Set this INPUT
//  vector<double> resultsVector;
//  vector<double> trainedResultNum(4);
//  string trainedResultString;
//
//  resultsVector = MSRDMLayer::get_MSRDM_output(netState, netAction, inputVector);
//
//  trainedResultString = MSRDMLayer::interpret_results(resultsVector, 2, trainedResultNum);
//
//  EXPECT_EQ(1, trainedResultNum[3]);
//  EXPECT_EQ("EMERGENCY", trainedResultString);
//}
