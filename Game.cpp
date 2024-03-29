#include "Game.h"

enum State {STATE_MENU,STATE_BOARD,STATE_LOAD,STATE_MULTIPLAYER};

sf::TcpSocket Socket;

int MouseX = 0;
int MouseY = 0;
int Mouse2X = 0;
int Mouse2Y = 0;
int cxClient = 0;
int cyClient = 0;
int GameState = STATE_MENU;

int isMultiplayer =  false;
int amIHost =  false;
int myPlayer = 0;

COLORREF TripleWordColor = RGB(230,0,32);
COLORREF DoubleWordColor = RGB(244,165,130);
COLORREF NormalTileColor = RGB(247,247,247);
COLORREF DoubleLetterColor = RGB(146,197,222);
COLORREF TripleLetterColor = RGB(5,113,176);
COLORREF LetterColor = RGB(253,184,97);


void InitializeGame(int cx,int cy)
{
	cxClient = cx;
	cyClient = cy;
	MouseX = 0;
	MouseY = 0;
	GameState = STATE_MENU;
	isMultiplayer = true;
	amIHost =  true;
	myPlayer = 0;

	if(!amIHost)
	{
		sf::Socket::Status status = Socket.connect("169.254.70.58", 53000);
		if (status != sf::Socket::Done)
		{
			 
		}
	}
	else
	{
		sf::TcpListener listener;

		// bind the listener to a port
		if (listener.listen(53000) != sf::Socket::Done)
		{
			// error...
		}

		// accept a new connection
		//sf::TcpSocket client;
		if (listener.accept(Socket) != sf::Socket::Done)
		{
			// error...
		}
	}
	Socket.setBlocking(false);
	InitializeBoard();
}

void CleanUp()
{
	//nothing here
}

//key presses
void HandleKeyPresses(WPARAM wParam)
{
}

//update
void Update(double timeelasped)
{
	
}

