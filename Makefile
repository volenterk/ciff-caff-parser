CXX = g++
CXXFLAGS = -Wall -g -Wextra -pedantic -std=c++11
TARGET = parser

SRC = ciff/cifffile.cpp ciff/ciffheader.cpp ciff/ciffcontent.cpp
HDR = ciff/cifffile.h ciff/ciffheader.h ciff/ciffcontent.h

OBJ = $(SRC.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp $(HDR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)