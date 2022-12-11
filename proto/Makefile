CC = g++
CXXFLAGS = -std=c++11
TARGET = libproto.a
SOURCE = $(wildcard *.cc)
OBJS = $(patsubst %.cc, %.o, $(SOURCE))
INCLUDE = -I./

$(TARGET): $(OBJS)
	ar rcv $(TARGET) $(OBJS)

%.o: %.cc
	$(CC) $(CXXFLAGS) $(INCLUDE) -o $@ -c $^

.PHONY:clean proto

proto:
	protoc -I=./ --cpp_out=./ *.proto

clean:
	rm -f *.o $(TARGET) *.pb.cc *.pb.h
