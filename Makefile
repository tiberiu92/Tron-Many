DIRECTORY := tron-bot
SOURCES   := $(DIRECTORY)/*.cpp
HEADERS   := $(DIRECTORY)/*.hpp

ifeq ($(OS), Windows_NT)
	PLATFORM := WINDOWS
else
	ifeq ($(shell uname), Linux)
		PLATFORM := LINUX
	endif
endif

WINDOWS_EXTENSION := .exe
LINUX_EXTENSION   := 
OUTPUT            := bot$($(PLATFORM)_EXTENSION)

ifeq ($(PLATFORM), WINDOWS)
	CLEANCMD := del
endif
ifeq ($(PLATFORM), LINUX)
	CLEANCMD := rm
endif

build: $(SOURCES)
	@g++ -o $(OUTPUT) -Wall $(SOURCES)

clean:
	@$(CLEANCMD) $(OUTPUT)
