#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <string>
using namespace std;


//Arrow key Movments
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


//Gameover Boolian
bool GameOver;


//World border size 
const int width = 40;
const int height = 20;


//x,y and score ints of the Snake and Fruit
int x, y, fruitX, fruitY, score, fruits;


//Tail ints
int tailX[100], tailY[100];
int nTail;


//User Inputs there are more then 2 so the code doesn't break and mess up the game 
string input1 = " ";
string input2 = " ";


//Colours to make the game look pretty and also has a colour reset
const char* MAGENTA = "\x1b[95m";
const char* RED = "\x1b[91m";
const char* GREEN = "\x1b[92m";
const char* YELLOW = "\x1b[93m";
const char* WHITE = "\x1b[97m";
const char* RESET_COLOR = "\x1b[0m";


enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN, };
eDirecton dir;


//Setup for the game 
void setup()
{
    GameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    fruits = 0;
}


//Draw function
void Draw()
{
    //Array the prints the world border aswell as the snake head and fruit inside the border map
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == y && j == x)
            {
                cout << GREEN << "O"; //Snake head
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << WHITE << "F"; //Fruit
            }
            //Prints the body if the snake on the back of the snake head
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {

                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << GREEN << "o"; //Snake body
                        print = true;
                    }
                }
                //Printing blank spaces in the sized map
                if (!print)
                    cout << RED << "\xb0";
            }
        }
        cout << endl;
    }
    
    cout << RESET_COLOR << endl;
    //Score and fruit display
    cout << "Score: " << score << endl;
    cout << "Fruits collected: " << fruits << endl;
}


//Makes the frames not flicker when you open the the game
void UpdateFrame()
{
    COORD cursorPosition{};
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}


//Movment controls of the snake
void Input()
{
    if (_kbhit())
    {
        //Arrow key Movments
        switch (_getch())
        {
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;

            //WASD Movments
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;

            //Pause function
        case 'p':
            system("cls");
            cout << "Game Paused." << endl;
            cout << "Score: " << score << endl;
            cout << "Fruits: " << fruits << endl;
            cout << "Would you like to Continue 'Y'/'N'" << endl;
            cin >> input1;
            system("cls");
            if (input1 == "Y" || input1 == "y")
            {
                GameOver = false;
            }
            else if (input1 == "N" || input1 == "n")
            {
                cout << "Game Quit." << endl;
                cout << "Final Scores: " << score << endl;
                cout << "Final Fruits: " << fruits << endl;
                GameOver = true;
            }
            else
            {
                cout << "Invalid Command." << endl;
                system("pause");
                system("cls");
            }
            break;
        }
    }
}


// logic and physics of the game
void Logic()
{
    // adding onto the back of the snake Head 
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // direction of the snake 
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //GameMode Choice input detecter so if it dectects the user type and enter 1 or 2 it will assign and play that Gamemode.
    //if it dectects a invalid input command it will end the program  
    if (input2 == "1")
    {

        if (x > width || x < 0 || y > height || y < 0)
        {
            system("cls");
            cout << "Game Over." << endl;
            cout << "Final score: " << score << endl;
            cout << "Total Fruits: " << fruits << endl;
            system("pause");
            GameOver = true;
        }
    }
    else if (input2 == "2")
    {

        if (x >= width) x = 0; else if (x < 0) x = width - 1;
        if (y >= height) y = 0; else if (y < 0) y = height - 1;
    }
    else
    {
        system("cls");
        cout << RED << "Invalid Command." << RESET_COLOR << endl;
        GameOver = true;
    }

    for (int i = 1; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
        {
            system("cls");
            cout << "Game Over." << endl;
            cout << "Final score: " << score << endl;
            cout << "Total Fruits: " << fruits << endl;
            system("pause");
            GameOver = true;
        }

    //Random fruit position Generator
    if (x == fruitX && y == fruitY)
    {
        fruits += 1;
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}


int main()
{
    //Main Menu
    cout << YELLOW << "time to Select one of the two GameModes Woohoo!!!" << endl;
    cout << endl << "Select a GameMode by pressing 1 or 2 and then press enter and lets play." << endl;
    cout << "Select '1' to play the Game with the Border on, select '2' to Play with the Border off" << RESET_COLOR << endl;
    getline(cin, input2);
    system("cls");

    //Main Game Loop
    setup();
    while (!GameOver)
    {
        Draw();
        UpdateFrame();
        Input();
        Logic();

        //Slows the game down for the people running the game with a faster CPU
        Sleep(50);
    }
    return 0;
}