CXXFLAGS=-Wall

SOURCES_LIB=aes.c aesni.c sha512.c
SOURCES_GEN=crypto.cpp

SOURCES_MAIN=$(SOURCES_GEN) main.cpp
OBJECTS_MAIN=$(SOURCES_MAIN:.cpp=.o) $(SOURCES_LIB:.c=.o)

SOURCES_TEST=$(SOURCES_GEN) testing.cpp
OBJECTS_TEST=$(SOURCES_TEST:.cpp=.o) $(SOURCES_LIB:.c=.o)

all: main main-test

test: main-test
	./main-test

# Depends on all object files and main, links the final binary.
main: $(OBJECTS_MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Depends on all object files and test, links the test binary.
main-test: $(OBJECTS_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Automatic rule for all object files in build directory
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -fr $(OBJECTS_MAIN) $(OBJECTS_TEST)
