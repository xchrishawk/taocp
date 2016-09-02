# -- Variables --

# Project name and inputs
PROJECT_NAME 		:= taocp
LIB_MODULES		:= astack
TEST_MODULES		:= main astack_tests

# Directories
ROOT_DIR		:= .
SRC_DIR			:= $(ROOT_DIR)
DEP_DIR			:= $(ROOT_DIR)/dep
OBJ_DIR			:= $(ROOT_DIR)/obj
BIN_DIR			:= $(ROOT_DIR)/bin

# Files for library
LIB_SRCS		:= $(addprefix $(SRC_DIR)/,$(addsuffix .c,$(LIB_MODULES)))
LIB_OBJS		:= $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(LIB_MODULES)))
LIB_DEPS		:= $(addprefix $(DEP_DIR)/,$(addsuffix .d,$(LIB_MODULES)))
LIB_TARGET		:= $(BIN_DIR)/lib$(PROJECT_NAME).a

# Files for unit tests
TEST_SRCS		:= $(addprefix $(SRC_DIR)/,$(addsuffix .c,$(TEST_MODULES)))
TEST_OBJS		:= $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(TEST_MODULES)))
TEST_DEPS		:= $(addprefix $(DEP_DIR)/,$(addsuffix .d,$(TEST_MODULES)))
TEST_TARGET		:= $(BIN_DIR)/$(PROJECT_NAME)-tests

# Misc
UNITTEST_SYMBOL		:= LIBTAOCP_TEST

# Toolchain flags
CPPFLAGS		:=
CFLAGS			:= -g -Wall -Wpedantic -Werror -std=gnu99
LDFLAGS			:= -g
LIBS			:=

# Target-specific flags
$(TEST_OBJS): CPPFLAGS	+= -D$(UNITTEST_SYMBOL)
$(TEST_DEPS): CPPFLAGS	+= -D$(UNITTEST_SYMBOL)
$(TEST_TARGET): LIBS	+= -lcunit

# -- Targets --

.PHONY: all rebuild test clean

# Build all targets and run unit tests
all: $(LIB_TARGET) $(TEST_TARGET) test

# Run unit tests
test: $(TEST_TARGET)
	$(TEST_TARGET)

# Clean, build all targets, and run unit tests
rebuild: clean all

# Unit test executable
$(TEST_TARGET): $(TEST_OBJS) $(LIB_TARGET)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

# Static library
$(LIB_TARGET): $(LIB_OBJS)
	$(AR) rcs $@ $^

# Build objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

# Build dependencies
$(DEP_DIR)/%.d: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) -MM -MT $(OBJ_DIR)/$(notdir $(basename $@)).o -MT $@ $< > $@

# Clean project
clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(DEP_DIR)/*.d
	$(RM) $(LIB_TARGET)
	$(RM) $(TEST_TARGET)

# Include dependency files
-include $(LIB_DEPS)
-include $(TEST_DEPS)
