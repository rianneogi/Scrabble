#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Hashing.h"
#include <string>

enum TileType {TILE_NORMAL,TILE_DOUBLEWORD,TILE_TRIPLEWORD,TILE_DOUBLELETTER,TILE_TRIPLELETTER};
typedef struct {
    char letter;      //current letter at board position
    TileType type;    //type of the tile eg: doubleword, tripleword
	bool scored;      //bool to check if the score of this letter has been taken care of
} Tile;

extern Tile tempstr[15][15];
extern Tile Board[15][15];
extern int LetterScore[26];
extern int LetterPile[26];
extern int countmoves;
extern int tilesplaced;
extern std::string text; //display text

extern char Hand[2][7]; //contains the letters on the hand of each player
extern int Pass[2];    //has the player used his pass?
extern int Shuffle[2]; //has the player used his shuffle?
extern int Score[2];

extern int turn; //whos turn is it?

extern char selection; //selected letter

void InitializeBoard();
int getScore();
int traverseWord(int c, int r, char dir);
int scoreWord(Tile* word);
int takeFromPile();

#endif