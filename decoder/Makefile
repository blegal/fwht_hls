CXX = g++

# To be adapted if needed
DEPSFLAGS = -MMD
WARNFLAGS = -Wall -Werror -Wno-unknown-pragmas -Wno-unused-label
CSTDFLAGS = -std=c++14
OPTSFLAGS = -O2

CXXFLAGS = $(WARNFLAGS) $(DEPSFLAGS) $(CSTDFLAGS) $(OPTSFLAGS)
LDFLAGS = $(OPTSFLAGS) $(CSTDFLAGS) $(WARNFLAGS)

EXE = bin/main

all: $(EXE)

bin/main: obj/main.o obj/decoder.o
	[ -d bin ] || mkdir bin
	$(CXX) -o $@ $^

obj/%.o: src/%.cpp
	[ -d obj ] || mkdir obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj/*.o
	rm -rf bin/main

-include obj/*.d
