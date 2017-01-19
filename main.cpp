#include <stdio.h>
#include "organism.hpp"
#include "consts.hpp"
#include <vector>

int main() {

	srand(time(NULL));

	vector<Organism*> organisms;

	organisms.push_back();

	Organism org3 = Organism::repopulate(org, org2);

	for(int i = 0; i < nTraits; i++) {
		printf("%i", org.getCode()[i]);
	}
	printf("\n");

	for(int i = 0; i < nTraits; i++) {
		printf("%i", org2.getCode()[i]);
	}
	printf("\n");

	for(int i = 0; i < nTraits; i++) {
		printf("%i", org3.getCode()[i]);
	}
	printf("\n");

	for(int i = 0; i < organisms.size(); i++) {
		delete organisms[i];
	}

	return 0;
}
