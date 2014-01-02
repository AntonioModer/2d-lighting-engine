BIN = .
ROOT = ..
SRC = ../src
CXX = g++
FLAGS = -g -std=c++0x
OBJS = main.o FrameBufferObject.o Game.o Image.o Lighting.o Polygon.o Scene.o
LIBS = -lSDL2 -lSDL_image -lGLEW -lGLU

all: main

main: $(OBJS)
	$(CXX) $(FLAGS) -o main $(OBJS) $(LIBS)

main.o: $(ROOT)/main.cpp $(SRC)/Game.h
	$(CXX) $(FLAGS) -c $(ROOT)/main.cpp

FrameBufferObject.o: $(SRC)/FrameBufferObject.cpp $(SRC)/FrameBufferObject.h
	$(CXX) $(FLAGS) -c $(SRC)/FrameBufferObject.cpp

Game.o: $(SRC)/Game.cpp $(SRC)/Game.h $(SRC)/Scene.h
	$(CXX) $(FLAGS) -c $(SRC)/Game.cpp

Image.o: $(SRC)/Image.cpp $(SRC)/Image.h
	$(CXX) $(FLAGS) -c $(SRC)/Image.cpp

Lighting.o: $(SRC)/Lighting.cpp $(SRC)/Lighting.h $(SRC)/Vector2.h
	$(CXX) $(FLAGS) -c $(SRC)/Lighting.cpp

Polygon.o: $(SRC)/Polygon.cpp $(SRC)/Polygon.h
	$(CXX) $(FLAGS) -c $(SRC)/Polygon.cpp

Scene.o: $(SRC)/Scene.cpp $(SRC)/Scene.h $(SRC)/Polygon.h $(SRC)/Lighting.h $(SRC)/FrameBufferObject.h
	$(CXX) $(FLAGS) -c $(SRC)/Scene.cpp

clean:
	rm -f *.o