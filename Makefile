SRC_DIR = src
OBJ_DIR = bin

SRC = $(wildcard src/*.cpp)
OBJ = ${subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.cpp=.o)}
PROG = limecell
TEST_PROG = unit_test

TEST_SRC = $(wildcard src/unit_tests/*.cpp) $(filter-out src/main.cpp, $(SRC))
TEST_OBJ = ${subst $(SRC_DIR), $(OBJ_DIR), $(TEST_SRC:.cpp=.o)}

BOOST_ROOT := /usr/include/boost
BOOST_REGEX := boost_regex
BOOST_FS := boost_filesystem
BOOST_DLL := boost_dll
BOOST_UNIT_TEST := boost_unit_test_framework

LDFLAGS = -L${BOOST_ROOT} -l${BOOST_REGEX} -l${BOOST_FS}
CFLAGS = -g

all: $(PROG)

test: $(TEST_PROG)

$(PROG): $(OBJ)
	g++ -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp
	g++ -c -o $@ $< $(CFLAGS)

$(TEST_PROG) : $(TEST_OBJ)
	g++ -o $@ $^ $(LDFLAGS) -l$(BOOST_UNIT_TEST)

$(OBJ_DIR)/%.o: src/unit_tests/%.cpp
	g++ -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) $(TEST_OBJ) $(PROG) $(TEST_PROG)