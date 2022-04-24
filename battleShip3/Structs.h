#pragma once


struct Shippart {
	si x = 0;
	si y = 0;
};
struct Ship{
	si size = 4;
	Shippart* shipparts = nullptr;
};
struct Game{
	char* playername = new char[30]{"AI"};
	si aliveShip = 10;
	si carriersize = 1;
	si battleshipsize = 2;
	si destroyersize = 3;
	si submarinesize = 4;
	Ship** ships = new Ship * [4] {
		new Ship[carriersize],
		new Ship[battleshipsize],
		new Ship[destroyersize],
		new Ship[submarinesize]
	};	
};

