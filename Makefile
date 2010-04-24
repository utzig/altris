CXX := g++
CXXFLAGS := -g
LIBS := -lgosu

all: AlTris

Block.cpp: Block.h

Block.o: Block.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

Tetramino.cpp: Tetramino.h

Tetramino.o: Tetramino.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

Board.cpp: Board.h

Board.o: Board.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

GameWindow.cpp: GameWindow.h

GameWindow.o: GameWindow.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

AlTris.o: AlTris.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

AlTris: Block.o Tetramino.o Board.o GameWindow.o AlTris.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f *.o AlTris

.PHONY: all clean
