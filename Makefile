# 211769757 Adi Ben Yehuda 208001677 Shahar Moshonov

CC = gcc
CFLAGS = -no-pie -fopenmp

TARGET = a.out
SRCS = main.c binary_tree.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@ -march=native -Wall -Wextra -std=c11 -lm

clean:
	rm -f $(TARGET)