CC=gcc
# library source folder
SRC=src
SOURCES=$(wildcard $(SRC)/*.c)
OBJECTS=$(patsubst $(SRC)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
INCLUDES=-Iinc

# Unity
UNITY_SOURCE=$(TEST)/Unity/src/unity.c
UNITY_OBJECT=$(BUILD_DIR)/unity.o

# Test directory
TEST=test
# Test obj directory
BUILD_DIR=$(TEST)/build
BIN_DIR=$(TEST)/bin
TEST_SOURCES=$(wildcard $(TEST)/*.c)
BUILD_DIRECTS=$(patsubst $(TEST)/%.c, $(BUILD_DIR)/%.o, $(TEST_SOURCES))
TEST_TARGETS=$(patsubst $(TEST)/%.c, $(BIN_DIR)/%, $(TEST_SOURCES))


all: $(TEST_TARGETS)

test: $(TEST_TARGETS)

clean:
	rm $(BUILD_DIR)/* -f
	rm $(BIN_DIR)/* -f


print:
	@echo Test Sources $(TEST_SOURCES)
	@echo Test Objects $(BUILD_DIRECTS)
	@echo Test Targets $(TEST_TARGETS)


# Build each test
$(TEST_TARGETS) : $(BUILD_DIRECTS) $(OBJECTS) $(UNITY_OBJECT)
	$(CC) $< $(OBJECTS) $(UNITY_OBJECT) -o $@

# Compile each test file into obj
$(BUILD_DIR)/%.o : $(TEST)/%.c
	$(CC) $(INCLUDES) $< -c -o $@

# Compile each library file into obj
$(BUILD_DIR)/%.o: $(SRC)/%.c
	$(CC) $(INCLUDES) $< -c -o $@

# Compile unity
$(UNITY_OBJECT): $(UNITY_SOURCE)
	$(CC) $< -c -o $@

