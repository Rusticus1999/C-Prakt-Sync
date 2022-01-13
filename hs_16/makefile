PROGRAM = hs_16
SOURCES.c = $(PROGRAM).c

SOURCES = \
$(SOURCES.H) \
$(SOURCES.c)

OBJECTS = \
$(SOURCES.c:%.c%=%.o)

CC = gcc

CFLAGS = -std=c99 -O3 -Wall -Wconversion -Wfatal-errors
LDLIBS = -lm

all:	$(PROGRAM)

$(PROGRAM): $(SOURCES.c) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

clean:
	rm -rf $(PROGRAM)

run:
	./$(PROGRAM)

indent:
	indent -gnu -cdw -npsl -bli0 $(SOURCES.c)
