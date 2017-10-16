#include <iostream>
#include <lib.hpp>
#include "Network.h"
#include "Neuron.h"
#include "Data.h"
#include "MSRDMLayer.h"
#include <vector>
#include <cassert>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {

  MSRDMLayer layer1(1);
  MSRDMLayer layer2(2);

  // DEMO
  cout
  << "Enter Input For Demo" << endl;  // Must press enter after each
  string stringUserInput1;
  string stringUserInput2;
  vector<double> userInputs(2);
  cin >> stringUserInput1 >> stringUserInput2;
  userInputs[0] = std::stod(stringUserInput1);
  userInputs[1] = std::stod(stringUserInput2);

  return 0;
}

