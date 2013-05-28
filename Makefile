CXXFLAGS = -Wall -g -std=c++0x -Iinclude
OBJS = $(patsubst src/%.cpp, objs/%.o, $(shell find src -type f -name "*.cpp" ))
EXECNAME = roguesdl
LDFLAGS = -Llibs
LIBS = -lSDL2

objs/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(EXECNAME): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
	-rm -f objs/*.o $(EXECNAME)
