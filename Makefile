CPPFLAGS = -Iinclude
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wconversion -O2
LDLIBS = -lcunit

SEARCH_OBJS = src/linear_search.o src/binary_search.o

.PHONY: all test clean

all: libcollections.a test_sort test_search

test: test_sort test_search
	./test_sort
	./test_search

clean:
	$(RM) libcollections.a
	$(RM) test_sort test_search
	$(RM) src/insertion_sort.o src/selection_sort.o src/merge_sort.o src/bubble_sort.o $(SEARCH_OBJS)
	$(RM) cunit/cunit_automated.o cunit/cunit_basic.o cunit/cunit_console.o
	$(RM) CUnitAutomated-Results.xml CUnitAutomated-Listing.xml
	$(RM) test/test_sort.o test/test_search.o

libcollections.a: src/insertion_sort.o src/selection_sort.o src/merge_sort.o src/bubble_sort.o $(SEARCH_OBJS)
	$(AR) $(ARFLAGS) $(@) $(^)

src/insertion_sort.o: include/sort.h
src/selection_sort.o: include/sort.h
src/merge_sort.o: include/sort.h
src/bubble_sort.o: include/sort.h

src/linear_search.o: include/search.h
src/binary_search.o: include/search.h

test/test_sort.o: include/sort.h
test/test_search.o: include/search.h

test_sort: test/test_sort.o cunit/cunit_basic.o libcollections.a
	$(CC) $(LDFLAGS) -o $(@) $(^) $(LOADLIBES) $(LDLIBS)

test_search: test/test_search.o cunit/cunit_basic.o libcollections.a
	$(CC) $(LDFLAGS) -o $(@) $(^) $(LOADLIBES) $(LDLIBS)
