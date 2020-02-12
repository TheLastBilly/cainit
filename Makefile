.PHONY: all clean

PROJECT_NAME=journali

CXX=g++
CPP_FLAGS=-std=c++14 -Wall -lssl -lcrypto

INCLUDE_DIR=src/include

SRC_DIR=src

INCLUDES=\
	-I$(INCLUDE_DIR)

SRCS=\
	$(SRC_DIR)/main.cpp\
	$(SRC_DIR)Reference.cpp

OBJS=$(SRCS:.cpp=.o)

all: $(OBJS)
	@$(CXX) $(CPP_FLAGS) $(INCLUDES) -o $(PROJECT_NAME) $(OBJS) $(TEST_FILE_SRC)

%.o : %.cpp
	@$(CXX) $(CPP_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm $(OBJS)
