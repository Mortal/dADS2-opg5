CXXFLAGS=-std=gnu++0x -Wall -Wextra

all: suffix

suffix: suffix.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) suffix
