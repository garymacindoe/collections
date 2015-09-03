CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wconversion -Werror -O2 -pipe

.PHONY: all test clean

all:
	echo > /dev/null

test:
	true

clean:
	$(RM) *.o
