CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self -fPIC

# Directorios
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj

# PyBind11
PYTHON_INCLUDE = -I/usr/include/python3.10 -I/home/pbn/.local/lib/python3.10/site-packages/pybind11/include

# Archivos fuente (CORREGIDO)
CPPFILES = $(wildcard ./lib/*.cpp)
SOURCES = $(CPPFILES)
OBJECTS = $(SOURCES:.cpp=.o)

# Target
TARGET = colisiones.so

all: $(TARGET)

# Linking corregido
$(TARGET): $(OBJECTS)
	$(CXX) -shared $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(PYTHON_INCLUDE) -I$(INCLUDE) -c $< -o $@


clean:
	rm -f $(OBJECTS) $(TARGET)