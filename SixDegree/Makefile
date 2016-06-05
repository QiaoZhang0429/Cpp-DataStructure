# A simple makefile for CSE 100 P4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
  CPPFLAGS += -O3
  LDFLAGS += -O3
else
  CPPFLAGS += -g
  LDFLAGS += -g
endif

all: pathfinder actorconnections extension

pathfinder: pathfinder.cpp ActorGraph.cpp Node.cpp Edge.cpp Movie.cpp UnionFind.cpp

actorconnections: actorconnections.cpp ActorGraph.cpp Node.cpp Edge.cpp Movie.cpp UnionFind.cpp

extension: extension.cpp ActorGraph.cpp Node.cpp Edge.cpp Movie.cpp UnionFind.cpp

clean:
	rm -f pathfinder actorconnections extension *.o core*