//This renders the entire game
void Render()
{
	if(GameState==STATE_MENU)
	{
		RenderMenu();
		return;
	}
	else if(GameState==STATE_MULTIPLAYER)
	{
		RenderMultiplayer();
		return;
	}

	gdi->ThickBlackPen();
	gdi->TransparentText();

	//draw the title
	gdi->OrangeBrush();
	gdi->Rect(TitleXOffset,TitleYOffset,TitleXOffset+LetterSize,TitleYOffset+LetterSize);
	gdi->RedBrush();
	gdi->Rect(TitleXOffset+LetterSize,TitleYOffset,TitleXOffset+LetterSize*2,TitleYOffset+LetterSize);
	gdi->GreenBrush();
	gdi->Rect(TitleXOffset+LetterSize*2,TitleYOffset,TitleXOffset+LetterSize*3,TitleYOffset+LetterSize);
	gdi->OrangeBrush();
	gdi->Rect(TitleXOffset+LetterSize*3,TitleYOffset,TitleXOffset+LetterSize*4,TitleYOffset+LetterSize);
	gdi->YellowBrush();
	gdi->Rect(TitleXOffset+LetterSize*4,TitleYOffset,TitleXOffset+LetterSize*5,TitleYOffset+LetterSize);
	gdi->OrangeBrush();
	gdi->Rect(TitleXOffset+LetterSize*5,TitleYOffset,TitleXOffset+LetterSize*6,TitleYOffset+LetterSize);
	gdi->RedBrush();
	gdi->Rect(TitleXOffset+LetterSize*6,TitleYOffset,TitleXOffset+LetterSize*7,TitleYOffset+LetterSize);
	gdi->GreenBrush();
	gdi->Rect(TitleXOffset+LetterSize*7,TitleYOffset,TitleXOffset+LetterSize*8,TitleYOffset+LetterSize);

	//draw the text "SCRABBLE" on top
	gdi->ThickBlackPen();
	gdi->TextAtPos(TextXOffset+TitleXOffset,TextYOffset+TitleYOffset,"S");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize,TextYOffset+TitleYOffset,"C");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*2,TextYOffset+TitleYOffset,"R");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*3,TextYOffset+TitleYOffset,"A");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*4,TextYOffset+TitleYOffset,"B");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*5,TextYOffset+TitleYOffset,"B");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*6,TextYOffset+TitleYOffset,"L");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*7,TextYOffset+TitleYOffset,"E");

	//draw the board
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			if(Board[i][j].type==TILE_NORMAL) //draw normal tiles
			{
				gdi->SetBrush(NormalTileColor);
				gdi->Rect(TileXOffset+TileSize*j,TileYOffset+TileSize*i,TileXOffset+TileSize*(j+1),TileYOffset+TileSize*(i+1));
			}
			else if(Board[i][j].type==TILE_TRIPLEWORD) //draw triple word tiles
			{
				gdi->SetBrush(TripleWordColor);
				gdi->Rect(TileXOffset+TileSize*j,TileYOffset+TileSize*i,TileXOffset+TileSize*(j+1),TileYOffset+TileSize*(i+1));
				gdi->ThickBlackPen();
				gdi->TextAtPos(TileXOffset+TextXOffset+TileSize*j,TileYOffset+TextYOffset+TileSize*i,"TW");
			}
			else if(Board[i][j].type==TILE_DOUBLEWORD) //draw double word tiles
			{
				gdi->SetBrush(DoubleWordColor);
				gdi->Rect(TileXOffset+TileSize*j,TileYOffset+TileSize*i,TileXOffset+TileSize*(j+1),TileYOffset+TileSize*(i+1));
				gdi->ThickBlackPen();
				gdi->TextAtPos(TileXOffset+TextXOffset+TileSize*j,TileYOffset+TextYOffset+TileSize*i,"DW");
			}
			else if(Board[i][j].type==TILE_TRIPLELETTER) //draw triple letter tiles
			{
				gdi->SetBrush(TripleLetterColor);
				gdi->Rect(TileXOffset+TileSize*j,TileYOffset+TileSize*i,TileXOffset+TileSize*(j+1),TileYOffset+TileSize*(i+1));
				gdi->ThickBlackPen();
				gdi->TextAtPos(TileXOffset+TextXOffset+TileSize*j,TileYOffset+TextYOffset+TileSize*i,"TL");
			}
			else if(Board[i][j].type==TILE_DOUBLELETTER) //draw double letter tiles
			{
				gdi->SetBrush(DoubleLetterColor);
				gdi->Rect(TileXOffset+TileSize*j,TileYOffset+TileSize*i,TileXOffset+TileSize*(j+1),TileYOffset+TileSize*(i+1));
				gdi->ThickBlackPen();
				gdi->TextAtPos(TileXOffset+TextXOffset+TileSize*j,TileYOffset+TextYOffset+TileSize*i,"DL");
			}
		}
	}

	//draw the notation on the side of the board
	/*gdi->BlackPen();
	for(int i = 0;i<15;i++)
	{
		std::string s;
		s += char(i+97);
		gdi->TextAtPos(TileXOffset-NotationOffset,TileYOffset+TileSize*(i+1)-NotationOffset,s);
		char s2[3];
		itoa(i+1,s2,10);
		s=s2;
		gdi->TextAtPos(TileXOffset+TileSize*(i+1)-NotationOffset,TileYOffset+TileSize*15,s);
	}*/

	//draw all the letters on the board
	gdi->ThickBlackPen();
	for(int i = 0;i<15;i++)
	{
		for(int j = 0;j<15;j++)
		{
			if(Board[i][j].letter!=' ')
			{
				drawLetter(TileXOffset+LetterXOffset+TileSize*j,TileYOffset+LetterYOffset+TileSize*i,Board[i][j].letter);
			}
			//gdi->BlackPen();
			//gdi->TextAtPos(TileXOffset+TileSize*j,TileYOffset+TileSize*i,std::to_string(Board[i][j].scored));
		}
	}

	//draw the hand
	for(int i = 0;i<7;i++)
	{
		gdi->GreyBrush(); //hand border
		gdi->Rect(HandXOffset+(LetterSize+HandSeperation)*i,HandYOffset,HandXOffset+(LetterSize+HandSeperation)*i+LetterSize,HandYOffset+LetterSize);

		if(isMultiplayer)
		{
			if(Hand[myPlayer][i]!=' ') 
			{
				drawLetter(HandXOffset+(LetterSize+HandSeperation)*i,HandYOffset,Hand[myPlayer][i]); //hand letter
			}
		}
		else
		{
			if(Hand[turn][i]!=' ') 
			{
				drawLetter(HandXOffset+(LetterSize+HandSeperation)*i,HandYOffset,Hand[turn][i]); //hand letter
			}
		}
	}

	//draw the buttons
	// submit
	if((MouseX < ButtonXOffset || MouseX > ButtonXOffset+MenuItemWidth) || (MouseY < SubmitYOffset || MouseY > SubmitYOffset+MenuItemHeight))
		gdi->OrangeBrush(); //orange if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(ButtonXOffset,SubmitYOffset,ButtonXOffset+MenuItemWidth,SubmitYOffset+MenuItemHeight);
	gdi->TextAtPos(ButtonXOffset+TextXOffset,SubmitYOffset+TextYOffset,"SUBMIT");

	// pass
	if(Pass[turn]==0)
		gdi->GreyBrush();
	else if((MouseX < ButtonXOffset || MouseX > ButtonXOffset+MenuItemWidth) || (MouseY < PassYOffset || MouseY > PassYOffset+MenuItemHeight))
		gdi->OrangeBrush(); //orange if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(ButtonXOffset,PassYOffset,ButtonXOffset+MenuItemWidth,PassYOffset+MenuItemHeight);
	gdi->TextAtPos(ButtonXOffset+TextXOffset,PassYOffset+TextYOffset,"PASS TURN");

	// shuffle
	if(Shuffle[turn]==0)
		gdi->GreyBrush();
	else if((MouseX < ButtonXOffset || MouseX > ButtonXOffset+MenuItemWidth) || (MouseY < ShuffleYOffset || MouseY > ShuffleYOffset+MenuItemHeight))
		gdi->OrangeBrush(); //orange if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(ButtonXOffset,ShuffleYOffset,ButtonXOffset+MenuItemWidth,ShuffleYOffset+MenuItemHeight);
	gdi->TextAtPos(ButtonXOffset+TextXOffset,ShuffleYOffset+TextYOffset,"SHUFFLE HAND");

	// save game
	if((MouseX < ButtonXOffset || MouseX > ButtonXOffset+MenuItemWidth) || (MouseY < SaveGameYOffset || MouseY > SaveGameYOffset+MenuItemHeight))
		gdi->GreyBrush(); //orange if mouse does not hover on menu item
	else
		gdi->GreyBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(ButtonXOffset,SaveGameYOffset,ButtonXOffset+MenuItemWidth,SaveGameYOffset+MenuItemHeight);
	gdi->TextAtPos(ButtonXOffset+TextXOffset,SaveGameYOffset+TextYOffset,"SAVE GAME");

	// return to menu
	if((MouseX < ButtonXOffset || MouseX > ButtonXOffset+MenuItemWidth) || (MouseY < ReturnYOffset || MouseY > ReturnYOffset+MenuItemHeight))
		gdi->OrangeBrush(); //orange if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(ButtonXOffset,ReturnYOffset,ButtonXOffset+MenuItemWidth,ReturnYOffset+MenuItemHeight);
	gdi->TextAtPos(ButtonXOffset+TextXOffset,ReturnYOffset+TextYOffset,"MAIN MENU");

	std::string s;
	s += "Player 1 Score: ";
	s += std::to_string(Score[0]);
	gdi->TextAtPos(750,100,s); //player 1 score
	s = "Player 2 Score: ";
	s += std::to_string(Score[1]);
	gdi->TextAtPos(750,125,s); //player 2 score
	if(turn==0)
		s = "Player 1";
	else 
		s = "Player 2";
	gdi->TextAtPos(750,150,text); //display the display text
	gdi->TextAtPos(220,HandYOffset+TextYOffset,s); //whos turn is it?

	//draw the selected letter
	if(selection!=' ')
	{
		drawLetter(MouseX,MouseY,selection);
	}
	if(isMultiplayer && selection2!=' ')
	{
		drawGreyLetter(MouseX,MouseY);
	}
}

