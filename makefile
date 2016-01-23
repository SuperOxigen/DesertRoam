COMPILER = g++
CFLAG = -std=c++11 -Wall
SRCTYPE = cpp
HDRTYPE = h
SOURCE = src
OBJECT = obj
BINARY = bin
NAME = desert_roam

all: $(BINARY)/$(NAME)

build: $(BINARY)

# ********************
#   Header Files
# ********************

$(SOURCE)/board.h: $(SOURCE)/point.h $(SOURCE)/player.h $(SOURCE)/map.h
	touch $(SOURCE)/board.h

$(SOURCE)/inventory.h: $(SOURCE)/resource.h
	touch $(SOURCE)/inventory.h

$(SOURCE)/map.h: $(SOURCE)/tile.h $(SOURCE)/tile_factory.h $(SOURCE)/matrix.h
	touch $(SOURCE)/map.h

$(SOURCE)/player.h: $(SOURCE)/inventory.h $(SOURCE)/stat_bar.h $(SOURCE)/attack.h
	touch $(SOURCE)/player.h

$(SOURCE)/tile.h: $(SOURCE)/player.h $(SOURCE)/tile_action.h
	touch $(SOURCE)/tile.h

$(SOURCE)/tile_factory.h: $(SOURCE)/tile.h
	touch $(SOURCE)/tile_factory.h

# ********************
#   Object Files
# ********************

$(OBJECT)/board.o: $(SOURCE)/board.cpp $(SOURCE)/board.h
	g++ $(CFLAG) -c $(SOURCE)/board.cpp -o $(OBJECT)/board.o

$(OBJECT)/drutils.o: $(SOURCE)/drutils.cpp $(SOURCE)/point.h
	g++ $(CFLAG) -c $(SOURCE)/drutils.cpp -o $(OBJECT)/drutils.o

$(OBJECT)/inventory.o: $(SOURCE)/inventory.cpp $(SOURCE)/inventory.h
	g++ $(CFLAG) -c $(SOURCE)/inventory.cpp -o $(OBJECT)/inventory.o

$(OBJECT)/map.o: $(SOURCE)/map.cpp $(SOURCE)/map.h
	g++ $(CFLAG) -c $(SOURCE)/map.cpp -o $(OBJECT)/map.o

$(OBJECT)/player.o: $(SOURCE)/player.cpp $(SOURCE)/player.h
	g++ $(CFLAG) -c $(SOURCE)/player.cpp -o $(OBJECT)/player.o

$(OBJECT)/stat_bar.o: $(SOURCE)/stat_bar.cpp $(SOURCE)/stat_bar.h
	g++ $(CFLAG) -c $(SOURCE)/stat_bar.cpp -o $(OBJECT)/stat_bar.o

$(OBJECT)/tile.o: $(SOURCE)/tile.cpp $(SOURCE)/tile.h
	g++ $(CFLAG) -c $(SOURCE)/tile.cpp -o $(OBJECT)/tile.o

$(OBJECT)/tile_action.o: $(SOURCE)/tile_action.cpp $(SOURCE)/tile_action.h
	g++ $(CFLAG) -c $(SOURCE)/tile_action.cpp -o $(OBJECT)/tile_action.o

$(OBJECT)/tile_factory.o: $(SOURCE)/tile_factory.cpp $(SOURCE)/tile_factory.h
	g++ $(CFLAG) -c $(SOURCE)/tile_factory.cpp -o $(OBJECT)/tile_factory.o

$(OBJECT): $(OBJECT)/drutils.o $(OBJECT)/inventory.o \
	$(OBJECT)/map.o $(OBJECT)/player.o $(OBJECT)/stat_bar.o \
	$(OBJECT)/tile.o $(OBJECT)/tile_action.o $(OBJECT)/tile_factory.o \
	$(OBJECT)/board.o

# ********************
#   Binaries Files
# ********************

$(BINARY)/$(NAME): $(OBJECT) $(SOURCE)/$(NAME).cpp
	g++ $(CFLAG) $(SOURCE)/$(NAME).cpp $(OBJECT)/* -o $(BINARY)/$(NAME) 

clean:
	rm $(BINARY)/$(NAME); rm $(OBJECT)/*

run: $(BINARY)/$(NAME)
	$(BINARY)/$(NAME)

