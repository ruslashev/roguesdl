CXX = clang++
CXXFLAGS = -Wall -Wextra -g -ggdb -std=c++0x -O0
OBJS = $(patsubst src/%.cpp, objs/%.o, $(shell find src -type f -name "*.cpp" ))
EXECNAME = roguesdl
LDFLAGS = -L/usr/local/lib #-L./libs
LIBS = -lSDL2_image -lSDL2_ttf -lSDL2

objs/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(EXECNAME): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

clean:
	-rm -f objs/*.o $(EXECNAME)
