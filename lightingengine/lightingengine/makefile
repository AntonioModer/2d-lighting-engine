BIN = ./bin
SRC = ./src
CXX = g++
FLAGS = -g -Wall -std=c++0x
OBJS = main.o FrameBufferObject.o Game.o Image.o Lighting.o Polygon.o Scene.o
LIBS = -lSDL2 -lSDL_image -lGLEW -lGLU

all: 
	$(MAKE) -sC $(BIN) all && ln -sf $(BIN)/main main

clean:
	cd $(BIN) && $(MAKE) -s clean