#Docker image for toolchain cross-compiler gnueabi, musl, LLVM, arm32 & aarch64

############EEEE HHHH SSSSS AAAAA NNNNN #######################
#
#
#
###############################################################
From ubuntu
LABEL "author" = "Ehsan"
LABEL "version" = "1.0"


#insall required packagaes
RUN apt-get update
RUN apt-get upgrade
RUN apt-get update && apt-get -y -qq install sudo

RUN adduser --gecos "" --disabled-password epz && usermod -aG sudo epz 
#RUN ["/bin/bash", "chpasswd <<<", "'epz:123'"]

#install text Editor
RUN apt-get update && apt-get -qq -y install vim
RUN apt-get update && apt-get -qq -y install nano

#SSH & SCP
RUN apt-get update && sudo apt-get -qq -y install openssh-client
RUN apt-get update && sudo apt-get -qq -y install file
RUN apt-get update && sudo apt-get -qq -y install wget
RUN apt-get update && sudo apt-get -qq -y install xz-utils
RUN apt-get update && sudo apt-get -qq -y install openssh-server
RUN 
#Build Chain
RUN apt-get update && apt-get update && sudo apt-get -y install build-essential


#make chain
RUN apt-get update && sudo apt-get -qq -y install cmake
RUN apt-get update && sudo apt-get -qq -y install gcc-arm-linux-gnueabi
RUN apt-get update && sudo apt-get -qq -y install binutils-arm-linux-gnueabi
RUN apt-get update && sudo apt-get -qq -y install g++-arm-linux-gnueabi
RUN apt-get update && sudo apt-get -qq install -y gcc-aarch64-linux-gnu
RUN apt-get update && sudo apt-get -qq install -y binutils-aarch64-linux-gnu
RUN apt-get update && sudo apt-get -qq install -y g++-aarch64-linux-gnu
WORKDIR /bin
RUN ln -s aarch64-linux-gnu-gcc arm64-gcc
RUN ln -s aarch64-linux-gnu-g++ arm64-g++
RUN ln -s arm-linux-gnueabi-gcc arm-gcc
RUN ln -s arm-linux-gnueabi-g++ arm-g++

#Build Chain Linaro
#WORKDIR /bin
#RUN sudo wget https://snapshots.linaro.org/gnu-toolchain/13.0-2022.11-1/aarch64-linux-gnu/gcc-linaro-13.0.0-2022.11-x86_64_aarch64-linux-gnu.tar.xz
#RUN sudo tar -xf gcc-linaro-13.0.0-2022.11-x86_64_aarch64-linux-gnu.tar.xz
#RUN ln -s gcc-linaro-13.0.0-2022.11-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-g++ linaro-g++
#RUN ln -s gcc-linaro-13.0.0-2022.11-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc linaro-gcc

EXPOSE 21
ENTRYPOINT /bin/bash








