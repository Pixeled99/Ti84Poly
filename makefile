# ----------------------------
# Makefile Options
# ----------------------------

NAME = POLY
DESCRIPTION = "Find a zero for a polynomial"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)