CXX = g++
CXXFLAGS = -O2 -std=c++17

SRC_DIR = ./src
SRCS = $(SRC_DIR)/test.cpp \
       $(SRC_DIR)/generateArr.cpp \
       $(SRC_DIR)/parseRead.cpp \
       $(SRC_DIR)/heapSort.cpp \
       $(SRC_DIR)/shellSort.cpp \
       $(SRC_DIR)/insertSort.cpp \
       $(SRC_DIR)/quickSort.cpp \
       $(SRC_DIR)/configuration.cpp \
       ./main.cpp

TARGET = zadanie_1

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

