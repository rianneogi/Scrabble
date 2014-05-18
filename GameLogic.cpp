#include "GameLogic.h"
#include "Hashing.c"

// board geometry 15x15
Tile Board[15][15];

// letter values are   A B C D E  F G H I J K L M N O P Q  R S T U V W X Y Z
int LetterScore[26] = {1,3,3,2,1 ,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

int LetterPile[26]  = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1 ,6,4,6,4,2,2,1,2,1};

Tile tempstr[15][15];

int countmoves = 0;
int tilesplaced = 0;

Tile tempstring[15];
int counter = 0;

int turn = 0;
char Hand[2][7];
int Pass[2];
int Shuffle[2];
int Score[2];

char selection = ' ';
std::string text = "";

//initializes the board
void InitializeBoard()
{
    int i, j;
	text = "";
    for (i=0; i<15; i++)
	{
        for (j=0; j<15; j++)
        {
            Board[i][j].type = TILE_NORMAL;
            Board[i][j].letter = ' ';
			Board[i][j].scored = false;
            if ((i==0 || i==7 || i==14) && (j==0 || j==7 || j==14))     //Triple Word initialization, except for the center tile.
                Board[i][j].type = (i==7 && j==7) ? TILE_DOUBLEWORD : TILE_TRIPLEWORD;
            else if ((i==5 || i==9) && ((j-1)%4==0))                    //
                Board[i][j].type = TILE_DOUBLELETTER;
            else if ((j==5 || j==9) && ((i-1)%4==0))
                Board[i][j].type = TILE_TRIPLELETTER;
            else if ((i==6 || i==8) && (j==2 || j==6 || j==8 || j==12))
                Board[i][j].type = TILE_DOUBLELETTER;
            else if ((j==6 || j==8) && (i==2 || i==6 || i==8 || i==12))
                Board[i][j].type = TILE_DOUBLELETTER;
            else if ((i==3 || i==11) && (j==0 || j==7 || j==14))
                Board[i][j].type = TILE_DOUBLELETTER;
            else if ((j==3 || j==11) && (i==0 || i==7 || i==14))
                Board[i][j].type = TILE_DOUBLELETTER;
            else if (i==j || i==(14-j))
                Board[i][j].type = TILE_DOUBLEWORD;
        }
	}
	//Board[7][7].scored = true;

	LetterPile[0] = 9;
	LetterPile[1] = 2;
	LetterPile[2] = 2;
	LetterPile[3] = 4;
	LetterPile[4] = 12;
	LetterPile[5] = 2;
	LetterPile[6] = 3;
	LetterPile[7] = 2;
	LetterPile[8] = 9;
	LetterPile[9] = 1;
	LetterPile[10] = 1;
	LetterPile[11] = 4;
	LetterPile[12] = 2;
	LetterPile[13] = 6;
	LetterPile[14] = 8;
	LetterPile[15] = 2;
	LetterPile[16] = 1;
	LetterPile[17] = 6;
	LetterPile[18] = 4;
	LetterPile[19] = 6;
	LetterPile[20] = 4;
	LetterPile[21] = 2;
	LetterPile[22] = 2;
	LetterPile[23] = 1;
	LetterPile[24] = 2;
	LetterPile[25] = 1;

	countmoves = 0;
	tilesplaced = 0;

	turn = 0;
	selection = ' ';
	Shuffle[0] = 1;
	Shuffle[1] = 1;
	Pass[0] = 1;
	Pass[1] = 1;
	Score[0] = 0;
	Score[1] = 0;

	//randomize the hands
	for(int i = 0;i<7;i++)
	{
		for(int j = 0;j<2;j++)
		{
			Hand[j][i] = 65+takeFromPile();
		}
	}
}

int takeFromPile()
{
	int i,sum=0;
	for(i = 0;i<26;i++)
	{
		sum += LetterPile[i];
	}
	if(sum==0) return -1;
	int r = rand()%sum;
	int ptr = 0;
	for(int i = 0;i<26;i++)
	{
		ptr += LetterPile[i];
		if(ptr>r)
			return i;
	}
	return -2;
}

int getWordMul(TileType t)
{
	if(t==TILE_DOUBLEWORD) return 2;
	if(t==TILE_TRIPLEWORD) return 3;
	return 1;
}

int getLetterMul(TileType t)
{
	if(t==TILE_DOUBLELETTER) return 2;
	if(t==TILE_TRIPLELETTER) return 3;
	return 1;
}

