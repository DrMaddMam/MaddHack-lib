# imma be real i just got this from stack overflow

# Toolchain
CC      ?= gcc
AR      ?= ar
RANLIB  ?= ranlib
PICFLAGS:= -fPIC
CFLAGS  ?= -O2 -Wall -Wextra -std=c11 $(PICFLAGS) -I.    # top-level include

# Library names
LIBNAME ?= maddhack
STATIC_LIB := lib$(LIBNAME).a
SHARED_LIB := lib$(LIBNAME).so

# You can override to exclude files (space-separated basenames)
# e.g. EXCLUDE = main.c test.c
EXCLUDE ?=

# Gather source files recursively from this directory
SRCS := $(shell find . -type f -name '*.c')
# Filter out excluded basenames (if any)
ifneq ($(strip $(EXCLUDE)),)
  EXCL_PATTERNS := $(addprefix ./,$(EXCLUDE))
  # remove any SRCS entries that match an excluded basename
  SRCS := $(filter-out $(EXCL_PATTERNS),$(SRCS))
endif

# Convert .c -> .o (placed alongside sources)
OBJS := $(SRCS:.c=.o)

.PHONY: all static shared clean install uninstall deps

# Default: build both libs
all: static shared

# static lib target
static: CFLAGS +=     # keep default (no -fPIC required but allowed)
static: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	@echo "Creating static library $@"
	$(AR) rcs $@ $(OBJS)
	$(RANLIB) $@ || true

# shared lib target: compile objects with -fPIC then link shared object
# Force PIC compile for shared build by rebuilding .o with PIC flags when needed.
shared: CFLAGS += $(PICFLAGS)
shared: $(SHARED_LIB)

# Link shared from all .o (which were built with PICFLAGS above)
$(SHARED_LIB): $(OBJS)
	@echo "Linking shared library $@"
	$(CC) -shared -Wl,-soname,$(SHARED_LIB) -o $@ $(OBJS)

# Generic rule: compile .c -> .o (keeps directory structure)
# Uses current CFLAGS (for shared target CFLAGS includes -fPIC)
%.o: %.c
	@echo "Compiling $< ..."
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# clean
clean:
	@echo "Cleaning object files and libraries..."
	-find . -type f -name '*.o' -print -delete
	-rm -f $(STATIC_LIB) $(SHARED_LIB)

# Install to PREFIX (headers + libraries)
PREFIX ?= /usr/local
INCDIR := $(PREFIX)/include/$(LIBNAME)
LIBDIR := $(PREFIX)/lib

install: all
	@echo "Installing headers to $(INCDIR) and libs to $(LIBDIR)..."
	@mkdir -p $(INCDIR) $(LIBDIR)
	# Copy headers (all .h under this tree)
	-find . -type f -name '*.h' -exec cp --parents --parents \{\} $(INCDIR)/.. \;
	# The above uses cp --parents to preserve subdirs; if your cp lacks --parents, see note below.
	cp -f $(STATIC_LIB) $(LIBDIR)/
	cp -f $(SHARED_LIB) $(LIBDIR)/
	@echo "Done."

# uninstall
uninstall:
	@echo "Removing installed libraries..."
	-rm -f $(LIBDIR)/$(STATIC_LIB) $(LIBDIR)/$(SHARED_LIB)
	@echo "Remove headers under $(INCDIR) manually if desired."

# convenience: build just objects (no link)
deps: $(OBJS)

# show config
config:
	@echo "CC=$(CC)"
	@echo "CFLAGS=$(CFLAGS)"
	@echo "SRCS count=$(words $(SRCS))"
	@echo "OBJS count=$(words $(OBJS))"
	@echo "STATIC_LIB=$(STATIC_LIB)"
	@echo "SHARED_LIB=$(SHARED_LIB)"

