CXX := gcc
WARN := -Wall -Werror -Wextra -pedantic 
OPT := -O3
CFLAGS := $(OPT) $(WARN)

HEADERS := types.h
OBJECTS := bench.o
DEPS := $(HEADERS) $(OBJECTS)

bench.png: data.csv pyproject.toml plot.py
	poetry run python plot.py

data.csv: main
	./$^ > $@

main: main.c $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CXX) -c $< $(CFLAGS)

clean:
	-rm -f *.o
	-rm -f *.png
	-rm -f *.csv
	-rm -f main

.PHONY: all clean
