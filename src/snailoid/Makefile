INCLUDE = \
	-I"../config/include"

LIBS = -lSDL2 -lSDL2_gfx

CC = g++
CFLAGS = -Wall -Wextra -std=c++14 $(LIBS) $(INCLUDE)

SRC = \
	collisions.cpp \
	geometry.cpp \
	main.cpp \


BIN = snailoid
DEP = $(SRC:.cpp=.d)
OBJ = $(SRC:.cpp=.o)

all: $(BIN)

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

# Autogenerate dependency files (*.d) for sources
%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(DEP)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ)

.PHONY: clean
clean:
	rm -f $(DEP) $(OBJ) $(BIN)
