CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=gnu89
SRC=main.c printf.c
OBJ=$(SRC:.c=.o)
EXEC=printf

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
