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
#include <fstream>
#include "Proceso.h"
#include "memoria.h"

using namespace std;

list<Proceso> nuevos = {};
list<Proceso> listos = {};
list<Proceso> bloqueados = {};
list<Proceso> terminados = {};
list<Proceso> suspendidos = {};
Proceso procesoEnEjecucion;
Proceso procesoComodin;
Memoria memoria;

// int nLotes = 0;
// int numNuevos = 0;
int tiempoTranscurrido = 0;
int tiempoRestante = 0;
int loteActual = 0;
int tiempoGeneral = 0;
int cont = 0;
int id = 1;
bool error = false;
bool bloqueado = false;

int nProcesos = 0;
int nProcesosEnMemoria = 0;
int quantum = 0;
int quantumInicial = 0;
int quantumImprime = 0;

void llenaMemoria()
{
	int pags;
	int contador = 0;
	for (Proceso proceso : nuevos)
	{
		bool mocha = false;
		int i = 0;
		int j = 0;

		pags = proceso.tamanio / 5;
		int residuo = proceso.tamanio % 5;
		if (residuo > 0)
		{
			pags++;
			mocha = true;
		}

		if (pags <= memoria.espaciosLibres())
		{
			for (i = 0; i < pags; i++)
			{
				if (i == pags - 1)
				{
					if (mocha)
					{
						for (j = 0; j < sizeof(memoria.arr); j++)
						{
							if (memoria.arr[j].espacio == 0)
							{
								memoria.arr[j].espacio = residuo;
								memoria.arr[j].estado = to_string(proceso.id);
								break;
							}
						}
					}
					else
					{
						for (j = 0; j < sizeof(memoria.arr); j++)
						{
							if (memoria.arr[j].espacio == 0)
							{
								memoria.arr[j].espacio = 5;
								memoria.arr[j].estado = to_string(proceso.id);
								break;
							}
						}
					}
				}
				else
				{
					for (j = 0; j < sizeof(memoria.arr); j++)
					{
						if (memoria.arr[j].espacio == 0)
						{
							memoria.arr[j].espacio = 5;
							memoria.arr[j].estado = to_string(proceso.id);
							break;
						}
					}
				}
			}
			listos.push_back(proceso);
			contador++;
		}
	}

	for (int k = 0; k < contador; k++)
	{
		nuevos.pop_front();
	}

	// for (int i = 0; i < 4; i++)
	// {
	// 	if (nuevos.size() > 0)
	// 	{
	// 		// numNuevos--;
	// 		listos.push_back(nuevos.front());
	// 		nuevos.pop_front();
	// 	}
	// }
}

void printInfoNuevos()
{
	cout << "\t\tINFORMACION DE PROCESOS" << endl;
	cout << "\tNuevos: " << nuevos.size() << endl;
	cout << "\tValor del Quantum: " << quantumInicial << endl;
	// cout << "\tValor del Quantum Acual: " << quantum << endl;
	// cout << "\tLote Actual: " << loteActual << endl;
}

void printSuspendidos()
{
	cout << endl;
	cout << "\tProcesos suspendidos: " << suspendidos.size() << endl;
	cout << "\tInfo Proximo suspendido a regresar" << endl;
	if (suspendidos.size() > 0)
	{
		cout << "\tID: " << suspendidos.front().id << "  Tamanio: " << suspendidos.front().tamanio << endl;
	}
	else
	{
		cout << "\tID: -1   Tamanio:  -1 " << endl;
	}
}

void printSigNuevo()
{
	cout << endl;
	cout << "\t\tSiguiente Nuevo: " << endl;
	cout << "\tID: " << nuevos.front().id << "\tTamanio: " << nuevos.front().tamanio;
	cout << endl;
}

void addProceso()
{
	int op = 0;
	float n1 = 0;
	float n2 = 0;
	int TME = 0;
	int tam = 0;
	char operacion = ' ';

	op = (rand() % 5) + 1;
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

	n1 = (rand() % 100) + 1;
	n2 = (rand() % 100) + 1;
	TME = (rand() % 11) + 5;
	tam = (rand() % 19) + 6;

	cout << endl;

	Proceso newProceso(operacion, n1, n2, TME, id++, 0, tam);
	// cout << newProceso.id << endl;
	nuevos.push_back(newProceso);
}

