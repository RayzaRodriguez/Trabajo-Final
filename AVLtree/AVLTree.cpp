// AVLTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "cAvlTree.h"
#include <ctime> 

unsigned t0, t1;
int main()
{
	t0=clock();
	cAvlTrees<int> t(0);
	
	for (int i = 1; i <= 100; i++)
	{
		t.Insert(i);
	}
	
	t1 = clock();
	
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Execution Time: " << time << endl;
	
	//t.Insert(5);
	//t.Insert(10);
	//t.Insert(3);
	//t.Insert(6);
	//t.Insert(7);
	//t.Insert(11);
	//t.Insert(15);		
		//cout << "\nContinuar?: ";
		//cin >> opt;
	//t.Insert(8);
	//t.Insert(3);
	//t.Remove(7);
	//t.Remove(6);
	//t.Remove(9);
	//t.Remove(10);
	//t.imprimir();
    //std::cout << "Hello World!\n";*/
}


