#include<iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#define si short int
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
#include "Structs.h"
#include "Proto.h"


int main(){
	srand(time(NULL));

#pragma region firstPlayer

	Game* player1 = new Game;
	si size = 10;
	char** table = new char* [size];
	cleanTable(table, size, true);
	showTable(table, player1->playername, size);
	assignSizeOfShipparts(player1);
	cout << "player name: ";
	cin.getline(player1->playername, 30);
	char sp = 'O';

	showTable(table, player1->playername, size);
	si mouse = 0;

	(choosePLacementType(mouse)) ? randomPlacement(player1,sp,table): selfPlacement(table, player1, size, sp);//2 secim var 1 ve ya 0 qaytardigi ucun


	showTable(table, player1->playername, size);
#pragma endregion
#pragma region GAMEVersusAi
	Game* player2 = new Game;
	char** player2table = new char* [size];
	cleanTable(player2table, size, true);
	assignSizeOfShipparts(player2);
	randomPlacement(player2, sp, player2table);
	showTable(player2table, player2->playername, size);


	char** bigtable = new char* [size];
	cleanTable(bigtable, size, true, size);
	for (si i = 0; i < size; i++){
		for (si j = 0; j < size*2; j++){
			j < size ? bigtable[i][j] = table[i][j] : bigtable[i][j] = player2table[i][j-size];
		}
	}
	//delete table
	for (si i = 0; i < size; i++){
		delete[] table[i];
	}
	delete[] table;
	
	
	int* randcoor = new int[100]{};
	for (size_t i = 0; i < 100; i++)
	{
		randcoor[i] = i;
	}
	si mousex = size+size/2, mousey = size / 2;
	si AIx = 0, AIy = 0, AIz = 0;
	ShowBigTable(bigtable, size, player1, player2, mousex, mousey);
	bool search = true;
	si lenrand = 100;
	while (true){
		playerAttack(mousex, mousey, bigtable, sp, size, player1, player2);
		//shipControl(player2, bigtable, 10);
		AIattack(bigtable, sp, mousex, mousey, size, player1, player2,search,AIx,AIy,AIz,randcoor,lenrand);
		//shipControl(player1, bigtable);
		if (player1->aliveShip <= 0) { cout << player2->playername << " winn"; break; }
		else if (player2->aliveShip <= 0) { cout << player1->playername << " winn"; break; }
	}
	ShowBigTable(bigtable, size, player1, player2, mousex, mousey);
	system("pause");
#pragma endregion

	//{
	//	si mousex = size + size / 2, mousey = size / 2;
	//	si AIx = 0, AIy = 0, AIz = 0;
	//	si AIx2 = 0, AIy2 = 0, AIz2 = 0;
	//	ShowBigTable(bigtable, size, player1, player2, mousex, mousey);
	//	bool search = true;
	//	bool search2 = true;
	//	si len = 100;
	//	while (true) {
	//		AIattack2(bigtable, sp, mousex, mousey, size, player2, player1, search2, AIx2, AIy2, AIz2,randcoor,len);
	//		shipControl(player2, bigtable, 10);
	//		AIattack(bigtable, sp, mousex, mousey, size, player1, player2, search, AIx, AIy, AIz);
	//		shipControl(player1, bigtable);
	//		if (player1->aliveShip <= 0) { cout << player1->playername << " winn"; break; }
	//		else if (player2->aliveShip <= 0) { cout << player2->playername << " winn"; break; }
	//	}
	//}
}
