build: tron-bot/main.cpp tron-bot/world.cpp
	g++ -o bot -Wall tron-bot/main.cpp tron-bot/main.cpp

clean:
	rm -rf bot