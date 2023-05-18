CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
LIBS = -lwebp

SRC = main.cpp ciff/cifffile.cpp
HDR = ciff/cifffile.h

OBJ = $(SRC:.cpp=.o)

TARGET = parser

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LIBS) -o $(TARGET)

%.o: %.cpp $(HDR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)