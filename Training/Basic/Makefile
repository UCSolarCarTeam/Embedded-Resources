# Makefile for the Embedded C exercises (uses gcc)
#
#   make ex1a        build and run exercise 1a
#   make sol-ex1a    build and run the SOLUTION for 1a
#   make check       compile every exercise without running (catches typos)
#   make clean       delete the build folder
#   make help        show this help
#
# Exercises: ex1a ex1b ex1c  ex2a ex2b ex2c  ex3a ex3b ex3c  ex4a ex4b ex4c

CC     = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter -g -I.
BUILD  = build

EXERCISES = ex1a ex1b ex1c ex2a ex2b ex2c ex3a ex3b ex3c ex4a ex4b ex4c

.DEFAULT_GOAL := help
.PHONY: help check clean

# Find the source file for an exercise name, e.g. ex1a -> Lesson1/ex1a_fixed_width.c
find_src = $(firstword $(wildcard Lesson*/$(1)_*.c $(1)_*.c))
find_sol = $(firstword $(wildcard solutions/$(1)_*.c solutions/*/$(1)_*.c))

# $(1) = source file, $(2) = name of the program to build
define build_and_run
if [ -z "$(1)" ]; then echo "Could not find the source file for $(2)"; exit 1; fi; \
mkdir -p $(BUILD); \
echo "$(CC) $(CFLAGS) $(1) -o $(BUILD)/$(2)"; \
$(CC) $(CFLAGS) $(1) -o $(BUILD)/$(2) || exit 1; \
echo; \
./$(BUILD)/$(2) || true
endef

# Creates the targets  exNN  and  sol-exNN  for each exercise
define EXERCISE
.PHONY: $(1) sol-$(1)

$(1):
	@$$(call build_and_run,$$(call find_src,$(1)),$(1))

sol-$(1):
	@$$(call build_and_run,$$(call find_sol,$(1)),sol-$(1))
endef

$(foreach e,$(EXERCISES),$(eval $(call EXERCISE,$(e))))

help:
	@echo "Usage:"
	@echo "  make ex1a       build and run an exercise ($(EXERCISES))"
	@echo "  make sol-ex1a   build and run the solution for that exercise"
	@echo "  make check      compile everything (no running)"
	@echo "  make clean      remove the build folder"

check:
	@mkdir -p $(BUILD)
	@for f in Lesson*/ex*.c solutions/ex*.c solutions/*/ex*.c; do \
	    [ -f "$$f" ] || continue; \
	    echo "compile $$f"; \
	    $(CC) $(CFLAGS) -fsyntax-only $$f || exit 1; \
	done
	@echo "All files compile."

clean:
	rm -rf $(BUILD)