void RenderMenu()
{
	gdi->ThickBlackPen();
	gdi->TransparentText();

	//draw the title
	gdi->OrangeBrush();
	gdi->Rect(TitleXOffset,TitleYOffset,TitleXOffset+LetterSize,TitleYOffset+LetterSize);
	gdi->RedBrush();
	gdi->Rect(TitleXOffset+LetterSize,TitleYOffset,TitleXOffset+LetterSize*2,TitleYOffset+LetterSize);
	gdi->GreenBrush();
	gdi->Rect(TitleXOffset+LetterSize*2,TitleYOffset,TitleXOffset+LetterSize*3,TitleYOffset+LetterSize);
	gdi->OrangeBrush();
	gdi->Rect(TitleXOffset+LetterSize*3,TitleYOffset,TitleXOffset+LetterSize*4,TitleYOffset+LetterSize);
	gdi->YellowBrush();
	gdi->Rect(TitleXOffset+LetterSize*4,TitleYOffset,TitleXOffset+LetterSize*5,TitleYOffset+LetterSize);
	gdi->OrangeBrush();
	gdi->Rect(TitleXOffset+LetterSize*5,TitleYOffset,TitleXOffset+LetterSize*6,TitleYOffset+LetterSize);
	gdi->RedBrush();
	gdi->Rect(TitleXOffset+LetterSize*6,TitleYOffset,TitleXOffset+LetterSize*7,TitleYOffset+LetterSize);
	gdi->GreenBrush();
	gdi->Rect(TitleXOffset+LetterSize*7,TitleYOffset,TitleXOffset+LetterSize*8,TitleYOffset+LetterSize);

	//draw the text "SCRABBLE" on top
	gdi->ThickBlackPen();
	gdi->TextAtPos(TextXOffset+TitleXOffset,TextYOffset+TitleYOffset,"S");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize,TextYOffset+TitleYOffset,"C");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*2,TextYOffset+TitleYOffset,"R");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*3,TextYOffset+TitleYOffset,"A");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*4,TextYOffset+TitleYOffset,"B");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*5,TextYOffset+TitleYOffset,"B");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*6,TextYOffset+TitleYOffset,"L");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*7,TextYOffset+TitleYOffset,"E");

	//render the menu items
	// new game
	if((MouseX < MenuItemXOffset || MouseX > MenuItemXOffset+MenuItemWidth) || (MouseY < NewGameYOffset || MouseY > NewGameYOffset+MenuItemHeight))
		gdi->OrangeBrush(); //orange if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(MenuItemXOffset,NewGameYOffset,MenuItemXOffset+MenuItemWidth,NewGameYOffset+MenuItemHeight);
	gdi->TextAtPos(MenuItemXOffset+TextXOffset,NewGameYOffset+TextYOffset,"NEW GAME");

	// continue game
	if((MouseX < MenuItemXOffset || MouseX > MenuItemXOffset+MenuItemWidth) || (MouseY < ContinueGameYOffset || MouseY > ContinueGameYOffset+MenuItemHeight))
		gdi->OrangeBrush(); //orange if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(MenuItemXOffset,ContinueGameYOffset,MenuItemXOffset+MenuItemWidth,ContinueGameYOffset+MenuItemHeight);
	gdi->TextAtPos(MenuItemXOffset+TextXOffset,ContinueGameYOffset+TextYOffset,"CONTINUE GAME");

	// continue game
	if((MouseX < MenuItemXOffset || MouseX > MenuItemXOffset+MenuItemWidth) || (MouseY < MultiplayerYOffset || MouseY > MultiplayerYOffset+MenuItemHeight))
		gdi->OrangeBrush(); //orange if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(MenuItemXOffset,MultiplayerYOffset,MenuItemXOffset+MenuItemWidth,MultiplayerYOffset+MenuItemHeight);
	gdi->TextAtPos(MenuItemXOffset+TextXOffset,MultiplayerYOffset+TextYOffset,"CONTINUE GAME");
	
	// load game
	if((MouseX < MenuItemXOffset || MouseX > MenuItemXOffset+MenuItemWidth) || (MouseY < LoadGameYOffset || MouseY > LoadGameYOffset+MenuItemHeight))
		gdi->GreyBrush(); //orange if mouse does not hover on menu item
	else
		gdi->GreyBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(MenuItemXOffset,LoadGameYOffset,MenuItemXOffset+MenuItemWidth,LoadGameYOffset+MenuItemHeight);
	gdi->TextAtPos(MenuItemXOffset+TextXOffset,LoadGameYOffset+TextYOffset,"LOAD GAME");

	// exit
	if((MouseX < MenuItemXOffset || MouseX > MenuItemXOffset+MenuItemWidth) || (MouseY < ExitYOffset || MouseY > ExitYOffset+MenuItemHeight))
		gdi->OrangeBrush(); //orange if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(MenuItemXOffset,ExitYOffset,MenuItemXOffset+MenuItemWidth,ExitYOffset+MenuItemHeight);
	gdi->TextAtPos(MenuItemXOffset+TextXOffset,ExitYOffset+TextYOffset,"EXIT");
}

