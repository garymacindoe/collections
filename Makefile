CPPFLAGS = -Iinclude
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wconversion -O2
LDLIBS = -lcunit

.PHONY: all test clean

all: libcollections.a test_sort

test: test_sort
	./test_sort

clean:
	$(RM) libcollections.a
	$(RM) test_sort
	$(RM) src/insertion_sort.o src/selection_sort.o src/merge_sort.o
	$(RM) cunit/cunit_automated.o cunit/cunit_basic.o cunit/cunit_console.o
	$(RM) CUnitAutomated-Results.xml CUnitAutomated-Listing.xml
	$(RM) test/test_sort.o

libcollections.a: src/insertion_sort.o src/selection_sort.o src/merge_sort.o src/bubble_sort.o
	$(AR) $(ARFLAGS) $(@) $(^)

src/insertion_sort.o: include/sort.h src/copy.h
src/selection_sort.o: include/sort.h src/swap.h
src/merge_sort.o: include/sort.h src/copy.h
src/bubble_sort.o: include/sort.h src/swap.h

test/test_sort.o: include/sort.h

test_sort: test/test_sort.o cunit/cunit_basic.o libcollections.a
	$(CC) $(LDFLAGS) -o $(@) $(^) $(LOADLIBES) $(LDLIBS)
