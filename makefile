SRC_DIR   = src
OBJ_DIR   = obj
TST_OBJ_DIR = testobj
BIN_DIR   = bin

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TST_SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
TST_SOURCES := $(filter-out $(wildcard $(SRC_DIR)/main.cpp), $(TST_SOURCES))
TST_OBJECTS := $(TST_SOURCES:$(SRC_DIR)/%.cpp=$(TST_OBJ_DIR)/%.o)

.PHONEY: dingoo
dingoo:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@make -f makefile.dingoo

.PHONEY: test_dingoo
test_dingoo:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(TST_OBJ_DIR)
	@make -f makefiletest.dingoo

.PHONEY: osx
osx:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@make -f makefile.osx

.PHONEY: test_osx
test_osx:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(TST_OBJ_DIR)
	@make -f makefiletest.osx

.PHONEY: debug_osx
debug_osx:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@make -f makefiledebug.osx

.PHONEY: clean
clean:
	@rm -f $(BIN_DIR)/*
	@rm -f $(OBJ_DIR)/*
	@rm -f $(TST_OBJ_DIR)/*
