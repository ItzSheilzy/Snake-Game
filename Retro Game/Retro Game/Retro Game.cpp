#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
using namespace std;


bool GameOver;

// world border size 
const int width = 40;
const int height = 20;

// x,y and score ints of the Snake and Fruit
int x, y, fruitX, fruitY, score;

// Tail ints
int tailX[100], tailY[100];
int nTail;


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
}


// Draw function
void Draw()
{
    // system clears the old map to update and the snake to move around
    system("Cls"); 

    // Top of the map
    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;

    // 2D array the prints the world border aswell as the snake head and fruit inside the border map
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
            {
                cout << "#"; // World border
            }
            if(i == y && j == x)
            {
                cout << "O"; // Snake head
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << "F"; // Fruit
            }
            // prints the body if the snake on the back of the snake head
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; 
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
    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << endl;
    // Score display
    cout << "score: " << score << endl;
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
        case 'q':
            cout << "Game quit." << endl;
            GameOver = true;          
            break;
        case 'p':
            cout << "Game Paused." << endl;
            system("Pause");
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

    
    // the border will end your game 
    /*if (x > width || x < 0 || y > height || y < 0)
    {
        cout << "Game Over." << endl;
        GameOver = true;
    }*/
        
        
    // so you can go through the borders of the map
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
    for (int i = 1; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
        {
            cout << "Game Over." << endl;
            GameOver = true;  
        }
            

    // randomises the fruit spawns on the map
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++; 
    }
}


// main setup and Game loop
int main()
{
    setup();
    while (!GameOver)
    {
        Draw();
        Input();
        Logic();

        // slows the game down because of faster CPU
        Sleep(30); 
    }
    return 0;
}