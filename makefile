
bin/game: build/main.o build/interface.o build/game_logic.o build/ai_stratigie.o include/interface.h
	mkdir -p bin
	gcc build/*.o -o bin/game

build/main.o: src/main.c include/interface.h
	mkdir -p build
	gcc -Iinclude src/main.c -c -o build/main.o

build/interface.o: src/interface.c include/interface.h include/game_logic.h include/ai_stratigie.h
	mkdir -p build
	gcc -Iinclude src/interface.c -c -o build/interface.o

build/game_logic.o: src/game_logic.c include/game_logic.h
	mkdir -p build
	gcc -Iinclude src/game_logic.c -c -o build/game_logic.o

build/ai_stratigie.o: src/ai_stratigie.c include/ai_stratigie.h include/game_logic.h
	mkdir -p build
	gcc -Iinclude src/ai_stratigie.c -c -o build/ai_stratigie.o

.phony: clean run rebuild all push

all: bin/game

clean: 
	rm -f build/*.o bin/game

rebuild: clean all

run: bin/game
	bin/./game
