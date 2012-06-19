CXXFLAGS=-std=gnu++0x -Wall -Wextra

all: dADS2-09-5b dADS2-09a-5b dADS2-09a-5c

dADS2-09-5b: dADS2-09-5b.cpp suffix.h
	$(CXX) $(CXXFLAGS) -o $@ $<

dADS2-09a-5b: dADS2-09a-5b.cpp suffix.h
	$(CXX) $(CXXFLAGS) -o $@ $<

dADS2-09a-5c: dADS2-09a-5c.cpp suffix.h
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	$(RM) dADS2-09-5b dADS2-09a-5b dADS2-09a-5c
