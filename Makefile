.PHONY: all clean

PROJECT_NAME=cainit

CXX=g++
CPP_FLAGS=-std=c++14 -Wall -lssl -lcrypto

INCLUDE_DIR=src/include

SRC_DIR=src

INCLUDES=\
	-I$(INCLUDE_DIR)

SRCS=\
	$(SRC_DIR)/main.cpp\
	$(SRC_DIR)/File.cpp\
	$(SRC_DIR)/Parser.cpp\
	$(SRC_DIR)/Cainit.cpp

OBJS=$(SRCS:.cpp=.o)

all: $(OBJS)
	@$(CXX) $(CPP_FLAGS) $(INCLUDES) -o $(PROJECT_NAME) $(OBJS) $(TEST_FILE_SRC)

%.o : %.cpp
	@$(CXX) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm $(OBJS)
