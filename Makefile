CC=gcc
CXX=g++
CFLAGS=-Wall -g
CPPFLAGS=
CXXFLAGS+=-D_UNIT_TEST
#CXXFLAGS+=-D_DEBUG 
LDFLAGS=

UNITTEST_OBJS:=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
UNITTEST=test

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

$(UNITTEST): $(UNITTEST_OBJS)
	$(CXX) $(LDFLAGS) $(UNITTEST_OBJS) -o $@

all: $(UNITTEST)


.PHONY: clean

clean:
	rm *.o $(UNITTEST)