/*This is the part of the code where all of the words are processed at once

The steps for processing all the words are as follows.

1) The word must be longer than 1 letter(Except at the start)
2) There should be atleast one 0 and one 1 in the given string. Two flag variables will indicate this.

At this point, if both conditions are satisfied, then the word is stored into a 2D array to compute.
This process is repeated vertically and horizontally

We then examine the 2D array.
3) At least one of the substrings with Zeroes has to be equal to the tiles placed.(Zeroes are measured here and equated to the tiles placed.) If true
4) Finally, all substrings are evaluated for validity.

If the given evaluation works, then and only then is the score added to the overall score and the board is updated.

Another possible approach was to use matrix subtraction, but that was a bit heavy on the memory than we wanted, and so we decided against it.
*/

Tile tileat(int x,int y)
{
	if(x>=0 && x<15 && y>=0 && y<15) return Board[x][y];
	Tile t;
	t.letter = ' ';
	t.scored = false;
	t.type = TILE_NORMAL;
	return t;
}

int getScore()
{
	for(int i = 0;i<15;i++) //initialize
	{
		for(int j = 0;j<15;j++)
		{
			tempstr[i][j].letter = ' ';
			tempstr[i][j].type = TILE_NORMAL;
			tempstr[i][j].scored = false;
		}
		tempstring[i].letter = ' ';
		tempstring[i].type = TILE_NORMAL;
		tempstring[i].scored = false;
	}
	counter = 0;

    int x,y,u,v,m,n,no,flag=0,flagx=0,temp=0,tempscore=0,noo=0;

	if(Board[7][7].letter==' ') 
		return -4; //starting square not occupied

    if(countmoves==0)  // Starting condition
	{
		for(x=0;x<15;x++)  
		{
			for(y=0;y<15;y++)
			{
				if(Board[x][y].letter!=' ')    //First letter encountered of the game.  .
				{
					if(y<14 && Board[x][y+1].letter!=' ')
					   y+=traverseWord(y,x,'S');
					else if(x<14 && Board[x+1][y].letter==' ')
						if(x>0 && Board[x-1][y].letter==' ')
							return -1; //single letter found
				}
			}
		}
		for(y=0;y<15;y++)
		{
			for(x=0;x<15;x++)
			{
				if(Board[x][y].letter!=' ')    //First letter encountered of the game.  .
				{
					if(x<14 && Board[x+1][y].letter!=' ')
					   x+=traverseWord(y,x,'S');
					else if(y<14 && Board[x][y+1].letter==' ')
						if(y>0 && Board[x][y-1].letter==' ')
							return -1; //single letter found
				}
			}
		}
	}
	else
	{
		for(x=0;x<15;x++)  // Processing all words Horizontally
		{
			for(y=0;y<14;y++)
			{          
				if(Board[x][y].letter!= ' ')
                {
					if(Board[x][y+1].letter!=' ')
					{
						temp=traverseWord(y,x,'H');
						if(temp!=-1)
							y+=temp;
                    }
					else if(x<14 && Board[x+1][y].letter==' ')
					{
						if(x>0 && Board[x-1][y].letter==' ')
							return -1; //single letter found
						else if(x==0)
							return -1;
					}
					else if(x==14)
					{
						if(Board[x-1][y].letter==' ')
							return -1;
					}
                }
			}
		}
    
		for(u=0;u<15;u++)  //Processing all words vertically
		{
			for(v=0;v<14;v++)
			{
				if(Board[v][u].letter!= ' ')
				{
					if(Board[v+1][u].letter!=' ')
					{
						temp=traverseWord(u,v,'V');
						if(temp!=-1)
							v+=temp;
					}
					else if(u<14 && Board[v][u+1].letter==' ')
					{
						if(y>0 && Board[v][u-1].letter==' ')
							return -1; //single letter found
						else if(y==0)
							return -1;
					}
					else if(u==14)
					{
						if(Board[v][u-1].letter==' ')
							return -1;
					}
				}
			}
		}
	}

	if(counter==0)
		return -3; //no words added

    for(m=0;m<counter;m++)  // Checking for the zeroes being equal to Tiles placed
    {
		noo=0;
        for(n=0;n<15;n++)
        {
			if(tempstr[m][n].letter==' ') break;
            if(tempstr[m][n].scored==false)
                noo++;
        }
		if(noo==tilesplaced)
        {
            flag=1;
            break;
        }
    }
    if(flag)    // Final evaluation of strings.
    {
		flagx=1;
		for(m=0;m<counter;m++)
		{
			int has1 = 0;
			int has0 = 0;
			for(n=0;n<15;n++)
			{
				tempstring[n]=tempstr[m][n];
				/*if(tempstr[m][n].scored==true)
					has1 = 1;
				if(tempstr[m][n].scored==false)
					has0 = 1;*/
				if(tempstr[m][n].letter==' ') break;
			}
			//tempstring[n+1].letter=' ';
			//if((has0 && has1) || countmoves==0)
			//{
				int wordscore = scoreWord(tempstring);
				if(wordscore==-1)
				{
					flagx=0;
					break;
				}
				else
				{
					tempscore += wordscore;
				}
			//}
        }
    }
	else 
		return -1; //invalid placement
    if(flagx)
	{
		if(tempscore!=0)
			return tempscore;
		return -2; //invalid word added
	}
    else
		return -2; //invalid word added
}

