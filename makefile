# Biến
CXX = g++
CXXFLAGS = -Wall -g -I./header -I./source
LDFLAGS = -lncurses -lpthread

TARGET = electricity_motorcycle_app

SRC = main.cpp source/electricity_motorcycle.cpp

# Quy tắc biên dịch
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Quy tắc dọn dẹp
clean:
	rm -f $(TARGET)