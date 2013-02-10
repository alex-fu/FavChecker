CC=gcc
CXX=g++
CFLAGS=-Wall -g
CPPFLAGS=
CXXFLAGS+=-D_UNIT_TEST
#CXXFLAGS+=-D_DEBUG 
LDFLAGS=-lboost_unit_test_framework -lboost_date_time

UNITTEST_OBJS:=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
UNITTEST=test

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

# -Note-: LDFLAGS should be after OBJS because of the boost_unit_test_framework
$(UNITTEST): $(UNITTEST_OBJS)
	$(CXX) $(UNITTEST_OBJS) $(LDFLAGS) -o $@

all: $(UNITTEST)


.PHONY: clean

clean:
	rm *.o $(UNITTEST)