void RenderMultiplayer()
{
	gdi->ThickBlackPen();
	gdi->TransparentText();

	//draw the title
	gdi->OrangeBrush();
	gdi->Rect(TitleXOffset,TitleYOffset,TitleXOffset+LetterSize,TitleYOffset+LetterSize);
	gdi->RedBrush();
	gdi->Rect(TitleXOffset+LetterSize,TitleYOffset,TitleXOffset+LetterSize*2,TitleYOffset+LetterSize);
	gdi->GreenBrush();
	gdi->Rect(TitleXOffset+LetterSize*2,TitleYOffset,TitleXOffset+LetterSize*3,TitleYOffset+LetterSize);
	gdi->OrangeBrush();
	gdi->Rect(TitleXOffset+LetterSize*3,TitleYOffset,TitleXOffset+LetterSize*4,TitleYOffset+LetterSize);
	gdi->YellowBrush();
	gdi->Rect(TitleXOffset+LetterSize*4,TitleYOffset,TitleXOffset+LetterSize*5,TitleYOffset+LetterSize);
	gdi->OrangeBrush();
	gdi->Rect(TitleXOffset+LetterSize*5,TitleYOffset,TitleXOffset+LetterSize*6,TitleYOffset+LetterSize);
	gdi->RedBrush();
	gdi->Rect(TitleXOffset+LetterSize*6,TitleYOffset,TitleXOffset+LetterSize*7,TitleYOffset+LetterSize);
	gdi->GreenBrush();
	gdi->Rect(TitleXOffset+LetterSize*7,TitleYOffset,TitleXOffset+LetterSize*8,TitleYOffset+LetterSize);

	//draw the text "SCRABBLE" on top
	gdi->ThickBlackPen();
	gdi->TextAtPos(TextXOffset+TitleXOffset,TextYOffset+TitleYOffset,"S");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize,TextYOffset+TitleYOffset,"C");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*2,TextYOffset+TitleYOffset,"R");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*3,TextYOffset+TitleYOffset,"A");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*4,TextYOffset+TitleYOffset,"B");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*5,TextYOffset+TitleYOffset,"B");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*6,TextYOffset+TitleYOffset,"L");
	gdi->TextAtPos(TextXOffset+TitleXOffset+LetterSize*7,TextYOffset+TitleYOffset,"E");
}

