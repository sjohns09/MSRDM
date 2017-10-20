/** @file MSRDM.h
 * @brief This class is the backbone of the MSRDM module
 *
 * @author Samantha Johnson
 * @date October 17, 2017
 * @copyright [2017] <Samantha Johnson>
 *
 * @details Utilizes the neural net classes to create a robot that is capable of training
 * on a set of input to provide suitable actions for its human user, and also learning
 * how to improve those actions based on feedback from the human.
 *
 * Parts of this class utilized the training video by David Miller (https://vimeo.com/19569529)
 * called "Neural Net in C++ Tutorial", to develop the neural net framework.
 * All code was written by the author of this document.
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Network.h"

#ifndef INCLUDE_MSRDMLAYER_H_
#define INCLUDE_MSRDMLAYER_H_

class MSRDMLayer {
 public:
  /**
   * @brief A constructor that sets up the file location for the training file that the
   * MSRDM needs to operate
   * @param Input is the path to the training folder
   */
  MSRDMLayer(std::string userDataFolder);
  /**
   * @brief A method that gets the output of the MSRDM based on an input, which is processed
   * through two neural nets
   * @param Inputs are the state neural net for layer 1, the action neural net for layer 2,
   * and the inputs that will be processed
   * @return Return is the output of the MSRDM
   */
  static std::vector<double> get_MSRDM_output(Network& netState,
                                              Network& netAction,
                                              std::vector<double> input);
  /**
   * @brief A method that allows the robot to learn based on information gathered
   * through user interactions
   * @param Inputs are the action neural net, the name of the state that was input,
   * the input case to search for and update, and the ouput case to search for
   * and update
   */
  void learn(Network& actionNet, std::string state,
             std::vector<double> removeCaseInput,
             std::vector<double> removeCaseOutput);
  /**
   * @brief A method that allows the robot to be trained based on a set of training data
   * @param Inputs are the neural net, the topology of that network, and the training data
   */
  void train(Network& myNet, std::vector<int> topology, Data& trainData);

  /**
   * @brief A method that allows the robot to read user input
   * @return Return is the string the user has input
   */
  virtual std::string read_user_input();
  /**
   * @brief A method that interprets the raw output of the neural net to determine what the
   * result of the human state is or action of the robot should be
   * @param Inputs are the raw result vector, the layer number of the MSRDM, and an empty
   * result vector which will return the normalized results
   * @return Return is a string that specifies the human state or the robot action dependind
   * on the layer
   */
  static std::string interpret_results(const std::vector<double> resultVector,
                                       int layerNum,
                                       std::vector<double>& result);
  virtual ~MSRDMLayer();

 private:
  static std::string dataFolder;

};

#endif /* MSRDMLAYER_H_ */