void addNuevo()
{
	addProceso();

	bool mocha = false;
	int i = 0;
	int j = 0;
	int pags;

	pags = nuevos.front().tamanio / 5;
	int residuo = nuevos.front().tamanio % 5;
	if (residuo > 0)
	{
		pags++;
		mocha = true;
	}

	if (pags <= memoria.espaciosLibres())
	{
		for (i = 0; i < pags; i++)
		{
			if (i == pags - 1)
			{
				if (mocha)
				{
					for (j = 0; j < sizeof(memoria.arr); j++)
					{
						if (memoria.arr[j].espacio == 0)
						{
							memoria.arr[j].espacio = residuo;
							memoria.arr[j].estado = to_string(nuevos.front().id);
							break;
						}
					}
				}
				else
				{
					for (j = 0; j < sizeof(memoria.arr); j++)
					{
						if (memoria.arr[j].espacio == 0)
						{
							memoria.arr[j].espacio = 5;
							memoria.arr[j].estado = to_string(nuevos.front().id);
							break;
						}
					}
				}
			}
			else
			{
				for (j = 0; j < sizeof(memoria.arr); j++)
				{
					if (memoria.arr[j].espacio == 0)
					{
						memoria.arr[j].espacio = 5;
						memoria.arr[j].estado = to_string(nuevos.front().id);
						break;
					}
				}
			}
		}
		nuevos.front().TiempoLlegada = tiempoGeneral;
		listos.push_back(nuevos.front());
		nuevos.pop_front();
		nProcesosEnMemoria++;
	}

	// if (listos.size() + bloqueados.size() <= 3)
	// {
	// 	if (procesoEnEjecucion.id == -1)
	// 	{
	// 		nuevos.front().TiempoLlegada = tiempoGeneral;
	// 		listos.push_back(nuevos.front());
	// 		nuevos.pop_front();
	// 		nProcesosEnMemoria++;
	// 	}
	// 	else if (listos.size() + bloqueados.size() < 3)
	// 	{
	// 		nuevos.front().TiempoLlegada = tiempoGeneral;
	// 		listos.push_back(nuevos.front());
	// 		nuevos.pop_front();
	// 		nProcesosEnMemoria++;
	// 	}
	// }

	nProcesos++;
}

// void calculaNumLotes()
// {
// 	nLotes = lista.size() / 4;

// 	if (lista.size() % 4 != 0)
// 		nLotes++;
// }

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

void printListos()
{
	cout << endl;
	cout << "\t\tListos" << endl;
	if (listos.size() > 0)
	{
		for (Proceso proceso : listos)
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
	cout << "\tTamanio: " << procesoEnEjecucion.tamanio << endl;
	cout << "\tTME: " << procesoEnEjecucion.tme << endl;
}

void printTiempos()
{
	cout << endl;
	cout << "\t\tTIEMPOS" << endl;
	cout << "\tQuantum: " << quantumImprime << endl;
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
			cout << "\tResultado: " << proceso.resultado << endl; // Truncar decimales
			cout << endl;
		}
	}
	else
	{
		cout << "\t\tVacio" << endl;
	}
}

void printTablaTerminados()
{
	cout << endl;
	cout << "\t\tTABLA DE DATOS DE PROCESOS" << endl;
	if (terminados.size() > 0)
	{
		for (Proceso proceso : terminados)
		{
			cout << "\tNum de programa: " << proceso.id << endl;
			cout << "\tTME: " << proceso.tme << endl;
			cout << "\tOperacion: " << proceso.num1 << proceso.operacion << proceso.num2 << endl;
			cout << "\tResultado: " << proceso.resultado << endl; // Truncar decimales

			cout << "\tTiempo de Llegada: " << proceso.TiempoLlegada << endl;
			cout << "\tTiempo de Finalizacion: " << proceso.TiempoFinalizacion << endl;
			cout << "\tTiempo de Retorno: " << proceso.TiempoRetorno << endl;
			cout << "\tTiempo de Respuesta: " << proceso.TiempoRespuesta << endl;
			cout << "\tTiempo de Espera: " << proceso.TiempoEspera << endl;
			cout << "\tTiempo de Servicio: " << proceso.TiempoServicio << endl;

			cout << endl;
		}
	}
	else
	{
		cout << "\t\tVacio" << endl;
	}
}

