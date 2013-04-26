SOURCES = tron-bot/main.cpp tron-bot/world.cpp
HEADERS = tron-bot/world.hpp
OUTPUT  = bot

build: $(SOURCES)
	g++ -o $(OUTPUT) -Wall $(SOURCES)

clean:
	rm -rf $(OUTPUT)
