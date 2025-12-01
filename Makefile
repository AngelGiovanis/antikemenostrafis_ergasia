# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Source files
SRCS = src/main.cpp src/types.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = simulation

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)