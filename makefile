
FLAGS = -std=c++20

# Objektfiler
OBJS = build/main.o build/run.o build/setup.o build/library.o
# Slutligt program
TARGET = program

all: $(TARGET)

# Länkning
$(TARGET): $(OBJS)
	g++ $(FLAGS) -o $(TARGET) $(OBJS)

# Kompilering av varje fil
build/main.o: src/main.cc
	g++ $(FLAGS) -c src/main.cc -o build/main.o

build/run.o: src/run.cc
	g++ $(FLAGS) -c src/run.cc -o build/run.o

build/setup.o: src/setup.cc
	g++ $(FLAGS) -c src/setup.cc -o build/setup.o

build/library.o: src/library.cc
	g++ $(FLAGS) -c src/library.cc -o build/library.o

# städning
clean:
	rm -f $(OBJS) $(TARGET)