#include <iostream>
#include <cstring>
#include <ctime>
#include <stdlib.h>

using namespace std;

#define TEXT_REPLAY_OPTION 1
#define TEXT_SHOW_INSTRUCTION 2
#define TEXT_GET_PLAYER_INDEX 3
#define TEXT_SHOW_MAP 4
#define TEXT_SHOW_OUTTRO 5
#define TEXT_GAME_OVER 6
#define TEXT_WIN 7
#define TEXT_GET_PLAYER_MAP_SIZE 8


#define MAX_HEIGHT 100000
#define MAX_WIDTH 100000
#define MAX_MINES 100000

struct Index
{
    int x;
    int y;
};

Index playerIndex;

void ShowText(int text);
bool ReplayOption();
void ShowInstruction();
void GetPlayerMapOption(int& mapHeight, int& mapWidth, int& mines);
char** GenerateMap(int mapHeight, int mapWidth, int mines);
void SetMap(char** tmpMap, int mapHeight, int mapWidth, int mines);
Index GetPlayerIndex(int** visited, int mapHeight, int mapWidth);
bool CheckPlayerLevelSelection(int mapHeight, int mapWidth, int mines);
void PlayMinesweeper(char** realMap, char** shownMap, int mapHeight, int mapWidth, int maxMove);
void ShowMap(char** MapTmp, int mapHeight, int mapWidth);
bool InsideMap(int indexX, int indexY, int mapHeight, int mapWidth);
bool checkPlayerIndex(int playerIndexX, int playerIndexY, int mapHeight, int mapWidth, int** visited);
void ShowOuttro();

int main()
{
    do
    {
        //Clean screen to start a new game
        system("CLS");
        ShowInstruction();

        int m = MAX_HEIGHT;
        int n = MAX_WIDTH;
        int k = MAX_MINES;

        GetPlayerMapOption(m, n, k);
        int maxMove = m*n-k;
        
        char** realMap = GenerateMap(m,n,k);
        char** shownMap = GenerateMap(m,n,k);
        SetMap(realMap,m,n,k);

        //shownMap to check Map (only for Developer) =)))
        ShowMap(realMap, m, n);
        PlayMinesweeper(realMap, shownMap, m, n, maxMove);
    }while(ReplayOption() == true);
    ShowOuttro();
    return 0;
}

// This function shows text when be called
void ShowText(int text)
{
    if(text == TEXT_REPLAY_OPTION)
    {
        cout << "Do you want to play Minesweeper again? [Y/N]" << endl;
        cout << "[Y] to play again!" << endl << "[N] to quit" << endl;
    }
    if(text == TEXT_SHOW_INSTRUCTION)
    {
        cout << "Hello, welcome to Minesweeper v1.0" << endl << "Clone by: pknguyendev" << endl << "______________" << endl << endl;
        cout << "You need to enter index x and y to select square you want to open" << endl << "If it is a mines in that square, you lose" << endl;
        cout << "You only win if you open all square which don't have any mine" << endl << "Good luck!" << endl;
        cout << "______________" << endl;
    }
    if(text == TEXT_GET_PLAYER_INDEX)
    {
        cout << "Please enter coordinate of x and y do you want to select: " << endl;
    }
    if(text == TEXT_SHOW_OUTTRO)
    {
        cout << "Have a nice day! See you again" << endl << "#From_pknguyendev_with_love" << endl << endl;
    }
    if(text == TEXT_GET_PLAYER_MAP_SIZE)
    {
        cout << "Please enter m, n, k" << endl << "m is width" << endl << "n is height" << endl << "k is the number of Mine" << endl;
    }
    if(text == TEXT_GAME_OVER)
    {
        cout << "YOU ARE DEAD" << endl;
        cout << "GAME OVER!" << endl << endl;
    }
    if(text == TEXT_WIN)
    {
        cout << "CONGRATULATION! YOU WIN" << endl << endl;
    }
}

bool ReplayOption()
{
    char replay;
    do
    {
        ShowText(TEXT_REPLAY_OPTION);
        cin >> replay;
    }while(replay != 'Y' && replay != 'N');

    if(replay == 'Y')
        return 1;
    return 0;
}

void ShowInstruction()
{
    ShowText(TEXT_SHOW_INSTRUCTION);
}

void PlayMinesweeper(char** realMap, char** shownMap, int mapHeight, int mapWidth, int maxMove)
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
        ShowMap(shownMap,mapHeight,mapWidth);
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
            realMap[playerIndex.x][playerIndex.y] = '1';
            shownMap[playerIndex.x][playerIndex.y] = '1';
            playerMove++;
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

void GetPlayerMapOption(int& mapHeight, int& mapWidth, int& mines)
{
    int playerSelection;
    do
    {
        ShowText(TEXT_GET_PLAYER_MAP_SIZE);
        cout << "m: ";
        cin >> mapHeight;
        cout << "n: ";
        cin  >> mapWidth;
        cout << "k: ";
        cin >> mines;
        cout << endl;
    } while (CheckPlayerLevelSelection(mapHeight, mapWidth, mines) == false);
    
}

bool CheckPlayerLevelSelection(int mapHeight, int mapWidth, int mines)
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
            tmpMap[i][j] = '0';
    return tmpMap;
}

// Set random mines in map
void SetMap(char** tmpMap, int mapHeight, int mapWidth, int mines)
{
    bool mark[mapHeight*mapWidth];
    memset(mark,false,sizeof(mark));
    int i = 0;
    srand(time(NULL));
    while(i < mines)
    {
        int random = rand()%(mapHeight*mapWidth);
        int x = random/mapWidth;
        int y = random%mapHeight;
        if (mark[random] == false)
        {
            tmpMap[x][y] = '*';
            mark[random] = true;
            i++;
        }
    }
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
    
    system("CLS");
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