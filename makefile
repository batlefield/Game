TARGET = ./bin/Run
LIBS = -lSDLmain -lSDL_image -ljpeg -lpng -ltiff -lwebp -lSDL -lGL 
CC = g++
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
HEADERS = $(wildcard ./src/*.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f ./src/*.o
	-rm -f $(TARGET)
run:
	./bin/Run
	
