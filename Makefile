CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wconversion -Werror -O2 -pipe

.PHONY: all test clean

all:
	echo > /dev/null

test:
	true

clean:
	$(RM) cunit/cunit_automated.o cunit/cunit_basic.o cunit/cunit_console.o
	$(RM) CUnitAutomated-Results.xml CUnitAutomated-Listing.xml
	$(RM) *.o
