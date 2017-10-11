# C++ Boilerplate
[![Build Status](https://travis-ci.org/sjohns09/MSRDM.svg?branch=master)](https://travis-ci.org/sjohns09/MSRDM)
[![Coverage Status](https://coveralls.io/repos/github/sjohns09/MSRDM/badge.svg?branch=master)](https://coveralls.io/github/sjohns09/MSRDM?branch=master)
---

## Overview

ACME is developing an in home (or hospital) mental health robotic pet companion. This
companion is geared toward individuals with moderate-severe mental health conditions that would
benefit from constant supervision and stimulation from an external source. The target consumer is
young to middle aged adult, who may live alone or are in a situation where there is limited supervision,
and who also suffers from a behavioral disorder such as depression, anxiety, or bi-polar disorder. The
goal of this product is to provide companionship, motivation, emotional stabilization, activity
notifications, and emergency resources to aid in the recovery process for an individual suffering from a
mental health disorder. This product also hopes to speed up the recovery time and decrease the relapse
rate for these individuals, and also reduce the high number of suicides that occur amongst this group.

The module that will be developed is the Mental State Reactionary Decision Maker (MSRDM),
which is a component of the decision making part of the brain for the robot companion. This part of the
brain will need to be trained to respond to different signals that are coming in from the user and make a
decision on how to react to best help the user at that time. The robot will detect the state of the patient
through various sensors, such as a wearable armband for heart rate detection, facial detection to
determine emotions such as sadness and smiling, motion detection to determine the activity level of the
individual, and sound detection to determine if the individual is in distress. Each of these sensors will
provide an input into the MSRDM which will then determine which action the robot needs to take in
order to address the mental state of the individual and output this for the robot to act upon.

One of the key components of the MSRDM will be its ability to take feedback from the user over
time and re-learn how to react when that user exhibits certain signs. This means that each pet
companion will be tailored for its own human and will grow to understand how to interact with the
human better as time passes

To develop the MSRDM a feedforward Artificial Neural Network will be developed which will
allow the MSRDM to be initially trained on a data set using a supervised backpropagation method. The
MSRDM will actually consist of two layers of ANNs, where the signals from the sensors feed into the
input to the first ANN, then the output from the first ANN feeds into the inputs to the second ANNs, and
the output from the second ANNs tell the robot what action needs to be taken. The first ANN will
determine the state of the human based on sensor inputs, and bin this state into categories, such as
depressed, lethargic, anxious, and in-danger. The second layer of ANNs will exist to determine the best
response that the robot should take based on its previous training and the users preferences. Only the
second layer of ANNs will be user tunable through user interactions.

## Standard install via command-line
```
git clone --recursive https://github.com/sjohns09/MSRDM.git
cd <MSRDM>
mkdir build
cd build
cmake ..
make
Run tests: ./test/cpp-test
Run program: ./app/shell-app
```

## Backlog and Worklog Tracking

Backlog: https://github.com/sjohns09/MSRDM/projects/1
	- When each of the cards is clicked a more detailed view of that issue will open
	- Each issue is tied to a milestone, which represents a Sprint
Worklog: https://docs.google.com/a/terpmail.umd.edu/spreadsheets/d/1ZThi5BMmKaSMvxs0Rrzsw18x1GJcbB0TY2FZOLDv7rU/edit?usp=sharing
	- Commentable by all UMD users with link

## References

Used the following tutorial video for guidance in the development of the Artificial Neural Network - https://vimeo.com/19569529

## License

TBD
