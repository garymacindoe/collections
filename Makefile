CPPFLAGS = -Iinclude
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wconversion -O2
LDLIBS = -lcunit

SEARCH_OBJS = src/linear_search.o src/binary_search.o
SORT_OBJS = src/insertion_sort.o src/selection_sort.o src/merge_sort.o src/bubble_sort.o src/heap_sort.o
HEAP_OBJS = src/make_heap.o

.PHONY: all test clean

all: libcollections.a test_sort test_search test_heap

test: test_sort test_search test_heap
	./test_sort
	./test_search
	./test_heap

clean:
	$(RM) libcollections.a
	$(RM) test_sort test_search test_heap
	$(RM) $(SORT_OBJS) $(SEARCH_OBJS) $(HEAP_OBJS)
	$(RM) cunit/cunit_automated.o cunit/cunit_basic.o cunit/cunit_console.o
	$(RM) CUnitAutomated-Results.xml CUnitAutomated-Listing.xml
	$(RM) test/test_sort.o test/test_search.o test/test_heap.o

libcollections.a: $(SORT_OBJS) $(SEARCH_OBJS) $(HEAP_OBJS)
	$(AR) $(ARFLAGS) $(@) $(^)

src/insertion_sort.o: include/sort.h src/copy.h
src/selection_sort.o: include/sort.h src/swap.h
src/merge_sort.o: include/sort.h src/copy.h
src/bubble_sort.o: include/sort.h src/swap.h

src/linear_search.o: include/search.h
src/binary_search.o: include/search.h

src/make_heap.o: include/heap.h src/heapify.h src/swap.h

test/test_sort.o: include/sort.h
test/test_search.o: include/search.h
test/test_heap.o: include/heap.h

test_sort: test/test_sort.o cunit/cunit_basic.o libcollections.a
	$(CC) $(LDFLAGS) -o $(@) $(^) $(LOADLIBES) $(LDLIBS)

test_search: test/test_search.o cunit/cunit_basic.o libcollections.a
	$(CC) $(LDFLAGS) -o $(@) $(^) $(LOADLIBES) $(LDLIBS)

test_heap: test/test_heap.o cunit/cunit_basic.o libcollections.a
	$(CC) $(LDFLAGS) -o $(@) $(^) $(LOADLIBES) $(LDLIBS)
