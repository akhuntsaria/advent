CXX = g++
CXXFLAGS = -std=c++23 -Ofast

TARGET = a.out

all: run

build: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: build
	time ./$(TARGET) $(INPUT)

clean:
	rm -f $(TARGET)

.PHONY: all build run clean
