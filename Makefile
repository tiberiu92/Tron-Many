build: tron-bot/main.cpp
	g++ -o bot -Wall tron-bot/main.cpp

clean:
	rm -rf bot