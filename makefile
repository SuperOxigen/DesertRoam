COMPILER = g++
CFLAG = -std=c++11
SRCTYPE = cpp
HDRTYPE = h
SOURCE = src
BINARY = bin
NAME = desert_run

all: $(BINARY)

build: $(BINARY)

$(BINARY): $(SOURCE)/*.$(SRCTYPE) $(SOURCE)/*.$(HDRTYPE)
	g++ -std=c++11 -o $(BINARY)/$(NAME) $(SOURCE)/*.$(SRCTYPE)

clean:
	rm $(BINARY)/*

run: $(BINARY)
	$(BINARY)/$(NAME)

