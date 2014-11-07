#pragma once

#include <windows.h>
#include <vector>

#include "utils.h"
#include "Cgdi.h"
#include "GameLogic.h"
#include "constants.h"

enum Player {PLAYER1,PLAYER2};

enum NetworkMessage {MESSAGE_MOUSEMOVE,MESSAGE_SELECT,MESSAGE_PASSTURN,MESSAGE_SHUFFLE,MESSAGE_SETHAND,MESSAGE_PLACETILE,MESSAGE_REMOVETILE,MESSAGE_SUBMIT};

//local copy of client window dimensions
extern int cxClient; //is this necessary?
extern int cyClient;

extern sf::TcpSocket Socket;

extern int MouseX, MouseY; //current position of the mouse
extern int Mouse2X, Mouse2Y;

extern int GameState; //contains game state, 0 = Main Menu, 1 = New Game, 2 = Load Game

extern int isMultiplayer;
extern int amIHost;
extern int myPlayer;

void InitializeGame(int cx,int cy);
void CleanUp();

void HandleKeyPresses(WPARAM wParam);
void Update(double timeelasped);
void Render();
void RenderMenu();
void RenderMultiplayer();
void RenderBoard();

void drawLetter(int x,int y,char c);
void drawGreyLetter(int x,int y);

void addWord(int x,int y,int dir,std::string word);
void LeftMouseClickEvent(POINTS p);
void RightMouseClickEvent(POINTS p);
void ChangeMousePosition(POINTS p);

void receivePacket(sf::Packet& p);


