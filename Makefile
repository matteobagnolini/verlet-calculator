CPPFLAGS = -std=c++20 -Wall -Wpedantic -Werror
SFML_PATH = /usr/local/Cellar/sfml/2.6.1
SFML_INCLUDES = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: app.exe

app.exe: main.o
		g++ -o app.exe main.o $(CPPFLAGS) -I$(SFML_PATH)/include -L$(SFML_PATH)/lib $(SFML_INCLUDES)

main.o: main.cpp physics.hpp renderer.hpp math.hpp
		g++ -c main.cpp $(CPPFLAGS)