CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++20
LIBS = -lwebp

SRC = main.cpp cifffile.cpp cafffile.cpp
HDR = cifffile.h cafffile.h

OBJ = $(SRC:.cpp=.o)

TARGET = parser

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LIBS) -o $(TARGET)

%.o: %.cpp $(HDR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)