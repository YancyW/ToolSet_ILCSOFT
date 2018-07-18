# Makefile template for shared library
TARGET_LIB = libtoolset.so

CC = g++
CFLAGS = -std=c++14 -pthread -m64 -fPIC -Wall -Wextra  
#CFLAGS = -std=c++14 -fPIC -Wall -Wextra ${shell root-config --cflags} 
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command

RootPath=/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-01/root/6.08.06
LCIOPath=/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-01/lcio/v02-12/include
MARLINPath=/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-01/Marlin/v01-16/include
INCLUDE = -I. -I..  -I$(RootPath)/include -I${LCIOPath} 
ROOTLIBS := $(shell root-config --libs) -lXMLIO 

SRCS = src/CData_Type.cpp src/CFormat.cpp src/CChain.cpp src/CChain_application.cpp \
	   src/CMC_Get.cpp src/CMC_Operator.cpp src/CMC_Status.cpp src/CMC_Judge.cpp src/CMC_Properties.cpp\
	   src/CRC_Get.cpp src/CRC_Operator.cpp src/CSort.cpp src/CPrint.cpp src/CFlavor.cpp
OBJS=$(patsubst %.cpp, %.o, $(SRCS))

all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} $(INCLUDE) -o $@ $^ $(ROOTLIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	-${RM} ${TARGET_LIB} ${OBJS}
