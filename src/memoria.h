#include <string>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include "Marco.h"
using namespace std;

class Memoria
{
public:
    Marco arr[40];
    int renglon = 0;

    Memoria()
    {
        this->fillMemoria();
    }

    void fillMemoria()
    {
        int id = 0;
        for (int j = 0; j < 2; j++)
        {
            Marco marco(id++, 5, "S.O");
            this->arr[j] = marco;
        }

        for (int i = 2; i < 40; i++)
        {
            Marco newMarco(id++, 0, "Libre");
            this->arr[i] = newMarco;
        }
    }

    void printMemoria()
    {
        renglon = 0;
        for (int i = 0; i < 40; i++)
        {
            this->arr[i].printMarco(renglon);
            renglon++;
            // cout << endl;
        }
    }

    int espaciosLibres()
    {
        int cont = 0;
        for (int i = 0; i < 40; i++)
        {
            if (this->arr[i].estado == "Libre")
            {
                cont++;
            }
        }
        return cont;
    }

    void liberarMemoria(int id)
    {
        for (int i = 0; i < 40; i++)
        {
            if (this->arr[i].estado == to_string(id))
            {
                this->arr[i].espacio = 0;
                this->arr[i].estado = "Libre";
            }
        }
    }
};