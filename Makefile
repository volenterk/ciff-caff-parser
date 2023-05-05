CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
LIBS = -lwebp

SRC = main.cpp ciff/cifffile.cpp ciff/ciffheader.cpp ciff/ciffcontent.cpp
HDR = ciff/cifffile.h ciff/ciffheader.h ciff/ciffcontent.h

# Define the object files
OBJ = $(SRC:.cpp=.o)

# Define the output executable
TARGET = parser

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LIBS) -o $(TARGET)

%.o: %.cpp $(HDR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

all_clean: all clean