//draws a scrabble letter at position x,y of character 'c'
void drawLetter(int x,int y,char c)
{
	gdi->ThickBlackPen();
	gdi->SetBrush(LetterColor);
	gdi->Rect(x,y,x+LetterSize,y+LetterSize);
	std::string s;
	s += c;
	gdi->TextAtPos(x+TextXOffset,y+TextYOffset,s);
	s = std::to_string(LetterScore[c-65]);
	gdi->TextAtPos(x+LetterScoreXOffset,y+LetterScoreYOffset,s);
}

void drawGreyLetter(int x,int y)
{
	gdi->ThickBlackPen();
	gdi->GreyBrush();
	gdi->Rect(x,y,x+LetterSize,y+LetterSize);
}

//adds a word to the board
void addWord(int x,int y,int dir,std::string word)
{
	for(int i = 0;i<word.length();i++)
	{
		if(dir==0)
		{
			if(x+i > 14) break; 
			Board[x+i][y].letter = word.at(i);
		}
		else if(dir==1)
		{
			if(y+i > 14) break; 
			Board[x][y+i].letter = word.at(i);
		}
	}
}

//gets the X-coordinate of the tile the mouse is positioned over, returns -1 if mouse isn't over any tile
int getSquareX(POINTS p)
{
	int endofboard = TileXOffset + 15*TileSize;
	if(p.x < TileXOffset || p.x > endofboard)
		return -1;
	return (p.x-TileXOffset)/TileSize;
}

