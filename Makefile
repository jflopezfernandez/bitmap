
vpath %.c src
vpath Doxyfile docs

RM       := rm -f

CC       := gcc
CFLAGS   := -std=c17 -Wall -Wextra -Wpedantic -Og -ggdb3 -fanalyzer
CPPFLAGS := -Iinclude -D_GNU_SOURCE
LDFLAGS  := -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now
LIBS     := -lm

SRCS     := $(notdir $(wildcard src/*.c))
OBJS     := $(patsubst %.c,%.o,$(SRCS))

TARGET   := bitmap

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $^

docs: Doxyfile
	doxygen $<

.PHONY: clean
clean:
	$(RM) $(OBJS) *.bmp $(TARGET)
