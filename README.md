# Stream Encoder Project
In this project a three tier encoder is designed for compressing online data stream. The project has three main modules which are managed using two threads. A grabber module for extracting some real data which is run without interruption and make some real data by predefined frequency. A GSM transmitter for sending data through GSM module. This module is run periodically and send produced data after encoding. An three tier encoder for compressing data which is run as a module of GSM transmitter. After running the project, a never-ending process starts from receiving data, compressing and sending it.
# Architecture of the system
* Runner madule
    * Tractive module which containes:
        * Flash data structure
        * Garbber module
        * GSM Transmitter module
            * Three Tier Encoder module            

# Modules
This project contains 4 modules.
## Grabber
This module generates a random data in range `(0 .. 254)` as a real data which is extracted through some sensors. This module simulates sensor module of the real products. The frequency of data generation is controlled by `READ_FREQUENCY` variable before compiling in [grabber.h](code/include/grabber.h) 
## GSM Transmitter
## Encoder
### Quantizer
### RunLength Coder
### Huffman Coder
## Tractive
## Main Runner
# Tests
## Unit and Integration Tests
## System Test
# System Proposal
# Project Manager





