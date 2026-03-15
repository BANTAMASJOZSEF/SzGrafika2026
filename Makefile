CC = gcc
CFLAGS = -I. -Wall -g
LDFLAGS = -lfreeglut -lopengl32 -lglu32 -lm

SOURCES = main.c app.c scene.c helicopter.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = helikopter_szimulator

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE).exe