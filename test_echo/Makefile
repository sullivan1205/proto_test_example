CC = g++
CXXFLAGS = -std=c++11
TARGET = test_echo
SOURCE = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SOURCE))
INCLUDE = -I./
LIBS = -lproto -lprotobuf
LIBPATH = -L../proto

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LIBPATH) $(LIBS)

%.o: %.c
	protoc -I=./ --cpp_out=./ ./echo.proto
	$(CC) $(CXXFLAGS) $(INCLUDE) -o $@ -c $^                                                                                                                                                                         

.PHONY:clean
clean:
	rm -f *.o $(TARGET)
