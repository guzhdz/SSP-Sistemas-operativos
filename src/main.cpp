#include <iostream>
#include <list>
#include <string>
#include <limits>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include "Proceso.h"

using namespace std;

list<Proceso> lista = {};
list<Proceso> loteEnEjecucion = {};
list<Proceso> terminados = {};
Proceso procesoEnEjecucion;
int nLotes = 0;
int tiempoTranscurrido = 0;
int tiempoRestante = 0;
int loteActual = 0;
int tiempoGeneral = 0;

bool repetido(int id)
{
	for (Proceso proceso : lista)
	{
		if (id == proceso.id)
		{
			return true;
		}
	}
	return false;
}

void nuevoLote()
{
	nLotes--;
	loteActual++;
	for (int i = 0; i < 4; i++)
	{
		if (lista.size() > 0)
		{
			loteEnEjecucion.push_back(lista.front());
			lista.pop_front();
		}
	}
}

void printInfoLote()
{
	cout << "\t\tINFORMACION DE LOTES" << endl;
	cout << "\tNumero de lotes pendientes: " << nLotes << endl;
	cout << "\tLote Actual: " << loteActual << endl;
}

void addProceso()
{
	string nombre = "";
	int id = 0;
	float n1 = 0;
	float n2 = 0;
	int TME = 0;
	char operacion = ' ';

	cin.ignore();
	cout << "Nombre del programador" << endl;
	getline(cin, nombre);

	cout << "Que operacion deseas reealizar? (+, -, *, /, %)" << endl;
	cin >> operacion;
	cout << "Digita el operando 1" << endl;
	cin >> n1;

	do
	{
		cout << "Digita el operando 2" << endl;
		cin >> n2;
	} while (operacion == '/' && n2 == 0);

	do
	{
		cout << "Digita el TME" << endl;
		cin >> TME;
	} while (TME <= 0);

	do
	{
		cout << "Digita el numero de programa" << endl;
		cin >> id;
	} while (repetido(id));

	cout << endl;

	Proceso newProceso(nombre, operacion, n1, n2, TME, id);
	lista.push_back(newProceso);
}

void calculaNumLotes()
{
	nLotes = lista.size() / 4;

	if (lista.size() % 4 != 0)
		nLotes++;
}

float resuelveOperacion(Proceso proceso)
{
	switch (proceso.operacion)
	{
	case '+':
		return proceso.num1 + proceso.num2;
		break;
	case '-':
		return proceso.num1 - proceso.num2;
		break;
	case '*':
		return proceso.num1 * proceso.num2;
		break;
	case '/':
		return proceso.num1 / proceso.num2;
		break;
	case '%':
		return int(proceso.num1) % int(proceso.num2);
		break;
	default:
		break;
	}
	return 0;
}

void printLoteActual()
{
	cout << endl;
	cout << "\t\tLOTE ACTUAL" << endl;
	if (loteEnEjecucion.size() > 0)
	{
		for (Proceso proceso : loteEnEjecucion)
		{
			cout << "\tNombre del programador:" << proceso.nombre << endl;
			cout << "\tTME:" << proceso.tme << endl;
		}
	}
	else
	{
		cout << "\t\tVacio" << endl;
	}
}

void printProcesoEnEjecucion()
{
	cout << endl;
	cout << "\t\tPROCESO EN EJECUCION" << endl;
	cout << "\tNum de programa: " << procesoEnEjecucion.id << endl;
	cout << "\tNombre programador: " << procesoEnEjecucion.nombre << endl;
	cout << "\tOperacion: " << procesoEnEjecucion.num1 << procesoEnEjecucion.operacion << procesoEnEjecucion.num2 << endl;
	cout << "\tTME: " << procesoEnEjecucion.tme << endl;
}

void printTiempos()
{
	cout << endl;
	cout << "\t\tTIEMPOS" << endl;
	cout << "\tTiempo Transcurrido: " << tiempoTranscurrido << endl;
	cout << "\tTiempo Restante: " << tiempoRestante << endl;
	cout << "\tTiempo General: " << tiempoGeneral << endl;
}

void printTerminados()
{
	cout << endl;
	cout << "\t\tTERMINADOS" << endl;
	if (terminados.size() > 0)
	{
		for (Proceso proceso : terminados)
		{
			cout << "\tNum de programa: " << proceso.id << endl;
			cout << "\tOperacion: " << proceso.num1 << proceso.operacion << proceso.num2 << endl;
			cout << "\tResultado: " << resuelveOperacion(proceso) << endl;
			cout << endl;
		}
	}
	else
	{
		cout << "\t\tVacio" << endl;
	}
}

int main(int argc, char *argv[])
{
	bool nuevo = true;
	int opc = 0;

	cout << "Procesamiento por lotes" << endl;
	cout << "Nuevo Lote" << endl;

	while (nuevo)
	{
		addProceso();
		cout << "Desea ingresar otro registro? (SI = 1 / NO = 2)" << endl;
		cin >> opc;
		if (opc == 2)
		{
			nuevo = false;
		}
		system("cls");
	}

	calculaNumLotes();

	while (nLotes != 0)
	{
		nuevoLote();
		while (loteEnEjecucion.size() != 0)
		{
			procesoEnEjecucion = loteEnEjecucion.front();
			loteEnEjecucion.pop_front();

			tiempoRestante = procesoEnEjecucion.tme;
			while (tiempoRestante != 0)
			{
				printInfoLote();
				printLoteActual();
				printTerminados();

				tiempoTranscurrido++;
				tiempoRestante--;
				tiempoGeneral++;

				printProcesoEnEjecucion();
				printTiempos();

				Sleep(1300);
				system("cls");
			}
			tiempoTranscurrido = 0;
			terminados.push_back(procesoEnEjecucion);
		}
	}

	cout << "\t\tPROCESO FINALIZADO" << endl;
	cout << endl;
	printInfoLote();
	printTerminados();
	printTiempos();
	system("pause");
	return 0;
}
