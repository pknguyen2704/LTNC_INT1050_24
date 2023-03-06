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
#define TEXT_SELECT_DIFFICULTY 6
#define TEXT_GAME_OVER 7
#define TEXT_WIN 8

#define MAX_LEVEL 3
#define EASY_MODE 1
#define MEDIUM_MODE 2
#define EXTREME_MODE 3

#define EASY_MODE_HEIGHT 8
#define EASY_MODE_WIDTH 8
#define EASY_MODE_MINES 10

#define MEDIUM_MODE_HEIGHT 15
#define MEDIUM_MODE_WIDTH 20
#define MEDIUM_MODE_MINES 50

#define EXTREME_MODE_HEIGHT 20
#define EXTREME_MODE_WIDTH 25
#define EXTREME_MODE_MINES 50


int MAX_WIDTH = EXTREME_MODE_WIDTH;
int MAX_HEIGHT = EXTREME_MODE_HEIGHT;
int MINES = EXTREME_MODE_MINES;
int MAX_MOVE = (MAX_WIDTH*MAX_HEIGHT)-MINES;

struct Index
{
    int x;
    int y;
};
Index playerIndex;

void ShowText(int text);
bool ReplayOption();
void ShowInstruction();
void SelectDifficulty();
bool CheckPlayerLevelSelection(int playerSelection);
void SetDifficulty(int playerSelection);
char** GenerateMap();
void SetMap(char** Map);
Index GetPlayerIndex(int** visited);
void PlayMinesweeper(char** realMap, char** shownMap);
void ShowMap(char** Map);
bool InsideMap(int indexX, int indexY);
void ShowOuttro();

int main()
{
    do
    {
        //Clean screen to start a new game
        system("CLS");

        ShowInstruction();
        SelectDifficulty();

        char** realMap = GenerateMap();
        char** shownMap = GenerateMap();
        SetMap(realMap);
        //shownMap to check Map (only for Developer) =)))
        //shownMap(realMap);
        PlayMinesweeper(realMap, shownMap);
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
        cout << "X - from " << 1 << " to " << MAX_HEIGHT << endl;
        cout << "Y - from " << 1 << " to " << MAX_WIDTH << endl; 
    }
    if(text == TEXT_SHOW_OUTTRO)
    {
        cout << "Have a nice day! See you again" << endl << "#From_pknguyendev_with_love";
        cout << endl;
    }
    if(text == TEXT_SELECT_DIFFICULTY)
    {
        cout << "Select level you want to play [1/2/3]?" << endl;
        cout << "1. Easy Mode" << endl;
        cout << "2. Medium Mode" << endl;
        cout << "3. Extreme Mode" << endl;
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

void PlayMinesweeper(char** realMap, char** shownMap)
{
    // visited is a matrix to check init data from user: Not alow to input an index has been inputted before
    int** visited = new int*[MAX_HEIGHT];
    for(int i = 0; i < MAX_HEIGHT; i++)
            visited[i] = new int[MAX_WIDTH];
    
    for(int i = 0; i < MAX_HEIGHT; i++)
        for(int j = 0; j < MAX_WIDTH; j++)
            visited[i][j] = 0;
            
    int playerMove = 0;
    bool isQuit = false;
    while(isQuit == false)
    {
        ShowMap(shownMap);
        playerIndex = GetPlayerIndex(visited);
        if(realMap[playerIndex.x][playerIndex.y] == '*')
        {
            ShowText(TEXT_GAME_OVER);
            ShowMap(realMap);
            cout << endl;
            isQuit = true;
        }
        else
        {
            realMap[playerIndex.x][playerIndex.y] = '1';
            shownMap[playerIndex.x][playerIndex.y] = '1';
            playerMove++;
            if(playerMove == MAX_MOVE)
            {
                ShowText(TEXT_WIN);
                ShowMap(realMap);
                cout << endl;
                isQuit = true;
            }
        }
    }
}

void SelectDifficulty()
{
    int playerSelection;
    do
    {
        ShowText(TEXT_SELECT_DIFFICULTY);
        cin >> playerSelection;
    } while (CheckPlayerLevelSelection(playerSelection) == false);
    
    SetDifficulty(playerSelection);
}

bool CheckPlayerLevelSelection(int playerSelection)
{
    return playerSelection >= 1 && playerSelection <= MAX_LEVEL;
}

void SetDifficulty(int playerSelection)
{
    if(playerSelection == EASY_MODE)
    {
        MAX_HEIGHT = EASY_MODE_HEIGHT;
        MAX_WIDTH = EASY_MODE_WIDTH;
        MINES = EASY_MODE_MINES;
        MAX_MOVE = (MAX_WIDTH*MAX_HEIGHT)-MINES;
    }
    if(playerSelection == MEDIUM_MODE)
    {
        MAX_HEIGHT = MEDIUM_MODE_HEIGHT;
        MAX_WIDTH = MEDIUM_MODE_WIDTH;
        MINES = MEDIUM_MODE_MINES;
        MAX_MOVE = (MAX_WIDTH*MAX_HEIGHT)-MINES;
    }
    if(playerSelection == EXTREME_MODE)
    {
        MAX_HEIGHT = EXTREME_MODE_HEIGHT;
        MAX_WIDTH = EXTREME_MODE_WIDTH;
        MINES = EXTREME_MODE_MINES;
        MAX_MOVE = (MAX_WIDTH*MAX_HEIGHT)-MINES;
    }
}

char** GenerateMap()
{
    char** tmpMap = new char*[MAX_HEIGHT];
    for(int i = 0; i < MAX_HEIGHT; i++)
        tmpMap[i] = new char[MAX_WIDTH];
    for(int i = 0; i < MAX_HEIGHT; i++)
        for(int j = 0; j < MAX_WIDTH; j++)
            tmpMap[i][j] = '0';
    return tmpMap;
}

// Set random mines in map
void SetMap(char** tmpMap)
{
    bool mark[MAX_HEIGHT*MAX_WIDTH];
    memset(mark,false,sizeof(mark));
    int i = 0;
    srand(time(NULL));
    while(i < MINES)
    {
        int random = rand()%(MAX_HEIGHT*MAX_WIDTH);
        int x = random/MAX_WIDTH;
        int y = random%MAX_HEIGHT;
        if (mark[random] == false)
        {
            tmpMap[x][y] = '*';
            mark[random] = true;
            i++;
        }
    }
}

void ShowMap(char** MapTmp)
{
    ShowText(TEXT_SHOW_MAP);
    for(int i = 0; i < MAX_HEIGHT; i++)
    {
        for(int j = 0; j < MAX_WIDTH; j++)
            cout << MapTmp[i][j] << " ";
        cout << endl;
    }
}

Index GetPlayerIndex(int** visited)
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
    } while (InsideMap(tmpPlayerIndex.x, tmpPlayerIndex.y) == false);
    
    system("CLS");
    return tmpPlayerIndex;
}

bool InsideMap(int indexX, int indexY)
{
    return indexX >= 0 && indexX < MAX_HEIGHT && indexY >= 0 && indexY < MAX_WIDTH;
}

void ShowOuttro()
{
    ShowText(TEXT_SHOW_OUTTRO);
}