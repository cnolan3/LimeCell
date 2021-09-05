SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
PROG = limecell

BOOST_ROOT := /usr/include/boost
BOOST_REGEX := boost_regex

LDFLAGS = -L${BOOST_ROOT} -l${BOOST_REGEX}
CFLAGS = -g

all: $(PROG)

%.o: %.cpp
	g++ -c -o $@ $< $(CFLAGS)

$(PROG): $(OBJ)
	g++ -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) limecell