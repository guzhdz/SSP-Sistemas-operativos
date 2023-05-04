#include <string>
#include <iostream>

using namespace std;

class Proceso
{
public:
    int TiempoLlegada;
    int TiempoRetorno;
    int TiempoFinalizacion;
    int TiempoRespuesta;
    int TiempoEspera;
    int TiempoServicio;

    int TiempoEnEspera;
    int transcurrido;
    char operacion;
    float num1;
    float num2;
    int tme;
    int id;
    int tamanio;
    string resultado;

    Proceso()
    {
        this->TiempoEnEspera = 0;
        this->transcurrido = 0;
        this->resultado = "";
        this->operacion = '$';
        this->num1 = 0;
        this->num2 = 0;
        this->tme = 0;
        this->id = -1;
        this->tamanio = 0;
        this->TiempoLlegada = 0;
        this->TiempoFinalizacion = 0;
        this->TiempoRetorno = 0;
        this->TiempoRespuesta = -1;
        this->TiempoEspera = 0;
        this->TiempoServicio = 0;
    }

    Proceso(char ope, float n1, float n2, int t, int id, int transcurrido, int tam)
    {
        this->operacion = ope;
        this->num1 = n1;
        this->num2 = n2;
        this->tme = t;
        this->id = id;
        this->resultado = "";
        this->transcurrido = transcurrido;
        this->TiempoEnEspera = 0;
        this->TiempoLlegada = 0;
        this->TiempoFinalizacion = 0;
        this->TiempoRetorno = 0;
        this->TiempoRespuesta = -1;
        this->TiempoEspera = 0;
        this->TiempoServicio = 0;
        this->tamanio = tam;
    }
};