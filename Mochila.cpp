#include <iostream> 
using namespace std; 

void Mochila(int n, int Peso[], int Valor[], int PMax){ 
     int *a = new int[PMax]; 
     int *temp = new int[PMax]; 
     int aux; 

     for (int i = 0; i <= PMax; i++){ 
          a[i] = 0; 
          temp[i] = -1; 
     } 

     a[0] = 0; 
     for (int i = 1; i <= PMax; i++) 
          for (int j = 0; j < n; j++) 
               if ((Peso[j] <= i) && (a[i] < a[i - Peso[j]] + Valor[j])){ 
                    a[i] = a[i - Peso[j]] + Valor[j]; 
                    temp[i] = j; 
               } 

     aux = PMax; 
     while ((aux > 0) && (temp[aux] != -1)){ 
          cout << "Se agrego " << temp[aux] + 1 << " ($"<<Valor[temp[aux]] << ", " << Peso[temp[aux]] << "Kg) Espacio disponible: " << aux - Peso[temp[aux]] << endl; 
          aux -= Peso[temp[aux]]; 
     } 
     cout << "Valor total: $" << a[PMax] << endl; 
     delete[] temp; 
     delete[] a; 
} 

int main() { 
     int n, PMax; 
     cout<<"Ingrese la cantidad de objetos: "; 
     cin>>n; 
     int *Peso = new int[n]; 
     int *Valor = new int[n]; 
     for(int i=0; i<n; i++){ 
          cout << "Ingrese el Peso del objeto " << i + 1 << ": "; 
          cin >> Peso[i]; 
          cout << "Ingrese el Valor del objeto " << i + 1 << ": "; 
          cin >> Valor[i]; 
          cout << endl; 
     } 
     cout << "Ingrese el peso maximo de la mochila: "; 
     cin >> PMax; 
     cout << endl << "Calculando..." << endl; 
     Mochila(n, Peso, Valor, PMax); 

     return 0; 
} 