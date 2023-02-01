#include <string>
#include <iostream>
using namespace std;

class Proceso
{
public:
    string nombre;
    char operacion;
    float num1;
    float num2;
    int tme;
    int id;

    Proceso()
    {
        this->nombre = "";
        this->operacion = '$';
        this->num1 = 0;
        this->num2 = 0;
        this->tme = 0;
        this->id = -1;
    }

    Proceso(string nom, char ope, float n1, float n2, int t, int id)
    {
        this->nombre = nom;
        this->operacion = ope;
        this->num1 = n1;
        this->num2 = n2;
        this->tme = t;
        this->id = id;
    }
};