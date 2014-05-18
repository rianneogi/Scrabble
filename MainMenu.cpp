#include "MainMenu.h"

void RenderMenu(int MouseX, int MouseY)
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
		gdi->OrangeBrush(); //yellow if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(MenuItemXOffset,NewGameYOffset,MenuItemXOffset+MenuItemWidth,NewGameYOffset+MenuItemHeight);
	gdi->TextAtPos(MenuItemXOffset+TextXOffset,NewGameYOffset+TextYOffset,"NEW GAME");
	
	// load game
	if((MouseX < MenuItemXOffset || MouseX > MenuItemXOffset+MenuItemWidth) || (MouseY < LoadGameYOffset || MouseY > LoadGameYOffset+MenuItemHeight))
		gdi->OrangeBrush(); //yellow if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(MenuItemXOffset,LoadGameYOffset,MenuItemXOffset+MenuItemWidth,LoadGameYOffset+MenuItemHeight);
	gdi->TextAtPos(MenuItemXOffset+TextXOffset,LoadGameYOffset+TextYOffset,"LOAD GAME");

	// exit
	if((MouseX < MenuItemXOffset || MouseX > MenuItemXOffset+MenuItemWidth) || (MouseY < ExitYOffset || MouseY > ExitYOffset+MenuItemHeight))
		gdi->OrangeBrush(); //yellow if mouse does not hover on menu item
	else
		gdi->YellowBrush(); //yellow if mouse hovers on menu item
	gdi->Rect(MenuItemXOffset,ExitYOffset,MenuItemXOffset+MenuItemWidth,ExitYOffset+MenuItemHeight);
	gdi->TextAtPos(MenuItemXOffset+TextXOffset,ExitYOffset+TextYOffset,"EXIT");
}
