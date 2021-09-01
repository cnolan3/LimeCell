SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
PROG = limecell

LDFLAGS = -g
CFLAGS = -g

all: $(PROG)

%.o: %.cpp
	g++ -c -o $@ $< $(CFLAGS)

$(PROG): $(OBJ)
	g++ -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) limecell