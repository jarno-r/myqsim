
all: build myqsim

clean:
	-rm -rf build

.PHONY: all clean

build:
	mkdir -p build
	mkdir -p build/tests

CPPFLAGS = -std=c++23 -Isrc -Isrc/tests -g

SRCS = $(wildcard src/*.cpp src/*/*.cpp)
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))
DEPS = $(patsubst src/%.cpp, build/%.d, $(SRCS))

myqsim: $(OBJS)
	$(CXX) -o $@ $^

build/%.o: src/%.cpp build/%.d
	$(CXX) $(CPPFLAGS) -MMD -c -o $@ $<

build/%.d: ;

-include $(DEPS)
