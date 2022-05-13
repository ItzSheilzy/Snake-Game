#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <string>

using namespace std;

// Gameover Boolian
bool GameOver;

// world border size 
const int width = 40;
const int height = 20;

// x,y and score ints of the Snake and Fruit
int x, y, fruitX, fruitY, score , fruits;

// Tail ints
int tailX[100], tailY[100];
int nTail;

//User Inputs there are more then 2 so the code doesn't break and mess up the game 
string input1 = " ";
string input2 = " ";


//Colours to make the game look pretty
const char* MAGENTA = "\x1b[95m";
const char* RED = "\x1b[91m";
const char* GREEN = "\x1b[92m";
const char* YELLOW = "\x1b[93m";
const char* WHITE = "\x1b[97m";
const char* RESET_COLOR = "\x1b[0m";


enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN,};
eDirecton dir;


// setup for the game 
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


// Draw function
void Draw()
{
    // Top of the map
    for (int i = 0; i < width + 1; i++)
    {
        cout << RED << "#";
    } 
    cout << endl;

    // Array the prints the world border aswell as the snake head and fruit inside the border map
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
            {
                cout << RED << "#"; // World border
            }
            if(i == y && j == x)
            {
                cout << GREEN << "O"; // Snake head
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << WHITE << "F"; // Fruit
            }
            // prints the body if the snake on the back of the snake head
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << GREEN << "o"; 
                        print = true;
                    }
                } 
                // printing blank spaces in the sized map
                if (!print)
                    cout << " ";
                
            }
        }
        cout << endl;
    }
    // bottom of the map
    for (int i = 0; i < width + 1; i++)
    {
        cout << RED << "#";
    }
    cout << RESET_COLOR << endl;
    // Score display
    cout << "Score: " << score << endl;
    cout << "Fruits collected: " << fruits << endl;
}


// makes the frames not flicker when you open the the game
void UpdateFrame()
{
    COORD cursorPosition;	
    cursorPosition.X = 0;	
    cursorPosition.Y = 0;	
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}


// Movment controls of the snake
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
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


    if (x == fruitX && y == fruitY)
    {
        fruits += 1;
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}


// main setup and Game loop
int main()
{
    cout << YELLOW << "Welcome to Snake a fun little game that anyone can play." << endl;
    cout << "I hope you enjoy it because this took me a long time and a lot of pain. HA HA HA" << endl;
    cout << endl << "Please select a GameMode" << endl;
    cout << "Select '1' to play the Game with the Border on, select '2' to Play with the Border off" << RESET_COLOR << endl;
    getline(cin, input2);
    system("cls");
    

    setup();
    while (!GameOver)
    {
        Draw();
        UpdateFrame();
        Input();
        Logic();


        if (input2 == "1")
        {
            if (x + 2 > width || x < 0 || y > height || y < 0)
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
            if (x + 1 >= width) x = 0; else if (x < 0) x = width - 2;
            if (y >= height) y = 0; else if (y < 0) y = height - 1;
        }
        else
        {
            system("cls");
            cout << "Invalid Command." << endl;
            return 1;
        }

        // slows the game down for the people running the game with a faster CPU
        Sleep(50);
    }
    return 0;
}