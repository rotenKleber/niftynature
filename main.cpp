#include <stdio.h>
#include "organism.hpp"
#include "consts.hpp"
#include "game.hpp"

int main() {
	Game game(20, 20);

	srand(time(NULL));
	
	int code[nTraits] = {1, 1, 1};

	game.organisms.push_back(new Organism(code));
	
	return 0;
}
