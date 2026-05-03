CC = gcc
CFLAGS = -Iinclude -I. -Wall -g

LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglu32 -lm

SRC_DIR = src
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/app.c $(SRC_DIR)/scene.c $(SRC_DIR)/helicopter.c $(SRC_DIR)/loader.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = helikopter_szimulator

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE).exe