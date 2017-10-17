add_executable(shell-app main.cpp Network.cpp Neuron.cpp MSRDMLayer.cpp
Data.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
