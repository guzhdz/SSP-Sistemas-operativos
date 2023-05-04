#include <string>
#include <iostream>
#include <list>
#include <string>
#include <limits>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <cmath>
#include <math.h>
#include <iomanip>

using namespace std;

class Marco
{
public:
    int id;
    int espacio;
    string estado;

    Marco()
    {
        this->estado = "Libre";
        this->espacio = 0;
    }

    Marco(int id, int esp, string est)
    {
        this->id = id;
        this->estado = est;
        this->espacio = esp;
    }

    void printMarco(int renglon)
    {
        gotoxy(70, renglon);
        cout << this->id << "  " << this->espacio << "/5"
             << "  " << this->estado;
    }

    void gotoxy(int x, int y)
    {
        HANDLE hcon;
        hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD dwPos;
        dwPos.X = x;
        dwPos.Y = y;
        SetConsoleCursorPosition(hcon, dwPos);
    }
};