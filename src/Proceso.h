#include <string>
#include <iostream>
using namespace std;

class Proceso
{
public:
    int transcurrido;
    char operacion;
    float num1;
    float num2;
    int tme;
    int id;
    string resultado;

    Proceso()
    {
        this->transcurrido = 0;
        this->resultado = "";
        this->operacion = '$';
        this->num1 = 0;
        this->num2 = 0;
        this->tme = 0;
        this->id = -1;
    }

    Proceso(char ope, float n1, float n2, int t, int id, int transcurrido)
    {
        this->operacion = ope;
        this->num1 = n1;
        this->num2 = n2;
        this->tme = t;
        this->id = id;
        this->resultado = "";
        this->transcurrido = transcurrido;
    }
};