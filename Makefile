CC = gcc
CFLAGS = -Wall -Wextra -fopenmp

TARGETS = istogramma

SRC = istogramma.cpp

all: $(TARGETS)

istogramma: $(SRC)
	$(CC) $(CFLAGS) -o istogramma $(SRC)

run: istogramma
	./istogramma

clean:
	rm -f $(TARGETS)