void printBloqueados()
{
	cout << endl;
	cout << "\t\tBLOQUEADOS" << endl;
	if (bloqueados.size() > 0)
	{
		for (Proceso proceso : bloqueados)
		{
			cout << "\tNum de programa: " << proceso.id << endl;
			cout << "\tTiempo en bloqueado: " << proceso.TiempoEnEspera << endl;
			cout << endl;
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
	bloqueado = true;
	bloqueados.push_back(proc);
}

void err(Proceso proc)
{
	proc.resultado = "error";

	nProcesos--;
	nProcesosEnMemoria--;

	error = true;
	bool otro = false;
	bool mocha = false;

	proc.TiempoFinalizacion = tiempoGeneral;
	proc.TiempoRetorno = proc.TiempoFinalizacion - proc.TiempoLlegada;
	proc.TiempoServicio = proc.transcurrido;
	proc.TiempoEspera = proc.TiempoRetorno - proc.TiempoServicio;
	memoria.liberarMemoria(proc.id);
	terminados.push_back(proc);

	// meter a listos un proceso nuevo
	do
	{
		if (nuevos.size() > 0)
		{
			mocha = false;
			int i = 0;
			int j = 0;
			int pags;

			pags = nuevos.front().tamanio / 5;
			int residuo = nuevos.front().tamanio % 5;

			if (residuo > 0)
			{
				pags++;
				mocha = true;
			}

			if (pags <= memoria.espaciosLibres())
			{
				for (i = 0; i < pags; i++)
				{
					if (i == pags - 1)
					{
						if (mocha)
						{
							for (j = 0; j < sizeof(memoria.arr); j++)
							{
								if (memoria.arr[j].espacio == 0)
								{
									memoria.arr[j].espacio = residuo;
									memoria.arr[j].estado = to_string(nuevos.front().id);
									break;
								}
							}
						}
						else
						{
							for (j = 0; j < sizeof(memoria.arr); j++)
							{
								if (memoria.arr[j].espacio == 0)
								{
									memoria.arr[j].espacio = 5;
									memoria.arr[j].estado = to_string(nuevos.front().id);
									break;
								}
							}
						}
					}
					else
					{
						for (j = 0; j < sizeof(memoria.arr); j++)
						{
							if (memoria.arr[j].espacio == 0)
							{
								memoria.arr[j].espacio = 5;
								memoria.arr[j].estado = to_string(nuevos.front().id);
								break;
							}
						}
					}
				}
				nuevos.front().TiempoLlegada = tiempoGeneral;
				listos.push_back(nuevos.front());
				nuevos.pop_front();
				nProcesosEnMemoria++;
				otro = true;
			}
			else
			{
				otro = false;
			}
		}
		else
		{
			otro = false;
		}
	} while (otro);
}

void muestraTabla()
{
	cout << endl;
	cout << "\t\tTABLA DE DATOS DE PROCESOS" << endl;
	if (listos.size() > 0)
	{
		for (Proceso proceso : listos)
		{
			cout << "\tNum de programa: " << proceso.id << endl;
			cout << "\tEstado: Listo" << endl;
			cout << "\tTME: " << proceso.tme << endl;
			cout << "\tOperacion: " << proceso.num1 << proceso.operacion << proceso.num2 << endl;
			cout << "\tResultado: N/A" << endl;

			cout << "\tTiempo de Llegada: " << proceso.TiempoLlegada << endl;
			cout << "\tTiempo de Finalizacion: N/A" << endl;
			cout << "\tTiempo de Retorno: N/A" << endl;

			if (proceso.TiempoRespuesta > -1)
				cout << "\tTiempo de Respuesta: " << proceso.TiempoRespuesta << endl;
			else
				cout << "\tTiempo de Respuesta: N/A" << endl;

			cout << "\tTiempo de Espera: " << tiempoGeneral - proceso.transcurrido - proceso.TiempoLlegada << endl;
			cout << "\tTiempo de Servicio: " << proceso.transcurrido << endl;
			cout << "\tTiempo Restante en CPU: " << proceso.tme - proceso.transcurrido << endl;

			cout << endl;
		}
	}

	if (bloqueados.size() > 0)
	{
		for (Proceso proceso : bloqueados)
		{
			cout << "\tNum de programa: " << proceso.id << endl;
			cout << "\tEstado: Bloqueado" << endl;
			cout << "\tTME: " << proceso.tme << endl;
			cout << "\tOperacion: " << proceso.num1 << proceso.operacion << proceso.num2 << endl;
			cout << "\tResultado: N/A" << endl;

			cout << "\tTiempo de Llegada: " << proceso.TiempoLlegada << endl;
			cout << "\tTiempo de Finalizacion: N/A" << endl;
			cout << "\tTiempo de Retorno: N/A" << endl;

			if (proceso.TiempoRespuesta > -1)
				cout << "\tTiempo de Respuesta: " << proceso.TiempoRespuesta << endl;
			else
				cout << "\tTiempo de Respuesta: N/A" << endl;

			cout << "\tTiempo de Espera: " << tiempoGeneral - proceso.transcurrido - proceso.TiempoLlegada << endl;
			cout << "\tTiempo de Servicio: " << proceso.transcurrido << endl;
			cout << "\tTiempo Restante en CPU: " << proceso.tme - proceso.transcurrido << endl;
			cout << "\tTiempo Restante en Bloqueado: " << 8 - proceso.TiempoEnEspera << endl;

			cout << endl;
		}
	}

	if (nuevos.size() > 0)
	{
		for (Proceso proceso : nuevos)
		{
			cout << "\tNum de programa: " << proceso.id << endl;
			cout << "\tEstado: Nuevo" << endl;
			cout << "\tTME: " << proceso.tme << endl;
			cout << "\tOperacion: " << proceso.num1 << proceso.operacion << proceso.num2 << endl;
			cout << "\tResultado: N/A" << endl;

			cout << "\tTiempo de Llegada: N/A" << endl;
			cout << "\tTiempo de Finalizacion: N/A" << endl;
			cout << "\tTiempo de Retorno: N/A" << endl;
			cout << "\tTiempo de Respuesta: N/A" << endl;

			cout << "\tTiempo de Espera: N/A" << endl;
			cout << "\tTiempo de Servicio: N/A" << endl;
			cout << "\tTiempo Restante en CPU: " << proceso.tme << endl;

			cout << endl;
		}
	}

	if (terminados.size() > 0)
	{
		for (Proceso proceso : terminados)
		{
			cout << "\tNum de programa: " << proceso.id << endl;
			cout << "\tEstado: Terminado" << endl;
			if (proceso.resultado == "error")
				cout << "\tEstado de terminado: Por error" << endl;
			else
				cout << "\tEstado de terminado: Normal" << endl;

			cout << "\tTME: " << proceso.tme << endl;
			cout << "\tOperacion: " << proceso.num1 << proceso.operacion << proceso.num2 << endl;
			cout << "\tResultado: " << proceso.resultado << endl; // Truncar decimales

			cout << "\tTiempo de Llegada: " << proceso.TiempoLlegada << endl;
			cout << "\tTiempo de Finalizacion: " << proceso.TiempoFinalizacion << endl;
			cout << "\tTiempo de Retorno: " << proceso.TiempoRetorno << endl;
			cout << "\tTiempo de Respuesta: " << proceso.TiempoRespuesta << endl;
			cout << "\tTiempo de Espera: " << proceso.TiempoEspera << endl;
			cout << "\tTiempo de Servicio: " << proceso.TiempoServicio << endl;

			cout << endl;
		}
	}

	if (procesoEnEjecucion.id != -1)
	{
		cout << "\tNum de programa: " << procesoEnEjecucion.id << endl;
		cout << "\tEstado: Ejecucion" << endl;
		cout << "\tTME: " << procesoEnEjecucion.tme << endl;
		cout << "\tOperacion: " << procesoEnEjecucion.num1 << procesoEnEjecucion.operacion << procesoEnEjecucion.num2 << endl;
		cout << "\tResultado: N/A" << endl;

		cout << "\tTiempo de Llegada: " << procesoEnEjecucion.TiempoLlegada << endl;
		cout << "\tTiempo de Finalizacion: N/A" << endl;
		cout << "\tTiempo de Retorno: N/A" << endl;

		if (procesoEnEjecucion.TiempoRespuesta > -1)
			cout << "\tTiempo de Respuesta: " << procesoEnEjecucion.TiempoRespuesta << endl;
		else
			cout << "\tTiempo de Respuesta: N/A" << endl;

		cout << "\tTiempo de Espera: " << tiempoGeneral - procesoEnEjecucion.transcurrido - procesoEnEjecucion.TiempoLlegada << endl;
		cout << "\tTiempo de Servicio: " << procesoEnEjecucion.transcurrido << endl;
		cout << "\tTiempo Restante en CPU: " << procesoEnEjecucion.tme - procesoEnEjecucion.transcurrido << endl;
	}

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

void suspendido()
{
	Proceso proc;
	bool otro = false;
	bool mocha = false;
	if (bloqueados.size() > 0)
	{
		proc = bloqueados.front();

		nProcesosEnMemoria--;
		bloqueados.pop_front();

		memoria.liberarMemoria(proc.id);
		suspendidos.push_back(proc);

		// escribir proceso en el archivo
		ofstream archivo("suspendidos.txt", ofstream::out | ofstream::app);
		if (!archivo.is_open())
		{
			cout << "Error al abrir suspendidos.txt\n";
			exit(EXIT_FAILURE);
		}
		else
		{
			archivo << "ID: " << proc.id << "\tTamanio: " << proc.tamanio << "\tTME: " << proc.tme << endl;
		}

		archivo.close();

		do // Verficar si cabe un proceso nuevo en memoria
		{
			if (nuevos.size() > 0)
			{
				mocha = false;
				int i = 0;
				int j = 0;
				int pags;

				pags = nuevos.front().tamanio / 5;
				int residuo = nuevos.front().tamanio % 5;

				if (residuo > 0)
				{
					pags++;
					mocha = true;
				}

				if (pags <= memoria.espaciosLibres())
				{
					for (i = 0; i < pags; i++)
					{
						if (i == pags - 1)
						{
							if (mocha)
							{
								for (j = 0; j < sizeof(memoria.arr); j++)
								{
									if (memoria.arr[j].espacio == 0)
									{
										memoria.arr[j].espacio = residuo;
										memoria.arr[j].estado = to_string(nuevos.front().id);
										break;
									}
								}
							}
							else
							{
								for (j = 0; j < sizeof(memoria.arr); j++)
								{
									if (memoria.arr[j].espacio == 0)
									{
										memoria.arr[j].espacio = 5;
										memoria.arr[j].estado = to_string(nuevos.front().id);
										break;
									}
								}
							}
						}
						else
						{
							for (j = 0; j < sizeof(memoria.arr); j++)
							{
								if (memoria.arr[j].espacio == 0)
								{
									memoria.arr[j].espacio = 5;
									memoria.arr[j].estado = to_string(nuevos.front().id);
									break;
								}
							}
						}
					}
					nuevos.front().TiempoLlegada = tiempoGeneral;
					listos.push_back(nuevos.front());
					nuevos.pop_front();
					nProcesosEnMemoria++;
					otro = true;
				}
				else
				{
					otro = false;
				}
			}
			else
			{
				otro = false;
			}
		} while (otro);
	}
}

void regresa()
{
	int mocha = false;
	if (suspendidos.size() > 0)
	{
		mocha = false;
		int i = 0;
		int j = 0;
		int pags;

		pags = suspendidos.front().tamanio / 5;
		int residuo = suspendidos.front().tamanio % 5;

		if (residuo > 0)
		{
			pags++;
			mocha = true;
		}

		if (pags <= memoria.espaciosLibres())
		{
			for (i = 0; i < pags; i++)
			{
				if (i == pags - 1)
				{
					if (mocha)
					{
						for (j = 0; j < sizeof(memoria.arr); j++)
						{
							if (memoria.arr[j].espacio == 0)
							{
								memoria.arr[j].espacio = residuo;
								memoria.arr[j].estado = to_string(suspendidos.front().id);
								break;
							}
						}
					}
					else
					{
						for (j = 0; j < sizeof(memoria.arr); j++)
						{
							if (memoria.arr[j].espacio == 0)
							{
								memoria.arr[j].espacio = 5;
								memoria.arr[j].estado = to_string(suspendidos.front().id);
								break;
							}
						}
					}
				}
				else
				{
					for (j = 0; j < sizeof(memoria.arr); j++)
					{
						if (memoria.arr[j].espacio == 0)
						{
							memoria.arr[j].espacio = 5;
							memoria.arr[j].estado = to_string(suspendidos.front().id);
							break;
						}
					}
				}
			}
			listos.push_back(suspendidos.front());
			suspendidos.pop_front();
			nProcesosEnMemoria++;

			// sacar del archivo
			remove("suspendidos.txt");

			ofstream archivo("suspendidos.txt", ofstream::out | ofstream::app);
			if (!archivo.is_open())
			{
				cout << "Error al abrir suspendidos.txt\n";
				exit(EXIT_FAILURE);
			}
			else
			{
				for (Proceso proceso : suspendidos)
				{
					archivo << "ID: " << proceso.id << "\tTamanio: " << proceso.tamanio << "\tTME: " << proceso.tme << endl;
				}
			}

			archivo.close();
		}
	}
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
		case 'n':
			addNuevo();
			return 3;
			break;
		case 't':
			muestraTabla();
			return 4;
			break;
		case 'a':
			pausa();
			return 5;
			break;
		case 's':
			suspendido();
			return 6;
			break;
		case 'r':
			regresa();
			return 7;
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	remove("suspendidos.txt");
	srand(time(NULL));
	int i = 0;
	int j = 0;
	int test = 0;
	int opc = 0;

	int opcTecla = 0;

	procesoComodin.tme = 1;

	cout << "Procesos Suspendidos" << endl;
	cout << "Ingrese el numero de procesos a generar: ";
	cin >> nProcesos;
	cout << "Ingrese el valor del Quantum: ";
	cin >> quantum;
	quantumInicial = quantum;

	for (i = 0; i < nProcesos; i++)
	{
		addProceso();
	}

	// calculaNumLotes();
	// numNuevos = nProcesos;

	llenaMemoria();

	nProcesosEnMemoria = listos.size();

	while (nProcesos != 0)
	{
		while (nProcesosEnMemoria != 0)
		{
			error = false;
			bloqueado = false;

			if (listos.size() > 0)
			{
				procesoEnEjecucion = listos.front();
				if (procesoEnEjecucion.TiempoRespuesta == -1)
				{
					procesoEnEjecucion.TiempoRespuesta = tiempoGeneral - procesoEnEjecucion.TiempoLlegada;
				}
				listos.pop_front();
			}
			else
			{
				procesoEnEjecucion = procesoComodin;
			}

			tiempoRestante = procesoEnEjecucion.tme - procesoEnEjecucion.transcurrido;
			tiempoTranscurrido = procesoEnEjecucion.transcurrido;

			if (tiempoRestante < quantumInicial)
			{
				quantum = tiempoRestante;
			}
			else
			{
				quantum = quantumInicial;
			}

			while (quantum != 0) // hasta que el quantum termine o se interrumpa
			{
				printInfoNuevos();
				printSuspendidos();
				printSigNuevo();
				printListos();
				printTerminados();
				printBloqueados();
				printProcesoEnEjecucion();
				printTiempos();
				memoria.printMemoria();

				cont = 0;

				opcTecla = checkTecla(procesoEnEjecucion);

				if (opcTecla == 1 || opcTecla == 2) // si la tecla es I o E
				{
					break;
				}

				if (bloqueados.size() > 0) // si hay procesos bloqueados
				{
					list<Proceso>::iterator it = bloqueados.begin();
					while (it != bloqueados.end())
					{
						if (it->TiempoEnEspera < 8)
						{
							it->TiempoEnEspera += 1;
							it++;
						}
						else
						{
							it->TiempoEnEspera = 0;
							listos.push_back(*it);
							it++;
							bloqueados.pop_front();
						}
					}
				}

				tiempoTranscurrido++;
				tiempoRestante--;
				tiempoGeneral++;
				quantum--;
				quantumImprime++;

				procesoEnEjecucion.transcurrido += 1; ///

				Sleep(1000);
				system("cls");
			}
			if (!error && (tiempoRestante == 0))
			{
				if (procesoEnEjecucion.id != -1)
				{
					procesoEnEjecucion.TiempoFinalizacion = tiempoGeneral;
					procesoEnEjecucion.TiempoRetorno = procesoEnEjecucion.TiempoFinalizacion - procesoEnEjecucion.TiempoLlegada;
					procesoEnEjecucion.TiempoServicio = procesoEnEjecucion.transcurrido;
					procesoEnEjecucion.TiempoEspera = procesoEnEjecucion.TiempoRetorno - procesoEnEjecucion.TiempoServicio;

					tiempoTranscurrido = 0;
					procesoEnEjecucion.resultado = resuelveOperacion(procesoEnEjecucion);
					terminados.push_back(procesoEnEjecucion);
					memoria.liberarMemoria(procesoEnEjecucion.id);
					nProcesos--;
					nProcesosEnMemoria--;
				}
				bool mocha = false;
				bool otro = false;
				int pags;
				do
				{
					if (nuevos.size() > 0) // meter nuevo proceso a listos
					{
						//

						mocha = false;
						i = 0;
						j = 0;

						pags = nuevos.front().tamanio / 5;
						int residuo = nuevos.front().tamanio % 5;

						if (residuo > 0)
						{
							pags++;
							mocha = true;
						}

						if (pags <= memoria.espaciosLibres())
						{
							for (i = 0; i < pags; i++)
							{
								if (i == pags - 1)
								{
									if (mocha)
									{
										for (j = 0; j < sizeof(memoria.arr); j++)
										{
											if (memoria.arr[j].espacio == 0)
											{
												memoria.arr[j].espacio = residuo;
												memoria.arr[j].estado = to_string(nuevos.front().id);
												break;
											}
										}
									}
									else
									{
										for (j = 0; j < sizeof(memoria.arr); j++)
										{
											if (memoria.arr[j].espacio == 0)
											{
												memoria.arr[j].espacio = 5;
												memoria.arr[j].estado = to_string(nuevos.front().id);
												break;
											}
										}
									}
								}
								else
								{
									for (j = 0; j < sizeof(memoria.arr); j++)
									{
										if (memoria.arr[j].espacio == 0)
										{
											memoria.arr[j].espacio = 5;
											memoria.arr[j].estado = to_string(nuevos.front().id);
											break;
										}
									}
								}
							}
							nuevos.front().TiempoLlegada = tiempoGeneral;
							listos.push_back(nuevos.front());
							nuevos.pop_front();
							nProcesosEnMemoria++;
							otro = true;
						}
						else
						{
							otro = false;
						}
					}
					else
					{
						otro = false;
					}
					// cout << "a " << endl;
				} while (otro);
				// system("pause");
			}
			else if (!error && (tiempoRestante != 0))
			{
				if (!bloqueado)
				{
					listos.push_back(procesoEnEjecucion);
				}
			}
			quantumImprime = 0;
		}
	}
	system("cls");
	cout << "\t\tPROCESO FINALIZADO" << endl;
	cout << endl;
	printInfoNuevos();
	printTablaTerminados();
	printTiempos();
	system("pause");
	return 0;
}
