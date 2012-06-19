CXXFLAGS=-std=gnu++0x -Wall -Wextra

all: 09

09: 09.cpp suffix.h
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) 09
