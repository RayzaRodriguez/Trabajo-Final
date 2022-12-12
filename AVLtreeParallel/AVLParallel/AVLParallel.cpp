// AVLParallel.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
/*#include "seq_avl.h"
#include<stdio.h>
#include<stdlib.h>
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}*/

#include "seq_avl.h"
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <ctime> 

unsigned t0, t1;

#define N (100)

using namespace std;

int cmp(const void* a, const void* b)
{
    return *(int*)b - *(int*)a;
}

void print_int(const void* i)
{
    //printf("%d ", *(int*)i);
    cout<<*(int*)i;
}

int main() {
    t0 = clock();
    avl_tree* t = avl_new_tree(&cmp);
    int* A = (int*)malloc(N * sizeof(int));
    int i;
    for (i = 0; i < N; i++)
    {
        A[i] = i + 1;
        avl_insert(t, A + i);
        //avl_preorder(t, &print_int);
        //printf("\n");
        //cout << endl;
    }
    /*for (i = 0; i < N; i++)
    {
        avl_remove(t, A + i);
        //avl_preorder(t, &print_int);
        //printf("\n");
    }*/
    avl_free_tree(t);
    free(A);
    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
    return 0;
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