//gets the Y-coordinate of the tile the mouse is positioned over, returns -1 if mouse isn't over any tile
int getSquareY(POINTS p)
{
	int endofboard = TileYOffset + 15*TileSize;
	if(p.y < TileYOffset || p.y > endofboard)
		return -1;
	return (p.y-TileYOffset)/TileSize;
}

//gets the position of the letter in the hand if the mouse is positioned over the hand, returns -1 if not
int getHandPosition(POINTS p)
{
	if(p.y < HandYOffset || p.y > HandYOffset + LetterSize || p.x<HandXOffset || p.x>HandXOffset+7*LetterSize+6*HandSeperation)
		return -1;
	return (p.x-HandXOffset)/(LetterSize+HandSeperation);
}

void SubmitButton()
{
	int turnscore = getScore();
		if(turnscore>=0)
		{
			//submit code here
			for(int i = 0;i<7;i++)
			{
				if(Hand[turn][i]==' ')
					Hand[turn][i] = 65+takeFromPile();
			}
			Score[turn] += turnscore;
			if(turn==0) turn=1;
			else turn=0;
			countmoves++;
			text = "";
			if(tilesplaced>=7)
			{
				Score[turn]+=50;
			}
			tilesplaced=0;
			for(int i = 0;i<15;i++)
			{
				for(int j = 0;j<15;j++)
				{
					if(Board[i][j].letter!=' ') 
						Board[i][j].scored = true; //score all words
				}
			}
		}
		else if(turnscore==-1)
		{
			text = "Invalid placement of letters!";
		}
		else if(turnscore==-2)
		{
			text = "That word doesn't exist!";
		}
		else if(turnscore==-3)
		{
			text = "Did you even add a word?";
		}
		else if(turnscore==-4)
		{
			text = "Start from the centre square!";
		}
}

void ShuffleButton()
{
	if(Shuffle[turn]>0)
	{
		Shuffle[turn]--;
		for(int i = 0;i<7;i++)
		{
			if(Hand[turn][i]!=' ')
				Hand[turn][i] = 65+takeFromPile();
		}
	}
}

void PassTurnButton()
{
	if(Pass[turn]>0)
	{
		Pass[turn]--;
		if(turn==0) turn=1;
		else turn=0;
	}
}

void PlaceTile(int x,int y,char c,bool isMyPlayer)
{
	//swap selection and letter in hand
	if(c!=' ' && Board[y][x].letter==' ') //update tilesplaced
		tilesplaced++;
	else if(c==' ' && Board[y][x].letter!=' ')
		tilesplaced--;
	if(isMyPlayer)
	{
		selection = Board[y][x].letter;
	}
	Board[y][x].letter = c;
}

