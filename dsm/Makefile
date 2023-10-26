CC=g++
#CFLAGS=-c -Wall -I/home/cecilia/utils/boost/include -I./ -O3 -D_LARGEFILE64_SOURCE
CFLAGS=-c -Wall -I/home/cecilia/dcc/tesis/software/spire12code/dsextract/boost/include -I./ -O3 -D_LARGEFILE64_SOURCE
SOURCES=Shingles.cpp AdjacencyMatrix.cpp vnm.cpp Trie.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=vnm

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

vnm.o: AdjacencyMatrix.h Trie.h Shingles.h vnm.cpp conf.h

AdjacencyMatrix.o: AdjacencyMatrix.cpp AdjacencyMatrix.h conf.h Utils.h

Trie.o: Trie.cpp Trie.h

Shingles.o: Shingles.cpp Shingles.h Utils.h conf.h

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -fr *.o vnm *~
