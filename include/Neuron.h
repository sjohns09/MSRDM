/** @file Neuron.h
 * @brief This class represents a neuron in a neural net.
 *
 * @author Samantha Johnson
 * @date October 17, 2017
 * @copyright [2017] <Samantha Johnson>
 *
 * @details Represents a neuron of a neural net and performs many of the necessary
 * calculations for the weighting and training on the network.
 *
 * This class utilized the training video by David Miller (https://vimeo.com/19569529)
 * called "Neural Net in C++ Tutorial", to develop the neural net framework.
 * All code was written by the author of this document.
 */

#include <iostream>
#include <vector>
#include "Network.h"

#ifndef INCLUDE_NEURON_H_
#define INCLUDE_NEURON_H_

typedef std::vector<Neuron> NetLayer;

class Neuron {
 public:
  /**
   * @brief A constructor that sets up the parameters for the neuron.
   * @param Inputs are the number of connections the neuron must connect to and the index of that
   * neuron in the net layer.
   */
  Neuron(int numOutConnections, int index);
  /**
   * @brief A method that sets the output value of the neuron.
   * @param Input is the output value
   */
  void setOutValue(double value);
  /**
   * @brief A method that gets the output value of the neuron.
   * @return Return is the output value
   */
  double getOutValue();
  /**
   * @brief A method that feeds the input values accross the neuron to the next layer
   * @param Input is previous layer which is needed to gather all input values
   */
  void feed_forward(const NetLayer& preLayer);
  /**
   * @brief A method that gets the output gradients between the target value and the actual value
   * in the neuron
   * @param Input is the target value of the neuron output
   */
  void get_out_gradients(double targetVal);
  /**
   * @brief A method that gets the output gradients of the hidden layers
   * @param Input is the next layer which contains the gradients of that layer
   */
  void get_hidden_gradients(const NetLayer& nextLayer);
  /**
   * @brief A method that updates the input weights of the neuron for use in training
   * @param Input is the previous layer of the network
   */
  void update_input_weights(NetLayer& preLayer);

  virtual ~Neuron();

 private:
  struct Connections {
    double weight;
    double deltaWeight;
  };
  /**
   * @brief A method that sets the initial weights of the network to random values
   * @return Return is the initial weights
   */
  double initial_weight();
  /**
   * @brief A method that represents the transfer function of the network
   * @param Input is the weight to pass into the transfer function
   * @return Return is the input processed through the transfer function
   */
  static double transferFunc(double x);
  /**
   * @brief A method that represents the derivative transfer function of the network
   * @param Input is the weight to pass into the transfer function
   * @return Return is the input processed through the transfer function
   */
  static double transferFuncDX(double x);
  double outValue;
  std::vector<Connections> outWeights;
  double gradient;
  int nIndex;
};

#endif /* APP_NEURON_H_ */
