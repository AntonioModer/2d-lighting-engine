BIN = ./bin
SRC = ./src
CXX = g++
FLAGS = -g -Wall -std=c++0x
OBJS = main.o FrameBufferObject.o Game.o Image.o Lighting.o Polygon.o Scene.o
LIBS = -lSDL2 -lSDL_image -lGLEW -lGLU

all: 
	$(MAKE) -C $(BIN) all && ln -sf $(BIN)/main main

clean:
	rm -f $(BIN)/*.o