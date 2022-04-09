SRC_DIR = src
OBJ_DIR = bin
TEST_SRC_DIR = $(SRC_DIR)/unit_tests
TEST_OBJ_DIR = $(OBJ_DIR)/unit_tests

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = ${subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.cpp=.o)}
PROG = limecell
TEST_PROG = unit_test

TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.cpp) $(filter-out $(SRC_DIR)/main.cpp, $(SRC))
TEST_OBJ = ${subst $(SRC_DIR), $(OBJ_DIR), $(TEST_SRC:.cpp=.o)}

BOOST_ROOT := /usr/include/boost
BOOST_REGEX := boost_regex
BOOST_FS := boost_filesystem
BOOST_DLL := boost_dll
BOOST_UNIT_TEST := boost_unit_test_framework

LDFLAGS = -L${BOOST_ROOT} -l${BOOST_REGEX} -l${BOOST_FS}
CFLAGS = -g

all: $(PROG) | $(OBJ_DIR)

test: $(TEST_PROG)

$(PROG): $(OBJ)
	g++ -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	g++ -c -o $@ $< $(CFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TEST_PROG) : $(TEST_OBJ)
	g++ -o $@ $^ $(LDFLAGS) -l$(BOOST_UNIT_TEST)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp | $(TEST_OBJ_DIR)
	g++ -c -o $@ $< $(CFLAGS)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

.PHONY: clean
clean:
	rm -f $(OBJ) $(TEST_OBJ) $(PROG) $(TEST_PROG)