int traverseWord(int c, int r, char dir)  // Traversing word
{
    int p=r,q=c,n=0,n1=0,n2=0,flag1=0,flag2=0;
    if(dir=='S')   // Word is either entered horizontally or vertically
    {
        if(r<14 && Board[r+1][c].letter!=' ')
        {
            n1=0;
            while(Board[p][q].letter!=' ')
			{
				tempstr[counter][n1]=Board[p][q];
				n1++;
				n++;
				p++;
				if(p>=15) break;
			}
			counter++;
		}
		else if(c<14 && Board[r][c+1].letter!=' ')
		{
			n1=0;
			while(Board[p][q].letter!=' ')
			{
				tempstr[counter][n1]=Board[p][q];
				n1++;
				n++;
				q++;
				if(q>=15) break;
			}
			counter++;
		}
		else 
			return 0;
    }
    else if(dir=='H')   //Horizontal
    {
        n=0,n1=0;
		while(Board[p][q].letter!=' ')
		{
			if(Board[p][q].scored==false)
				flag1=1;
            if(Board[p][q].scored==true)
				flag2=1;
            q++;
            n++;
			if(q>=15) break;
        }
        if(flag1 && flag2)
        {
			while(Board[r][c].letter!=' ')
			{
				tempstr[counter][n1]=Board[r][c];
				n1++;
				c++;
				if(c>=15) break;
			}
			counter++;
		}
		else if(flag1 && !flag2)
		{
			int checkflag = 0;
			p=r,q=c;
			while(Board[p][q].letter!=' ')
			{
				if(p<14 && Board[p+1][q].scored==true)
				{
					checkflag = 1;
					break;
				}
				else if(p>0 && Board[p-1][q].scored==true)
				{
					checkflag = 1;
					break;
				}
				q++;
				if(q>=15) break;
			}
			if(checkflag==1)
			{
				while(Board[r][c].letter!=' ')
				{
					tempstr[counter][n2]=Board[r][c];
					n2++;
					c++;
					if(c>=15) break;
				}
				counter++;
			}
		}
    }
    else if(dir=='V')   //Vertical
    {
		n2 = 0;
        while(Board[p][q].letter!=' ')
        {
			if(Board[p][q].scored==false)
                flag1=1;
			if(Board[p][q].scored==true)
                flag2=1;
            p++;
            n++;
			if(p>=15) break;
        }
        if(flag1 && flag2)
        {
			while(Board[r][c].letter!=' ')
			{
				tempstr[counter][n2]=Board[r][c];
				n2++;
				r++;
				if(r>=15) break;
			}
			counter++;
		}
		else if(flag1 && !flag2)
		{
			int checkflag = 0;
			p=r,q=c;
			while(Board[p][q].letter!=' ')
			{
				if(q<14 && Board[p][q+1].scored==true)
				{
					checkflag = 1;
					break;
				}
				else if(q>0 && Board[p][q-1].scored==true)
				{
					checkflag = 1;
					break;
				}
				p++;
				if(p>=15) break;
			}
			if(checkflag==1)
			{
				while(Board[r][c].letter!=' ')
				{
					tempstr[counter][n2]=Board[r][c];
					n2++;
					r++;
					if(r>=15) break;
				}
				counter++;
			}
		}
    }
	else 
		return 0;
	if(n==0) return 0;
	return n-1;
}

int scoreWord(Tile word[15])
{
    char tempword[17];
    int tempscore, wordmult=1, index,i=0;
    tempscore = 0;
	for(i = 0;i<15;i++)
	{
		if(word[i].letter==' ') break;
		tempword[i]=word[i].letter;
	}

    tempword[i]=0;

	struct word wordstruct;
	for(i = 0;i<17;i++)
	{
		wordstruct.tempw[i] = tempword[i];
	}

    if(!searchhash(wordstruct))
    {
        return -1;
    }
    else
    {
		for(int i = 0;i<15;i++)
		{
			if(word[i].letter==' ') break;
			index = word[i].letter - 'A';  // find zero-based index for alpha tile score.
		
			      // new tiles get letter and/or word multiplier, if any
			if(word[i].scored==false)
			{
				tempscore += LetterScore[index] * getLetterMul(word[i].type);
				wordmult *= getWordMul(word[i].type);  //Saving the new multiplier into a temporary variable.
			}
			else 
				tempscore += LetterScore[index];
		}
    }    
	// calculate final word score
    return (tempscore * wordmult);
}