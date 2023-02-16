#include <iostream>
#include <list>
#include <string>
#include <limits>
#include <Windows.h>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <cmath>
#include <math.h>
#include <iomanip>
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
int cont = 0;
int id = 1;
bool error = false;

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
	int op = 0;
	float n1 = 0;
	float n2 = 0;
	int TME = 0;
	char operacion = ' ';

	op = rand() % 5 + 1;
	switch (op)
	{
	case 1:
		operacion = '+';
		break;
	case 2:
		operacion = '-';
		break;
	case 3:
		operacion = '*';
		break;
	case 4:
		operacion = '/';
		break;
	case 5:
		operacion = '%';
		break;
	default:
		break;
	}

	n1 = rand() % 100 + 1;
	n2 = rand() % 100 + 1;
	TME = rand() % 12 + 5;

	cout << endl;

	Proceso newProceso(operacion, n1, n2, TME, id++, 0);
	// cout << newProceso.id << endl;
	lista.push_back(newProceso);
}

void calculaNumLotes()
{
	nLotes = lista.size() / 4;

	if (lista.size() % 4 != 0)
		nLotes++;
}

string resuelveOperacion(Proceso proceso)
{
	switch (proceso.operacion)
	{
	case '+':
		return (to_string(trunc(proceso.num1 + proceso.num2)));
		break;
	case '-':
		return (to_string(trunc(proceso.num1 - proceso.num2)));
		break;
	case '*':
		return (to_string(trunc(proceso.num1 * proceso.num2)));
		break;
	case '/':
		return (to_string(trunc(proceso.num1 / proceso.num2)));
		break;
	case '%':
		return (to_string(int(proceso.num1) % int(proceso.num2)));
		break;
	default:
		break;
	}
}

void printLoteActual()
{
	cout << endl;
	cout << "\t\tLOTE ACTUAL" << endl;
	if (loteEnEjecucion.size() > 0)
	{
		for (Proceso proceso : loteEnEjecucion)
		{
			cout << "\tID:" << proceso.id << "\tTME:" << proceso.tme << "\tTT: " << proceso.transcurrido << endl;
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
			if (cont < 4)
			{
				cout << "\tNum de programa: " << proceso.id << endl;
				cout << "\tOperacion: " << proceso.num1 << proceso.operacion << proceso.num2 << endl;
				cout << "\tResultado: " << resuelveOperacion(proceso) << endl;
				cout << endl;
			}
			else
			{
				cout << "\t--------------------" << endl;
				cout << "\tNum de programa: " << proceso.id << endl;
				cout << "\tOperacion: " << proceso.num1 << proceso.operacion << proceso.num2 << endl;
				cout << "\tResultado: " << resuelveOperacion(proceso) << endl;
				cout << endl;
				cont = 0;
			}

			cont++;
		}
	}
	else
	{
		cout << "\t\tVacio" << endl;
	}
}

void pausa()
{
	cout << "\tPrograma pausado, pulse 'c' para continuar" << endl;
	char ch = ' ';
	while (true)
	{
		if (kbhit())
		{
			ch = getch();
			if (ch == 'c')
			{
				break;
			}
		}
	}
}

void interrupt(Proceso proc)
{
	proc.transcurrido = tiempoTranscurrido - 1;
	loteEnEjecucion.push_back(proc);
}

void err(Proceso proc)
{
	proc.resultado = "error";
	terminados.push_back(proc);
	error = true;
}

int checkTecla(Proceso proc)
{
	char ch = ' ';
	if (kbhit())
	{
		ch = getch();
		switch (ch)
		{
		case 'p':
			pausa();
			return 0;
			break;
		case 'i':
			interrupt(proc);
			return 1;
			break;
		case 'e':
			err(proc);
			return 2;
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int test = 0;
	int nProcesos;
	int opc = 0;
	int opcTecla = 0;

	cout << "Procesamiento por lotes" << endl;
	cout << "Ingrese el numero de procesos a generar: ";
	cin >> nProcesos;

	for (int i = 0; i < nProcesos; i++)
	{
		addProceso();
	}

	calculaNumLotes();

	while (nLotes != 0)
	{
		nuevoLote();
		while (loteEnEjecucion.size() != 0)
		{
			error = false;
			procesoEnEjecucion = loteEnEjecucion.front();
			loteEnEjecucion.pop_front();

			tiempoRestante = procesoEnEjecucion.tme - procesoEnEjecucion.transcurrido;
			while (tiempoRestante != 0)
			{
				printInfoLote();
				printLoteActual();
				printTerminados();
				printProcesoEnEjecucion();
				printTiempos();
				cont = 0;

				opcTecla = checkTecla(procesoEnEjecucion);

				if (opcTecla == 1 || opcTecla == 2) // si la tecla es I o E
				{
					break;
				}

				tiempoTranscurrido++;
				tiempoRestante--;
				tiempoGeneral++;

				Sleep(1000);

				system("cls");
			}
			if (!error && (tiempoRestante == 0))
			{
				tiempoTranscurrido = 0;
				procesoEnEjecucion.resultado = resuelveOperacion(procesoEnEjecucion);
				terminados.push_back(procesoEnEjecucion);
			}
			else
			{
				tiempoTranscurrido = 0; // El tiempo transcurrido se guarda despues de una Interrupcion?
			}
		}
	}

	system("cls");
	cout << "\t\tPROCESO FINALIZADO" << endl;
	cout << endl;
	printInfoLote();
	printTerminados();
	printTiempos();
	system("pause");
	return 0;
}
