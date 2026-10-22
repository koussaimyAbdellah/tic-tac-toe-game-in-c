
bin/game: build/main.o build/interface.o build/game_logic.o build/ai_stratigie.o include/interface.h
	mkdir -p bin
	gcc build/*.o -o bin/game

objc := build/game_logic.o build/ai_stratigie.o build/interface.o build/main.o
dep := $(objc:.o=.d)

-include $(dep)

build/main.o: src/main.c include/interface.h
	mkdir -p build
	gcc -Iinclude -MMD -MP src/main.c -c -o build/main.o

build/interface.o: src/interface.c include/interface.h include/game_logic.h include/ai_stratigie.h
	mkdir -p build
	gcc -Iinclude -MMD -MP src/interface.c -c -o build/interface.o

build/game_logic.o: src/game_logic.c include/game_logic.h
	mkdir -p build
	gcc -Iinclude -MMD -MP src/game_logic.c -c -o build/game_logic.o

build/ai_stratigie.o: src/ai_stratigie.c include/ai_stratigie.h include/game_logic.h
	mkdir -p build
	gcc -Iinclude -MMD -MP src/ai_stratigie.c -c -o build/ai_stratigie.o
#------------------------------------------------------------------#
# bin/test/game_test: build/test/game_logic.o build/test/interface.o build/test/test_game.o 
# 	mkdir -p bin/test/
# 	gcc -Iinclude build/test/*.o -o game_test

# build/test/game_logic.o: src/game_logic.c 
# 	mkdir -p build/test/
# 	gcc -Iinclude src/game_logic.c -c -o build/test/game_logic.o

# build/test/interface.o: src/interface.c 
# 	mkdir -p build/test/
# 	gcc -Iinclude src/interface.c -c -o build/test/interface.o

# build/test/test_game.o: test/test_game.c 
# 	mkdir -p build/test/
# 	gcc  test/test_game.c -c -o build/test/test_game.o
#-----------------------------------------------------------------#
.phony: clean run rebuild all 

all: bin/game

clean: 
	rm -f build/*.o bin/game

rebuild: clean all

run: bin/game
	mkdir -p bin
	bin/./game
