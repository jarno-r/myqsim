
all: build myqsim

clean:
	-rm -rf build

.PHONY: all clean

build:
	mkdir -p build

SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))
DEPS = $(patsubst src/%.cpp, build/%.d, $(SRCS))

myqsim: $(OBJS)
	$(CXX) -o $@ $^

build/%.o: src/%.cpp build/%.d
	$(CXX) -MMD -c -o $@ $<

build/%.d: ;

-include $(DEPS)
