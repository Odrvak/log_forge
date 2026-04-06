CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -O2
TARGET  = logforge

SRCS    = src/main.c \
          src/core/file_reader.c \
          src/core/parser.c \
          src/analysis/stats.c \
          src/analysis/filter.c \
          src/cli/args.c \
          src/cli/commands.c \
          src/output/print.c

OBJS    = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -Isrc -c -o $@ $<

clean:
	del /Q $(subst /,\,$(OBJS)) $(TARGET).exe 2>NUL || \
	rm -f $(OBJS) $(TARGET)
