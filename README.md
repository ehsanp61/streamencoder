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
## Tractive
This module contains a Flash buffer, Grabber and GSM transmitter. Grabber module is used for read data and store in Flash. GSM transmitter is used for read data from Flash, compressed by Encoder module and then sent through GSM. This module implemented in [Tractive.h](code/include/tractive.h) and [Tractive.cpp](code/src/tractive.cpp).
## Grabber
This module generates a random data in range `(0 .. 254)` as a real data which is extracted through some sensors. This module simulates sensor module of the real products. The frequency of data generation is controlled by `READ_FREQUENCY` variable before compiling in [grabber.h](code/include/grabber.h) 
## GSM Transmitter
This module simulate GSM transmitter. This module contains Encoder module for compressing data before sending. This module implemented in [gsmTransmitter.h](code/include/gsmTransmitter.h) and [gsmTransmitter.cpp](code/src/gsmTransmitter.cpp).

## Encoder
This module is used for compressing data before sending. It uses three tier encoder which are manageable through some config parameters. This module implemented in [encoder.h](code/include/encoder.h) and [encoder.cpp](code/src/encoder.cpp).
### Quantizer
A lossy tier of encoder which is activated using `QUANTIZER_TIER` in [encoder.h](code/include/encoder.h). This module decreases dynamic range of the input data through quantizing by an scale factor `QUANTIZATION_SCALE` in [encoder.h](code/include/encoder.h).
### RunLength Coder
A main tier of compression algorithm. It is always active. It uses a Run Lenght algorithm for compressing.
### Huffman Coder
Final tier of encoder which is activated using `HUFFMAN_TIER` in [encoder.h](code/include/encoder.h). This tier uses Huffman Coding algorithm. This tier contains two main parts. Function `makeHuffmanCode()` makes Huffman code table heuristically and Function `huffmanTier()` uses Huffman code table for coding symbols in the final tier of encoder.
## Main Runner
This module runs two thread for managing process of tractive module. A thread for grabbing data and another for encoding and sending data through GSM. This module implemented in [runner.cpp](code/src/runner.cpp).
# Tests
## Unit and Integration Tests
## System Test
# Cross Compile
## Compile Toolchain
## Run Toolchain
# System Proposal
# Project Manager





