#include <iostream>
#include <cstring>
#include <ctime>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

#define TEXT_REPLAY_SELECTION 1
#define TEXT_SHOW_INTRODUCTION 2
#define TEXT_GET_PLAYER_INDEX 3
#define TEXT_GET_PLAYER_MAP_SIZE 4
#define TEXT_SHOW_MAP 5
#define TEXT_SHOW_OUTTRO 6
#define TEXT_GAME_OVER 7
#define TEXT_WIN 8

// define max map size
#define MAX_MAP_HEIGHT 10000
#define MAX_MAP_WIDTH 10000
#define MAX_MINES 10000

#define DIRECTION 8
const int dx[DIRECTION] = {-1,-1,0,1,1,1,0,-1};
const int dy[DIRECTION] = {0,1,1,1,0,-1,-1,-1};

struct Index
{
    int x;
    int y;
};

Index playerIndex;

// Function to show all Text in this game
void ShowText(int textCase);
// Get Events if user want to play again
bool ReplaySelection();
// Introduce about the rule of Minesweeper
void ShowIntroduction();

void GetPlayerMapSize(int& mapHeight, int& mapWidth, int& mines);
// Check number people enter is correct or not
bool CheckPlayerMapSize(double mapHeight, double mapWidth, double mines);

char** GenerateMap(int mapHeight, int mapWidth, int mines);

void SetMap(char** tmpMap, int mapHeight, int mapWidth, int mines);
char CountMinesSurround(char** tmpMap, int x, int , int mapHeight, int mapWidth);
Index GetPlayerIndex(int** visited, int mapHeight, int mapWidth);

void PlayMinesweeper(char** realMap, char** maskMap, int mapHeight, int mapWidth, int maxMove);

void ShowMap(char** MapTmp, int mapHeight, int mapWidth);
// Check people index input is correct or not
bool InsideMap(int indexX, int indexY, int mapHeight, int mapWidth);
bool checkPlayerIndex(int playerIndexX, int playerIndexY, int mapHeight, int mapWidth, int** visited);

// Show something to bye user
void ShowOuttro();

int main()
{
    ShowIntroduction();
    do
    {
        //Clean screen to start a new game
        system("CLS");

        int mapHeight = MAX_MAP_HEIGHT;
        int mapWidth = MAX_MAP_WIDTH;
        int mines = MAX_MINES;

        GetPlayerMapSize(mapHeight, mapWidth, mines);
        int maxMove = mapHeight*mapWidth-mines;
        
        char** realMap = GenerateMap(mapHeight, mapWidth, mines);
        char** maskMap = GenerateMap(mapHeight, mapWidth, mines);
        SetMap(realMap, mapHeight, mapWidth, mines);

        //ShowMap(realMap, m, n) to check Map (only for Developer) =)))
        //ShowMap(realMap, mapHeight, mapWidth);
        PlayMinesweeper(realMap, maskMap, mapHeight, mapWidth, maxMove);
    }while(ReplaySelection() == true);
    system("CLS");
    ShowOuttro();
    return 0;
}

// This function shows text when be called
void ShowText(int textCase)
{
    if(textCase == TEXT_REPLAY_SELECTION)
    {
        cout << "Do you want to play Minesweeper again? [Y/N]" << endl;
        cout << "[Y] to play again!" << endl << "[N] to quit" << endl;
    }
    if(textCase == TEXT_SHOW_INTRODUCTION)
    {
        cout << endl;
        cout << "Hello, welcome to Minesweeper v1.0" << endl << "Clone by: pknguyendev" << endl << "______________" << endl << endl;
        Sleep(2000);
        cout << "You need to enter index x and y to select square you want to open" << endl;
        cout << "If it is a mines in that square, you lose" << endl;
        cout << "You only win if you open all square which don't have any mine" << endl << "Good luck!" << endl;
        cout << "______________" << endl;
        Sleep(4000);
    }
    if(textCase == TEXT_GET_PLAYER_INDEX)
    {
        cout << "Please enter pix do you want to select: " << endl;
    }
    if(textCase == TEXT_SHOW_OUTTRO)
    {
        cout << "Have a nice day! See you again" << endl << "#From_pknguyendev_with_love" << endl << endl;
    }
    if(textCase == TEXT_GET_PLAYER_MAP_SIZE)
    {
        cout << "Please enter map height, map width, the number of mines" << endl;
    }
    if(textCase == TEXT_GAME_OVER)
    {
        cout << "YOU ARE DEAD" << endl;
        cout << "GAME OVER!" << endl << endl;
    }
    if(textCase == TEXT_WIN)
    {
        cout << "CONGRATULATION! YOU WIN" << endl << endl;
    }
}

bool ReplaySelection()
{
    char replay;
    do
    {
        ShowText(TEXT_REPLAY_SELECTION);
        cin >> replay;
    }while(replay != 'Y' && replay != 'N');

    if(replay == 'Y')
        return 1;
    return 0;
}

void ShowIntroduction()
{
    ShowText(TEXT_SHOW_INTRODUCTION);
}

