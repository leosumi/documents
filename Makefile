#
# Makefile
#
# Need makedepend to create dependencies in makefiles
#
# .o files are in BUILD_DIR
# .cpp and .hpp files are in SRC_DIR (with no subdirectory)
#

# mode con be debug or release
MODE = debug

CC = g++
EXEC = app

LDLIBS =

SRC_DIR = src
BUILD_DIR = build

# extra warnings
WEXTRA = yes
WSTYLE = yes
WPOINTER = yes
WCONVERSION = yes
WSWITCH = yes

# -Werror and -Wfatal-errors
WERROR = no
WFATALERRORS = no

ifeq ($(MODE), debug)
	CFLAGS = -pedantic -Wall -Wextra -g
	LDFLAGS =

	ifeq ($(WEXTRA), yes)
		CFLAGS += -Wshadow -Wfloat-equal -Wredundant-decls -Woverloaded-virtual -Winit-self \
			  -Wmissing-include-dirs -Wmissing-declarations -Wunreachable-code -Winline \
			  -Wnon-virtual-dtor
	endif
	ifeq ($(WSTYLE), yes)
		CFLAGS += -Weffc++
	endif
	ifeq ($(WPOINTER), yes)
		CFLAGS += -Wzero-as-null-pointer-constant -Wpointer-arith -Wcast-qual -Wcast-align
	endif
	ifeq ($(WCONVERSION), yes)
		CFLAGS += -Wconversion -Wdouble-promotion -Wold-style-cast
	endif
	ifeq ($(WSWITCH), yes)
		CFLAGS += -Wswitch-default -Wswitch-enum
	endif
	ifeq ($(WERROR), yes)
		CFLAGS += -Werror
	endif
	ifeq ($(WFATALERRORS), yes)
		CFLAGS += -Wfatal-errors
	endif

else ifeq ($(MODE), release)
	CFLAGS = -O2 -s
	LDFLAGS =
endif
CFLAGS += -std=c++11

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

all: directory depend $(EXEC)
	$(info Compiled in $(MODE) mode)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean distclean

clean:
	@rm -rf $(OBJ) $(wildcard *.bak)

distclean: clean
	@rm -rf $(EXEC)

directory:
	@mkdir -p $(BUILD_DIR) $(SRC_DIR)

depend:
	@makedepend $(SRC)
