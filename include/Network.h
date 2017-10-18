/** @file Network.h
 * @brief This class utilizes the functionality of the network of a Neural Net
 *
 * @author Samantha Johnson
 * @date October 17, 2017
 * @copyright [2017] <Samantha Johnson>
 *
 * @details Represents the network of a neural net and performs the looping and processing
 * necessary to train the network and get results from it.
 *
 * This class utilized the training video by David Miller (https://vimeo.com/19569529)
 * called "Neural Net in C++ Tutorial", to develop the neural net framework.
 * All code was written by the author of this document.
 */

#include <iostream>
#include <vector>
#include "Data.h"

#ifndef INCLUDE_NETWORK_H_
#define INCLUDE_NETWORK_H_

class Neuron;

typedef std::vector<Neuron> NetLayer;

class Network {
 public:
  /**
   * @brief A constructor that sets up the neural network for the system
   * @param Inputs are the number of neurons in the input layer, the number of neurons
   * in the output layer, the number of hidden layers, and the number of neurons in the
   * hidden layer.
   */
  Network(int numInputs, int numOutputs, int numHiddenLayers,
          int numHiddenNeuron);

  /**
   * @brief A method that feeds forward the inputs of the neural net across the layers
   * of the net to determine an output
   * @param Input is the inputs that need to feed forward
   */
  void feed_forward(const std::vector<double>& inputs);
  /**
   * @brief A method that updates the weights of the neural net during the training process
   * @param Input is the targets output of the net
   */
  void back_prop(const std::vector<double>& targets);
  /**
   * @brief A method that gets the output of the neural net
   * @param Input is results vector which is modified to contain the output of the net
   */
  void get_output(std::vector<double>& results);

  virtual ~Network();

 private:
  std::vector<NetLayer> layers;
  int numLayers;
  double errorRMS;
  int outputNum;
  int inputNum;
  int hiddenNum;
};

#endif /* NETWORK_H_ */