//actions that happen when the user leftcicks
void LeftMouseClickEvent(POINTS p)
{
	if(GameState==STATE_MENU)
	{
		if((MouseX >= MenuItemXOffset && MouseX <= MenuItemXOffset+MenuItemWidth) && 
			(MouseY >= NewGameYOffset && MouseY <= NewGameYOffset+MenuItemHeight))
		{
			InitializeBoard();
			GameState = STATE_BOARD; //user clicks New Game
		}
		else if((MouseX >= MenuItemXOffset && MouseX <= MenuItemXOffset+MenuItemWidth) && 
			(MouseY >= ContinueGameYOffset && MouseY <= ContinueGameYOffset+MenuItemHeight))
		{
			GameState = STATE_BOARD; //user clicks Continue Game
		}
		else if((MouseX >= MenuItemXOffset && MouseX <= MenuItemXOffset+MenuItemWidth) && 
			(MouseY >= MultiplayerYOffset && MouseY <= MultiplayerYOffset+MenuItemHeight))
		{
			GameState = STATE_MULTIPLAYER; //user clicks Continue Game
		}
		else if((MouseX >= MenuItemXOffset && MouseX <= MenuItemXOffset+MenuItemWidth) && 
			(MouseY >= ExitYOffset && MouseY <= ExitYOffset+MenuItemHeight))
		{
			//exit the game, will this cause leaks?
			CleanUp();
			exit(0);
		}
		return;
	}

	int handpos = getHandPosition(p);
	if(handpos!=-1) //is mouse positioned over hand?
	{
		//swap selection and letter in hand
		char tmp = selection;
		selection = Hand[turn][handpos];
		Hand[turn][handpos] = tmp;
		return;
	}
	int x = getSquareX(p);
	int y = getSquareY(p);
	if(x!=-1 && y!=-1) //is mouse over the board?
	{
		if(Board[y][x].scored==0 || Board[y][x].letter==' ')
		{
			if(isMultiplayer)
			{
				sf::Packet packet;
				sf::Int32 t=MESSAGE_PLACETILE;
				sf::Int32 x2 = x;
				sf::Int32 y2 = y;
				sf::Int32 c = selection;
				packet << t << x2 << y2 << c;
				Socket.send(packet);
				text = std::to_string(x2) + " " + std::to_string(y2) + " " + std::to_string(c) + "x";
				packet >> t;
				packet >> x2;
				packet >> y2;
				packet >> c;
				text += std::to_string(x2) + " " + std::to_string(y2) + " " + std::to_string(c);
			}
			PlaceTile(x,y,selection,true);
			
			return;
		}
	}

	if((MouseX >= ButtonXOffset && MouseX <= ButtonXOffset+MenuItemWidth) && 
			(MouseY >= SubmitYOffset && MouseY <= SubmitYOffset+MenuItemHeight))
	{
		SubmitButton();
		if(isMultiplayer)
		{
			sf::Packet packet;
			sf::Int32 t=MESSAGE_SUBMIT;
			packet << t;
			Socket.send(packet);
		}
	}

	if((MouseX >= ButtonXOffset && MouseX <= ButtonXOffset+MenuItemWidth) && 
			(MouseY >= PassYOffset && MouseY <= PassYOffset+MenuItemHeight))
	{
		PassTurnButton();
		if(isMultiplayer)
		{
			sf::Packet packet;
			sf::Int32 t=MESSAGE_PASSTURN;
			packet << t;
			Socket.send(packet);
		}
	}

	if((MouseX >= ButtonXOffset && MouseX <= ButtonXOffset+MenuItemWidth) && 
			(MouseY >= ShuffleYOffset && MouseY <= ShuffleYOffset+MenuItemHeight))
	{
		ShuffleButton();
		if(isMultiplayer)
		{
			sf::Packet packet;
			sf::Int32 t=MESSAGE_SHUFFLE;
			packet << t;
			Socket.send(packet);
		}
	}

	if((MouseX >= ButtonXOffset && MouseX <= ButtonXOffset+MenuItemWidth) && 
			(MouseY >= SaveGameYOffset && MouseY <= SaveGameYOffset+MenuItemHeight))
	{
		//save game code here
	}

	if((MouseX >= ButtonXOffset && MouseX <= ButtonXOffset+MenuItemWidth) && 
			(MouseY >= ReturnYOffset && MouseY <= ReturnYOffset+MenuItemHeight))
	{
		GameState = STATE_MENU; //return to main menu
	}
}

//actions that happen when the user rightcicks
void RightMouseClickEvent(POINTS p)
{
	
}

//This updates the mouse positions, to be called whenever mouse movement is detected
void ChangeMousePosition(POINTS p)
{
	MouseX = p.x;
	MouseY = p.y;

	/*if(isMultiplayer)
	{
		sf::Packet packet;
		sf::Uint32 type = MESSAGE_MOUSEMOVE;
		sf::Uint32 n = MouseX;
		sf::Uint32 n2 = MouseY;
		packet << 1 << n << n2;
		Socket.send(
	}*/
}

void receivePacket(sf::Packet& p)
{
	sf::Int32 type;
	p >> type;
	if(type==MESSAGE_PLACETILE)
	{
		sf::Int32 x,y,c;
		p >> x;
		p >> y;
		p >> c;
		text = std::to_string(x) + " " + std::to_string(y) + " "+std::to_string(c) + " ";
		PlaceTile(x,y,char(c),false);
	}
	if(type==MESSAGE_SUBMIT)
	{
		SubmitButton();
	}
	if(type==MESSAGE_PASSTURN)
	{
		PassTurnButton();
	}
	if(type==MESSAGE_SHUFFLE)
	{
		ShuffleButton();
	}
}