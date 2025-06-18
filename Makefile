CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self -fPIC

# Directorios
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj

# PyBind11
PYTHON_VERSION = $(shell python3 --version | cut -d '.' -f 1-2 | tr -d ' ' | sed 's/Python/python/')
PYTHON_INCLUDE = -I/usr/include/$(PYTHON_VERSION) -I$(PWD)/external/pybind11/include


CPPFILES = $(wildcard ./lib/*.cpp)
SOURCES = $(CPPFILES)
OBJECTS = $(SOURCES:.cpp=.o)

# Target
TARGET = colisiones.so

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -shared $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(PYTHON_INCLUDE) -I$(INCLUDE) -c $< -o $@


clean:
	rm -f $(OBJECTS) $(TARGET)