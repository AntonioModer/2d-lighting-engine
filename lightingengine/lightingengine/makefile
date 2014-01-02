BIN = ./bin
SRC = ./src

all: 
	$(MAKE) -sC $(BIN) all && ln -sf $(BIN)/main main

clean:
	cd $(BIN) && $(MAKE) -s clean