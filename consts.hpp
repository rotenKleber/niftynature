#ifndef CONSTS_H_
#define CONSTS_H_

#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <math.h>

using namespace std;

// 0 body size (1-10)
// 1 leg size (0-10) (determines speed)
// 2 stomach type (0-2) 0 for herbivore, 1 for omnivore, 2 for carnivore (can also be used to determine tooth type)

int irandom(const int &a, const int &b);

enum codeID {bodySize, legSize, stomachType};
enum food {cellulose = 0, plant = 1, meat = 2};

const unsigned int nTraits = 3;

// Map stuff

enum terrain {none, dirt, stone, grass};

#define MAP_W 20
#define MAP_H 20
#define TILE_W 64
#define TILE_H 64
#define SCREEN_W 1024
#define SCREEN_H 768

#endif
