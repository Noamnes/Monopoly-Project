# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -I. -g

# SFML library flags
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS = main.cpp StreetTile.cpp TextBox.cpp Board.cpp Player.cpp MonopolyGame.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = MonopolyGame

# Default target
all : $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(SFML_FLAGS)

# Compile source files into object files
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# dependencies


# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean