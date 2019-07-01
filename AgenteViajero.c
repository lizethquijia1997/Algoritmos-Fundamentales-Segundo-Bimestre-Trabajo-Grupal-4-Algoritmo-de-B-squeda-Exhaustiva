#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#ifdef _WIN32
	#define LIMPIAR_PANTALLA system("cls");
#else
	#define LIMPIAR_PANTALLA system("clear");
#endif
 
/*Definiciones de estructuras*/
 
typedef struct 
{
	int G[20][20];
	int num_ciudades;
} Datos;
 
/*Prototipos de funciones hechas por mi*/
 
int  RutaOptima              (void);
void PedirCaminos            (Datos *);
void BuscarRutaOptima        (Datos *,int [20][2]);
int  BuscarEnFila            (Datos *,int, int[20][2]);
void GuardarCiudad           (int [20][2], int);
void GuardarValor            (int [20][2], int);
void QuitarCiudadesVisitadas (Datos *, int [20][2], int, bool);
void ImprimirRutaOptima      (int [20][2], int);
int  SumarTrayectorias       (int [20][2], int);
void RepetirPrograma         (void);
void Flush_in                (void); /*se explica su uso al final del codigo*/
 
/*Funcion principal*/
 
int main()
	
{
  printf("\n\n\t\tEjemplo del agente viajero");
	RutaOptima();
	return 0;
}
 
/*Funciones hechas por mi*/
 
int RutaOptima(void)
{
	int ruta[20][2]= {0};
	Datos datos = {0,0};
 
	do
	{
		LIMPIAR_PANTALLA
		printf("\n\n\n\tTeclee el numero de ciudades a visitar (5 - 20): ");
		scanf("%d",&datos.num_ciudades);
		Flush_in();
 
		if (datos.num_ciudades < 5 || datos.num_ciudades > 20)
		{
			printf("\n\n\t\t** El numero de ciudades tiene que estar entre 5 y 20 **");
			getchar();
		}
 
	} while (datos.num_ciudades < 5 || datos.num_ciudades > 20);
 
	PedirCaminos(&datos);
	BuscarRutaOptima(&datos, ruta);
	ImprimirRutaOptima(ruta, datos.num_ciudades);
	RepetirPrograma();
 
	return 0;
}
 
void PedirCaminos(Datos *datos)
{
	int i, j;
 
	LIMPIAR_PANTALLA
	printf("\n\n\tA continuacion escriba la distancia en kilometros de las siguientes\n\ttrayectorias:\n\n");
 
	for (i = 0; i < (datos -> num_ciudades); i++)
	{
	    datos -> G[i][i] = 0;
 
	    for (j = i + 1; j < (datos -> num_ciudades); j++)
	    {	
    		printf("\n\tCiudad %d --> Ciudad %d : ", i+1, j+1);
     		scanf("%d",&datos -> G[i][j]);
     		Flush_in();
 
     		datos -> G[j][i] = datos -> G[i][j];
	    }
    }
}
 
void BuscarRutaOptima(Datos *datos, int r[20][2])
{
	int i, inicio, indice_del_menor;
 
	do
	{
		LIMPIAR_PANTALLA
		printf("\n\n\n\t\tCon cual ciudad desea comenzar su ruta: ");
		scanf("%d", &inicio);
		Flush_in();
 
		if (inicio < 1 || inicio > (datos -> num_ciudades))
		{
			printf("\n\t\t** La ciudad debe estar entre 1 y %d **", datos -> num_ciudades);
			getchar();
		}
	}while(inicio < 1 || inicio > (datos -> num_ciudades));
 
	r[0][0] = inicio;
 
	inicio--;	
 
	for (i = 0; i < (datos -> num_ciudades); i++)
	{			
		if(i == 0)
		{
			indice_del_menor = BuscarEnFila(datos, inicio, r);
			QuitarCiudadesVisitadas(datos, r, indice_del_menor, false);
		}
		else
			{
				if (i == (datos -> num_ciudades) - 2)
				{
					indice_del_menor = BuscarEnFila(datos, indice_del_menor, r);
					QuitarCiudadesVisitadas(datos, r, indice_del_menor, true);
				}
				else
				{
					indice_del_menor = BuscarEnFila(datos, indice_del_menor, r);
					QuitarCiudadesVisitadas(datos, r, indice_del_menor, false);
				}
			}		
	}
}
 
int BuscarEnFila(Datos *datos, int inicio, int r[20][2])
{
	int j, menor = 999999, indice_del_menor;
 
	for (j = 0; j < (datos -> num_ciudades); j++)
	{
		if ( (datos -> G[inicio][j]) != 0 )
		{
			if ( (datos -> G[inicio][j]) < menor )
			{
				menor =	 datos -> G[inicio][j];
				indice_del_menor = j;
			}
		}
	}	
 
	GuardarCiudad(r ,indice_del_menor);
	GuardarValor(r, menor);
 
	return indice_del_menor;
}
 
void GuardarCiudad(int r[20][2] , int indice_del_menor)
{
	int i, num_ciudades_visitadas;
 
	i= 0;
	num_ciudades_visitadas = 0;
 
	while(r[i][0] != 0)
	{
		i++;
		num_ciudades_visitadas++;
	}
 
	r[num_ciudades_visitadas][0] = indice_del_menor + 1;
}
 
void GuardarValor(int r[20][2], int menor)
{
	int i, num_ciudades_visitadas;
 
	i=0;
	num_ciudades_visitadas = 0;
 
	while(r[i][1] != 0)
	{
		i++;
		num_ciudades_visitadas ++;
	}
 
	r[num_ciudades_visitadas][1] = menor;
}
 
void QuitarCiudadesVisitadas(Datos *datos, int r[20][2], int indice_del_menor, bool penultimo)
{
	int i, num_ciudades_visitadas, aux;
 
	i = 0;
	num_ciudades_visitadas = 0;
 
	while(r[i][1] != 0)
	{
		i++;
		num_ciudades_visitadas++;
	}
 
	if (penultimo == true)
	{
		for (i = num_ciudades_visitadas; i >= 1; i--)
		{
			aux = r[i][0];
			aux = aux - 1;
			datos -> G[indice_del_menor][aux] = 0;
		}
	}
	else
	{
		for (i = num_ciudades_visitadas; i >= 0; i--)
		{
			aux = r[i][0];
			aux = aux - 1;
			datos -> G[indice_del_menor][aux] = 0;
		}
	}
}
 
void ImprimirRutaOptima(int ruta[20][2], int n)
{
	int i, total;
 
	total = SumarTrayectorias(ruta, n);
 
	printf("\n\n\tUna ruta optima seria: ");
 
	for (i = 0; i < n + 1; i++)
	{
		if (i == n)
 
			printf(" %d\n", ruta[i][0]);
 
		else
 
			printf(" %d ->", ruta[i][0]);		
	}
 
	printf("\n\n\tTotal de kilometros recorridos:");
 
	for (i = 0; i < n; i++)
	{
		if (i == n-1)
 
			printf(" %d = %d\n\n", ruta[i][1],total);
 
		else	
 
			printf(" %d +", ruta[i][1]);	
	}
 
	getchar();
}
 
int SumarTrayectorias(int r[20][2], int n)
{
	int i, total=0;
 
	for (i = 0; i < n; i++)
 
		total += r[i][1];
 
	return total;
}
 
void RepetirPrograma(void){
	int opcion;
 
	do
	{
		LIMPIAR_PANTALLA
		printf("\n\n\t\tDesea repetir de nuevo el programa\n\n\t 1.Si\n\n\t 2.No");
		printf("\n\n\n\tElegir opcion: ");
		scanf("%d", &opcion);
		Flush_in();
 
		switch(opcion)
			{
				case 1:
					RutaOptima();
				break;
 
				case 2:
					LIMPIAR_PANTALLA
				break;
 
				default:
					printf("\n\n\tOpcion no valida");
					getchar();
				break;
			}
	} while (opcion < 1 || opcion > 2);
}
 
 
/*	La funcion Flush_in sustituye a la funcion fflush(stdin) ya que aquella
 *  no funciona correctamente en linux y lo que hace es limpiar el buffer
 *  del teclado. La funcion Flush_in la uso especificamente para limpiar la 
 *  basura que contiene el buffer del teclado al usar la funciones como scanf 
 */
 
void Flush_in (void)
{
	char caracter;
 
	while((caracter = fgetc(stdin)) != EOF && caracter != '\n');
}
 