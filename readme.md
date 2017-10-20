# Mental State Reactionary Decision Maker
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
through various sensors, such as a wearable armband for heart rate detection, motion detection to determine the 
activity level of the individual, and sound detection to determine if the individual is in distress. 
Each of these sensors will provide an input into the MSRDM which will then determine which action the robot needs 
to take in order to address the mental state of the individual and output this for the robot to act upon.

One of the key components of the MSRDM is its ability to take feedback from the user over
time and re-learn how to react when that user exhibits certain signs. This means that each pet
companion will be tailored for its own human and will grow to understand how to interact with the
human better as time passes

To develop the MSRDM a feedforward Artificial Neural Network was developed which allows
the MSRDM to be initially trained on a data set using a supervised backpropagation method. The
MSRDM consists of two layers of ANNs, where the signals from the sensors feed into the
input to the first ANN, then the output from the first ANN feeds into the inputs to the second ANNs, and
the output from the second ANNs tell the robot what action needs to be taken. The first ANN
determines the state of the human based on sensor inputs, and bins this state into categories, such as
anxious, sad, lethargic, and critical. The second layer of ANNs determines the best
response that the robot should take based on its previous training and the users preferences. Only the
second layer of ANNs will be user tunable through user feedback.

Due to the complex nature of Neural Networks a training video was utilized to guide in creating the framework of the neural net. This video is by David Miller called "Neural Net in C++ Tutorial" (https://vimeo.com/19569529). All code for this project was developed by the author of this project, even though the video was used to guide development in areas where the author had less knowledge.

## Results
Demo Sample With Positive Feedback From Human
```
---- Welcome to the Mental State Reactionary Decision Maker Demo! ----
Enter a 0 or 1 for each sensor to show it has triggered
Press Enter After Each Input
Sensor 1: HeartRateElevated
Sensor 2: Motion Low
Sensor 3: Distressed Voice

1
0
0

Human State: ANXIOUS
Raw State Output: 0.972103 0.00031508 0.000570252 -0.000999933 
Normalized State Output: 1 0 0 0 

Robot Action Decision: COMFORT
Raw Action Output: 0.98364 0.0228972 -0.036628 0.011152 
Normalized Action Output: 1 0 0 0 

Are You Happy With Your Results? (Y/N)
Y
Yay!
```
Demo Sample With Negative Feedback From Human Showing Learning
```
Enter a 0 or 1 for each sensor to show it has triggered
Press Enter After Each Input
Sensor 1: HeartRateElevated
Sensor 2: Motion Low
Sensor 3: Distressed Voice
1
0
1

Human State: SAD
Raw State Output: 0.00125283 0.982556 -0.0013359 -0.00308637 
Normalized State Output: 0 1 0 0 

Robot Action Decision: PLAY
Raw Action Output: -0.00924147 0.980623 0.00176912 -0.0112443 
Normalized Action Output: 0 1 0 0 

Are You Happy With Your Results? (Y/N)
N

Which action would you prefer for state SAD?
 Enter the number 1 (Comfort), 2 (Play), or 3 (Motivate)
1

Done Training
Learning Complete!

Enter 'DONE' to end the demo or 'GO' to keep testing
Go
Enter a 0 or 1 for each sensor to show it has triggered
Press Enter After Each Input
Sensor 1: HeartRateElevated
Sensor 2: Motion Low
Sensor 3: Distressed Voice
1
0
1

Human State: SAD
Raw State Output: 0.00125283 0.982556 -0.0013359 -0.00308637 
Normalized State Output: 0 1 0 0 

Robot Action Decision: COMFORT
Raw Action Output: 0.98582 2.57923e-05 6.18593e-05 -7.29544e-06 
Normalized Action Output: 1 0 0 0 
```

## To Run Demo
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
The demo will begin running when shell-app is started.

## Backlog

Backlog: https://github.com/sjohns09/MSRDM/projects/1
- When each of the cards is clicked a more detailed view of that issue will open
- Each issue is tied to a milestone, which represents a Sprint

## Worklog

Worklog: https://docs.google.com/a/terpmail.umd.edu/spreadsheets/d/1ZThi5BMmKaSMvxs0Rrzsw18x1GJcbB0TY2FZOLDv7rU/edit?usp=sharing
- Commentable by all UMD users with the link

## Doxygen Documentation
To generate Doxygen Documentation:
Run "doxygen configfile" from the command line in the source code directory 

## References

Used the following tutorial video for guidance in the development of the Artificial Neural Network framework:
David Miller - https://vimeo.com/19569529

## License

GNU Library or "Lesser" General Public License
