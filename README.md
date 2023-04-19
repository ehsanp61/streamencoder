# Stream Encoder Project
In this project a three tier encoder is designed for compressing online data stream. The project has three main modules which are managed using two threads. A grabber module for extracting some real data which is run without interruption and make some real data by predefined frequency. A GSM transmitter for sending data through GSM module. This module is run periodically and send produced data after encoding. An three tier encoder for compressing data which is run as a module of GSM transmitter. After running the project, a never-ending process starts from receiving data, compressing and sending it. This project is implemented in C++ 17.
# Architecture of the system
* Runner module
    * Tractive module which contains:
        * Flash data structure
        * Garbber module
        * GSM Transmitter module
            * Three Tier Encoder module            

# Modules
This project contains 4 modules.
## Tractive
This module contains a Flash buffer, Grabber and GSM transmitter. Grabber module is used for read data and store in Flash. GSM transmitter is used for read data from Flash, compressed by Encoder module and then sent through GSM. This module is implemented in [Tractive.h](code/include/tractive.h) and [Tractive.cpp](code/src/tractive.cpp).
## Grabber
This module generates a random data in range `(0 .. 254)` as a real data which is extracted through some sensors. This module simulates sensor module of the real products. The frequency of data generation is controlled by `READ_FREQUENCY` variable before compiling in [grabber.h](code/include/grabber.h) 
## GSM Transmitter
This module simulate GSM transmitter. This module contains Encoder module for compressing data before sending. This module is implemented in [gsmTransmitter.h](code/include/gsmTransmitter.h) and [gsmTransmitter.cpp](code/src/gsmTransmitter.cpp).

## Encoder
This module is used for compressing data before sending. It uses three tier encoder which are manageable through some config parameters. This module is implemented in [encoder.h](code/include/encoder.h) and [encoder.cpp](code/src/encoder.cpp).
### Quantizer
A lossy tier of encoder which is activated using `QUANTIZER_TIER` in [encoder.h](code/include/encoder.h). This module decreases dynamic range of the input data through quantizing by an scale factor `QUANTIZATION_SCALE` in [encoder.h](code/include/encoder.h).
### RunLength Coder
A main tier of compression algorithm. It is always active. It uses a Run Lenght algorithm for compressing.
### Huffman Coder
Final tier of encoder which is activated using `HUFFMAN_TIER` in [encoder.h](code/include/encoder.h). This tier uses Huffman Coding algorithm. This tier contains two main parts. Function `makeHuffmanCode()` makes Huffman code table heuristically and Function `huffmanTier()` uses Huffman code table for coding symbols in the final tier of encoder.
## Main Runner
This module runs two threads for managing process of the tractive module. A thread for grabbing data and another for encoding and sending data through GSM. This module is implemented in [runner.cpp](code/src/runner.cpp).
# Tests
For analyzing the quality, correctness and performance of the implemented modules some Unit, Integration and system tests are designed and used.
## Unit and Integration Tests
5 unit tests and 2 integration tests are designed for analyzing modules. All tests are implemented in [tests.cpp](test/unitTest/tests.cpp). The function `testGetData()` tests grabber module. The functions `testTractive_init()`, `testTractive_writeFlash()` and `testTractive_writeReadFlash()` test tractive module. The function `test_encoderHuffman()`tests encoder module. The function `testGsmTransmitter_loadData()` tests gsmTransmitter and encoder modules as an integration test. The function `testGsmTransmitter_huffmanCode()` tests gsmTransmitter and encoder with Huffman tier modules as an integration test.
## System Test
For analyzing the performance and quality of the implemented modules a system test is designed. In this test, two python modules and a c++ module is used. A simple simulator of pets moving is implemented in [simulator.ipynb](test/systemTest/simulator.ipynb). This simulator makes synthesized data. The function `main()` is implemented in [systemPerformance.cpp](test/systemTest/systemPerformance.cpp) that imports synthesized data to the implemented system and record sent data in a file. A python module is designed and implemented in [decoder_analyzer.ipynb](test/systemTest/decoder_analyzer.ipynb) for decoding the recorded data and analyzing compression rate and error rate of the system. The obtain results are shown below:

```
Encoded Data Capacity:1770 Bytes
Raw Capacity:53315 Bytes
Compression rate:96.68010878739567%
Error rate:0.0%
Decoded Line Number:10650 Lines
Raw Line Number:10663 Lines
```
As shown in the results. The encoder provides a compression rate of around 97% with a zero error rate.
# Cross Compile Toolchain
For using implemented system on Arm32 and aarch64 embedded system a cross compiler toolchain based on the Docker technology is made. Dockerfile of the designed Docker image is provided in [Dockerfile](make/docker/Dockerfile). Also, for analyzing obtained binary file in Arm architecture system and Linux OS a Docker image which is made based on the [QEMU](https://www.qemu.org) is used. The required script for cross compiling and running on ARM architecture is provided in [scripts.txt](make/docker/scripts.txt). The required MakeFile and Config file for compiling in Linux and Windows OS are provided in [make](make) directory.
# Suggestions For Future
1. Using Compressed Sensing technology for decreasing sample rate of data before recording in Flash. This method relaxes some system limitations regarding critical resources such as memory, processing and power consumption. 
2. Using some transformations in space or frequency domain for improving the performance of the compression algorithm.
# Project Manager
I have used Tellero for managing this project. The details of the project management is accessible in [Tractive Project](https://trello.com/b/naMmtn2e/tractive-project). This project has taken ***about 30 Hours*** totally.