void PlayMinesweeper(char** realMap, char** maskMap, int mapHeight, int mapWidth, int maxMove)
{
    // visited is a matrix to check init data from user: Not alow to input an index has been inputted before
    int** visited = new int*[mapHeight];
    for(int i = 0; i < mapHeight; i++)
            visited[i] = new int[mapWidth];
    
    for(int i = 0; i < mapHeight; i++)
        for(int j = 0; j < mapWidth; j++)
            visited[i][j] = 0;
            
    int playerMove = 0;
    bool isQuit = false;
    while(isQuit == false)
    {
        system("CLS");
        ShowMap(maskMap, mapHeight, mapWidth);
        playerIndex = GetPlayerIndex(visited, mapHeight, mapWidth);
        if(realMap[playerIndex.x][playerIndex.y] == '*')
        {
            ShowText(TEXT_GAME_OVER);
            ShowMap(realMap,mapHeight,mapWidth);

            cout << endl;
            isQuit = true;
        }
        else
        {
            maskMap[playerIndex.x][playerIndex.y] = realMap[playerIndex.x][playerIndex.y];
            playerMove++;
            if(realMap[playerIndex.x][playerIndex.y] == '0')
            {
                for(int k = 0; k < DIRECTION; k++)
                {
                    int u = playerIndex.x + dx[k];
                    int v = playerIndex.y + dy[k];
                    if(InsideMap(u, v, mapHeight, mapWidth) == 1 && visited[u][v] == 0)
                    {
                        maskMap[u][v] = realMap[u][v];
                        visited[u][v] = 1;
                        playerMove++;
                    }
                }
            }
            if(playerMove == maxMove)
            {
                ShowText(TEXT_WIN);
                ShowMap(realMap,mapHeight,mapWidth);
                cout << endl;
                isQuit = true;
            }
        }
    }
}

void GetPlayerMapSize(int& mapHeight, int& mapWidth, int& mines)
{
    double tmpMapHeight, tmpMapWidth, tmpMines;
    do
    {
        ShowText(TEXT_GET_PLAYER_MAP_SIZE);
        cout << "MAP HEIGHT: ";
        cin >> tmpMapHeight;
        cout << "MAP_WIDTH: ";
        cin  >> tmpMapWidth;
        cout << "THE NUMBER OF MINES: ";
        cin >> tmpMines;
        cout << endl;
    } while (CheckPlayerMapSize(tmpMapHeight, tmpMapWidth, tmpMines) == false);
    mapHeight = tmpMapHeight;
    mapWidth = tmpMapWidth;
    mines = tmpMines;
}

bool CheckPlayerMapSize(double mapHeight, double mapWidth, double mines)
{
    if(int(mapWidth) == mapWidth && int(mapHeight) == mapHeight && int(mines) == mines)
        return true;
    return false;
}

char** GenerateMap(int mapHeight, int mapWidth, int mines)
{
    char** tmpMap = new char*[mapHeight];
    for(int i = 0; i < mapHeight; i++)
        tmpMap[i] = new char[mapWidth];
    for(int i = 0; i < mapHeight; i++)
        for(int j = 0; j < mapWidth; j++)
            tmpMap[i][j] = 'o';
    return tmpMap;
}

// Set random mines in map
void SetMap(char** tmpMap, int mapHeight, int mapWidth, int mines)
{
    int i = 0;
    srand(time(NULL));
    while(i < mines)
    {
        int x = rand()%mapHeight;
        int y = rand()%mapWidth;
        if(tmpMap[x][y] != '*')
        {
            tmpMap[x][y] = '*';
            i++;
        }
    }
    cout << endl;
    for(int i = 0; i < mapHeight; i++)
    {
        for(int j = 0; j < mapWidth; j++)
        {
            if(tmpMap[i][j] == 'o')
            {
                tmpMap[i][j] = CountMinesSurround(tmpMap, i, j, mapHeight, mapWidth);
            }
        }
    }
}
char CountMinesSurround(char** tmpMap, int x, int y, int mapHeight, int mapWidth)
{
    int countMines = 0;
    for(int k = 0; k < DIRECTION; k++)
    {
        int u = x + dx[k];
        int v = y + dy[k];
        if(InsideMap(u, v, mapHeight, mapWidth) == 1 && tmpMap[u][v] == '*')
        {
            countMines++;
        }
    }
    return char(countMines+48);
}
void ShowMap(char** MapTmp, int mapHeight, int mapWidth)
{
    ShowText(TEXT_SHOW_MAP);
    for(int i = 0; i < mapHeight; i++)
    {
        for(int j = 0; j < mapWidth; j++)
            cout << MapTmp[i][j] << " ";
        cout << endl;
    }
}

Index GetPlayerIndex(int** visited, int mapHeight, int mapWidth)
{
    Index tmpPlayerIndex;
    do
    {
        ShowText(TEXT_GET_PLAYER_INDEX);
        cout << "Index X: ";
        cin >> tmpPlayerIndex.x;
        cout << "Index Y: ";
        cin >> tmpPlayerIndex.y;
        cout << endl; 
        tmpPlayerIndex.x--;
        tmpPlayerIndex.y--;
    } while (checkPlayerIndex(tmpPlayerIndex.x, tmpPlayerIndex.y, mapHeight, mapWidth, visited) == 0);
    return tmpPlayerIndex;
}

bool checkPlayerIndex(int playerIndexX, int playerIndexY, int mapHeight, int mapWidth, int** visited)
{
    if(InsideMap(playerIndexX, playerIndexY, mapHeight, mapWidth) == 0)
        return false;
    if(visited[playerIndexX][playerIndexY] == 0)
        visited[playerIndexX][playerIndexY] = 1;
    else
        return false;
    return true;
}

bool InsideMap(int indexX, int indexY, int mapHeight, int mapWidth)
{
    return indexX >= 0 && indexX < mapHeight && indexY >= 0 && indexY < mapWidth;
}

void ShowOuttro()
{
    ShowText(TEXT_SHOW_OUTTRO);
}
