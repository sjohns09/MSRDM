/** @file Data.h
 * @brief This class reads and writes the training data for the neural net
 *
 * @author Samantha Johnson
 * @date October 17, 2017
 * @copyright [2017] <Samantha Johnson>
 *
 * @details Reads and writes training data using a specified file location.
 *
 * Parts of this class utilized the training video by David Miller (https://vimeo.com/19569529)
 * called "Neural Net in C++ Tutorial", to develop the neural net framework.
 * All code was written by the author of this document.
 */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifndef INCLUDE_DATA_H_
#define INCLUDE_DATA_H_

class Data {
 public:
  /**
   * @brief A constructor that sets up the file location for the training file
   * @param Input is the path to the training folder
   */
  Data(std::string folderPath);
  /**
   * @brief A methodthat creates training data to use in network
   * @param Input is the layer number of the network and the path to the training folder
   */
  static void create_training_data(int layerNum,
                                   std::string userDataFolderPath);
  /**
   * @brief A method that edits the training data in the training file so the
   * robot can re-learn and adjust to the users preferences
   * @param Input is the input of the case to remove, the output of the case to remove,
   * and the result the user would prefer to happen
   * @result Return is the success or failure of the training process
   */
  static int edit_training_data(std::vector<double> removeCaseInput,
                                std::vector<double> removeCaseOutput,
                                int casePrefer);
  /**
   * @brief A method that gets the next set of inputs from the training file
   * @result Return is the set of inputs
   */
  std::vector<double> get_next_inputs();
  /**
   * @brief A method that gets the next set of target outputs from the training file
   * @result Return is the set of target outputs
   */
  std::vector<double> get_target_outputs();
  /**
   * @brief A method that reads the topology from the training file to construct the net
   * @result Return is the topology variables
   */
  std::vector<int> read_topology();
  /**
   * @brief A method that allows vector values to be displayed in the console
   * @param Input is the text and values that will be displayed
   */
  static void show_vector_vals(std::string label, std::vector<double> v);
  /**
   * @brief A method that determine if the file has reached the end
   * @result Return is whether the end is reached or not
   */
  bool isEof(void);
  std::fstream trainingDataFile;
  std::string trainingFile;
  static std::string dataFolder;

  virtual ~Data();

};

#endif /* INCLUDE_DATA_H_ */
