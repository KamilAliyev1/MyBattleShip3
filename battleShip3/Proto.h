#pragma once

void ShowBigTable(char**& table, int size1,Game* player1,Game* player2,si& mousex,si& mousey) {
	system("CLS");
	cout << '\t' << player1->playername << "\t\t\t" << player2->playername << endl;
	cout << (char)201;
	si len = size1 * 2;
	for (si i = 0; i < len - 1; i++)
		cout << char(205);
	cout << (char)187 << "   ";
	cout << (char)201;
	for (si i = 0; i < len - 1; i++)
		cout << char(205);
	cout << (char)187 << endl;

	for (si i = 0; i < size1; i++)
	{
		for (si j = 0; j < len; j++)
		{
			if (j == 0) cout << (char)186;
			if (j == size1) cout << (char)186 << '\t' << (char)186;
			//if (table[i][j] == '+') { SetConsoleTextAttribute(h, 1); }
			//else SetConsoleTextAttribute(h, 7);
			if(i == mousey && j == mousex) { SetConsoleTextAttribute(h, 2); }
			else if(table[i][j]=='H') { SetConsoleTextAttribute(h, 9); }
			else if (table[i][j] == 'X') { SetConsoleTextAttribute(h, 4); }
			else if (table[i][j] == (char)232) { SetConsoleTextAttribute(h, 6); }
			if (table[i][j] != 'X' && table[i][j] != 'H' && table[i][j] != (char)232 && i == mousey && j == mousex) cout << '+';
			else if(j<size1 || table[i][j]=='X' || table[i][j] == 'H' || table[i][j] == (char)232)cout << table[i][j];
			else cout << ' ';
			SetConsoleTextAttribute(h, 7);
			if (j != size1 - 1 && j != len - 1) cout << ' ';
			if (j == len - 1) cout << (char)186;
		}
		cout << endl;
	}
	cout << (char)200;
	for (si i = 0; i < len - 1; i++)
		cout << char(205);
	cout << (char)188 << "   ";
	cout << (char)200;
	for (si i = 0; i < len - 1; i++)
		cout << char(205);
	cout << (char)188 << endl;
	cout << '\t' << player1->aliveShip << "\t\t\t" << player2->aliveShip << endl;
	cout << endl;
}


void cleanTable(char** table,si size = 10,bool check = false,si size2 = 0) {
	si len = size + size2;
	for (si i = 0; i < size; i++){
		if(check)table[i] = new char[len];
		for (si j = 0; j < len; j++){
			table[i][j] = ' ';
		}
	}
}
void showTable(char** table,char* name, si size = 10) {
	system("CLS");
	cout << '\t' << name << endl;
	cout << (char)201;
	si looprange = size * 2 - 1;
	for (si i = 0; i < looprange; i++)
		cout << char(205);
	cout << (char)187<<endl;
	for (si i = 0; i < size; i++){
		for (si j = 0; j < size; j++){
			if (j == 0) cout << (char)186;
			cout << table[i][j];
			if (j == size - 1) cout << (char)186;
			cout << ' ';
		}
		cout << endl;
	}
	cout << (char)200;
	for (si i = 0; i < looprange; i++)
		cout << char(205);
	cout << (char)188<<endl;
}



bool legalPlacement(Ship ship,si len,char sp,char** table) {
	for (si i = 0; i < len; i++) {
		si y = ship.shipparts[i].y;
		si x = ship.shipparts[i].x;
		if (table[y][x] == sp) return false;
		if (y+1<10 && table[y + 1][x] == sp) return false;
		if (x - 1 >= 0 && table[y][x-1] == sp) return false;
		if (y+1<10 && x+1<10 && table[y + 1][x + 1] == sp) return false;
		if (y+1<10 && x-1>=0 && table[y + 1][x - 1] == sp) return false;
		if (x+1<10 && table[y][x + 1] == sp) return false;
		if (y-1>=0 && x+1<10 && table[y - 1][x + 1] == sp) return false;
		if (y-1>=0 && table[y - 1][x] == sp) return false;
		if (y-1>=0 && x-1>=0 && table[y - 1][x - 1] == sp) return false ;
	}
	return true;
}


void showTable(char** table, char* name,Ship ship,char sp,si size = 10) {
	system("cls");
	si len = ship.size;
	cout << '\t' << name << endl;
	cout << (char)201;
	si looprange = size * 2 - 1;
	for (si i = 0; i < looprange; i++)
		cout << char(205);
	cout << (char)187 << endl;
	//bool checker = true;
	for (si i = 0; i < size; i++) {
		for (si j = 0; j < size; j++) {
			bool checker = true;
			if (j == 0) cout << (char)186;
			for (si s = 0; s < len; s++) {
				if (ship.shipparts[s].y == i && ship.shipparts[s].x == j) {
					bool islegal = legalPlacement(ship, len, sp, table);
					if(islegal)
						SetConsoleTextAttribute(h, 10);
					else
						SetConsoleTextAttribute(h, 4);
					cout << sp;
					SetConsoleTextAttribute(h, 7);
					checker = false;
				}
			}
			if(checker)
				cout << table[i][j];
			if (j == size - 1) cout << (char)186;
			cout << ' ';
		}
		cout << endl;
	}
	cout << (char)200;
	for (si i = 0; i < looprange; i++)
		cout << char(205);
	cout << (char)188 << endl;
}

void addTable(char**& table,Ship ship,char& sp) {
	si len = ship.size;
	for (size_t i = 0; i < len; i++){
		table[ship.shipparts[i].y][ship.shipparts[i].x] = sp;
	}
}
void swapShip(char** table,Ship ship, char& sp,bool& finish) {
	si len = ship.size;
	int x = _getch();
	if (x == 224) {
		int y = _getch();
		//cout << y << endl;
		if (y == 72) {//up
			if (ship.shipparts[len - 1].y - 1 >= 0) {
				for (si i = 0; i < len; i++) {
					ship.shipparts[i].y -= 1;
				}
			}
			else { cout << '\a'; }
		}
		else if (y == 80) {
			if (ship.shipparts[0].y + 1 < 10) {
				for (si i = 0; i < len; i++) {
					ship.shipparts[i].y += 1;
				}
			}
			else { cout << '\a'; }
		}
		else if (y == 75) {
			if (ship.shipparts[0].x - 1 >= 0) {
				for (si i = 0; i < len; i++) {
					ship.shipparts[i].x -= 1;
				}
			}
			else { cout << '\a'; }
		}
		else if (y == 77) {
			if (ship.shipparts[len-1].x + 1 < 10) {
				for (si i = 0; i < len; i++) {
					ship.shipparts[i].x += 1;
				}
			}
			else { cout << '\a'; }
		}
		

	}
	if (x == 'q' || x == 'Q') {
		if(ship.shipparts[len-1].y-len+1>=0)
			for (si i = 1; i < len; i++) {
				ship.shipparts[i].y = ship.shipparts[0].y-i;
				ship.shipparts[i].x = ship.shipparts[0].x;
			}
	}
	if (x == 'e' || x == 'E') {
		if(ship.shipparts[len-1].x+len-1<10)
			for (si i = 1; i < len; i++) {
				ship.shipparts[i].x = ship.shipparts[0].x + i;
				ship.shipparts[i].y = ship.shipparts[0].y;
			}
	}
	if (x == 13) {
		bool check;
		check = legalPlacement(ship, len,sp,table);
		if (check) {
			addTable(table, ship, sp);
			finish = !finish;
		}
	}
}

int chooseShip(si& mouse,si& c,si& b, si& d, si& s,bool& finish) {
	cout << "\nRemaining Ships:"<<endl;
	if (mouse == 0) { SetConsoleTextAttribute(h, 0 | (15 << 4)); }
	cout << "<<Carrier>>" << "  <<" << c << ">>" << endl;
	SetConsoleTextAttribute(h, 7);
	if (mouse == 1) { SetConsoleTextAttribute(h, 0 | (15 << 4)); }
	cout << "<<Battleship>>" << "  <<" << b << ">>" << endl;
	SetConsoleTextAttribute(h, 7);
	if (mouse == 2) { SetConsoleTextAttribute(h, 0 | (15 << 4)); }
	cout << "<<Destroyer>>" << "  <<" << d << ">>" << endl;
	SetConsoleTextAttribute(h, 7);
	if (mouse == 3) { SetConsoleTextAttribute(h, 0 | (15 << 4)); }
	cout << "<<Submarine>>" << "  <<" << s << ">>" << endl;
	SetConsoleTextAttribute(h, 7);


	int x = _getch();
	if(x==224){
		int y = _getch();
		if (y == 72) {
			if (mouse > 0) {
				mouse--;
			}
		}
		else if (y == 80) {
			if (mouse < 3) {
				mouse++;
			}
		}
	}
	if (x == 13) {
		if (mouse == 0 && c > 0) {
			c--;
			finish = !finish;
			return c;
		}
		else if (mouse == 1 && b > 0) {
			b--;
			finish = !finish;
			return b;
		}
		else if (mouse==2 && d>0) {
			d--;
			finish = !finish;
			return d;
		}
		else if (mouse==3 && s>0) {
			s--;
			finish = !finish;
			return s;
		}
	}

}


int choosePLacementType(si& mouse) {
#pragma region GUI
	system("cls");
	if(mouse==0)
		SetConsoleTextAttribute(h, 0 | (15 << 4)); 
	cout<< "\t\t\t\t\t\t SelfPlacement ";
	cout << endl;
	SetConsoleTextAttribute(h, 7);
	if (mouse == 1)
		SetConsoleTextAttribute(h, 0 | (15 << 4));
	cout << "\t\t\t\t\t\tRandomPlacement\n";
	SetConsoleTextAttribute(h, 7);
#pragma endregion
	int x = _getch();
	if (x == 224) {
		int y = _getch();
		if (y == 72 && mouse>0) {//UP
			mouse--;
		}
		else if (y == 80 && mouse<1) {//DOWN
			mouse++;
		}
	}
	if (x == 13) {
		return mouse;
	}
	choosePLacementType(mouse);

}

void selfPlacement(char** table,Game* player1,si size,char sp) {
	si mouse = 0;//shiptype
	si c = 1, b = 2, d = 3, s = 4;
	bool finish = false;
	si chosenship = 0;
	si len = 0;
	while (!(c == b && b == d && c == s && s == 0)) {
		while (!finish) {
			showTable(table, player1->playername, size);
			chosenship = chooseShip(mouse, c, b, d, s, finish);
		}
		len = player1->ships[mouse][chosenship].size;
		for (si i = 0; i < len; i++) {
			player1->ships[mouse][chosenship].shipparts[i].x = i + 4;
			player1->ships[mouse][chosenship].shipparts[i].y = 4;
		}
		while (finish) {
			showTable(table, player1->playername, player1->ships[mouse][chosenship], sp);
			swapShip(table, player1->ships[mouse][chosenship], sp, finish);
		}
		showTable(table, player1->playername, size);
	}
}


void randomShip(Game* player,si f,si j,char sp,char** table) {
	si rotate = rand() % 2;
	si x, y;
	if (rotate) {//paralel
		x = rand() % (10 - player->ships[f][j].size);
		//x-=player->ships[f][j].size;
		y = rand() % 10;
		for (si i = 0; i < player->ships[f][j].size; i++) {
			player->ships[f][j].shipparts[i].x = x + i;
			player->ships[f][j].shipparts[i].y = y;
		}
	}
	else {//horizontal
		x = rand() % 10;
		y = rand() % (player->ships[f][j].size);
		for (si i = 0; i < player->ships[f][j].size; i++) {
			player->ships[f][j].shipparts[i].x = x;
			player->ships[f][j].shipparts[i].y = y + i;
		}
	}
	if (legalPlacement(player->ships[f][j], player->ships[f][j].size, sp, table)) {
		addTable(table, player->ships[f][j], sp);
		return;
	}
	randomShip(player, f, j, sp, table);
}


void randomPlacement(Game* player,char sp,char** table) {
	for (si f = 0; f < 4; f++) {
		for (si j = 0; j < f+1; j++) {
			randomShip(player, f, j,sp,table);
		}
	}
}

void assignSizeOfShipparts(Game* player) {
	for (si i = 0; i < 4; i++) {
		for (si j = 0; j < i + 1; j++) {
			player->ships[i][j].size = 4 - i;
			player->ships[i][j].shipparts = new Shippart[player->ships[i][j].size];
		}
	}
}


void shipControl(Game* player1, char** bigtable, si secondtable = 0) {
	si len;
	bool checkDestroyed;
	for (si i = 0; i < 4; i++) {//butun gemiler
		for (si j = 0; j < i + 1; j++) {//1 gemi novu
			len = player1->ships[i][j].size;
			checkDestroyed = true;
			for (si f = 0; f < len; f++) {//1 gemi
				si x = player1->ships[i][j].shipparts[f].x + secondtable;
				si y = player1->ships[i][j].shipparts[f].y;
				if (bigtable[y][x] != 'H') { checkDestroyed = false; break; }
			}
			if (checkDestroyed) {
				for (si f = 0; f < len; f++) {
					si x = player1->ships[i][j].shipparts[f].x + secondtable;
					si y = player1->ships[i][j].shipparts[f].y;
					if (y + 1 < 10) bigtable[y + 1][x] = 'X';
					if (x - 1 >= 0 + secondtable) bigtable[y][x - 1] = 'X';
					if (y + 1 < 10 && x + 1 < 10 + secondtable) bigtable[y + 1][x + 1] = 'X';
					if (y + 1 < 10 && x - 1 >= 0 + secondtable) bigtable[y + 1][x - 1] = 'X';
					if (x + 1 < 10 + secondtable) bigtable[y][x + 1] = 'X';
					if (y - 1 >= 0 && x + 1 < 10 + secondtable) bigtable[y - 1][x + 1] = 'X';
					if (y - 1 >= 0) bigtable[y - 1][x] = 'X';
					if (y - 1 >= 0 && x - 1 >= 0 + secondtable) bigtable[y - 1][x - 1] = 'X';
				}
				for (si f = 0; f < len; f++) {
					si x = player1->ships[i][j].shipparts[f].x + secondtable;
					si y = player1->ships[i][j].shipparts[f].y;
					bigtable[y][x] = (char)232;
				}
				player1->aliveShip--;
			}
		}
	}
}



void playerAttack(si& mousex,si& mousey,char** bigtable,char sp,si size,Game* player1,Game* player2) {
	ShowBigTable(bigtable, size, player1, player2, mousex, mousey);
	int x = _getch();
	if (x == 224) {
		int y = _getch();
		cout << y << endl;
		if (y == 72 && mousey > 0) {//UP
			mousey--;
		}
		else if (y == 80 && mousey < 9) {//DOWN
			mousey++;
		}
		else if (y == 75 && mousex > 10) {//LEFT
			mousex--;
		}
		else if (y == 77 && mousex < 19) {//RIGHT
			mousex++;
		}
	}
	if (x == 13) {
		if (bigtable[mousey][mousex] == sp) {
			bigtable[mousey][mousex] = 'H';
			shipControl(player2, bigtable, 10);
			if (player2->aliveShip <= 0) { return; }
			return playerAttack(mousex, mousey, bigtable, sp,size,player1,player2);
		}
		else if (bigtable[mousey][mousex] == ' ') {
			bigtable[mousey][mousex] = 'X';
			return;
		}
	}
	return playerAttack(mousex, mousey, bigtable, sp, size, player1, player2);
}


int rnd(int*& coortable, si& len) {
	if (len == 0) return coortable[0];
	si x = rand() % len;
	int* newtable = new int[len - 1]{};
	si inc = 0;
	si temp = coortable[x];
	for (size_t i = 0; i < len - 1; i++) {
		if (i == x) inc++;
		newtable[i] = coortable[i + inc];
	}
	delete[] coortable;
	coortable = newtable;
	len--;
	return temp;
}

/*
void AIattack(char** bigtable, char sp, si& mousex, si& mousey, si size, Game* player1, Game* player2, bool& check, si& x, si& y,si& z,int*& randcoors,si& lenrand) {
	//Sleep(1000);
	if (check) {
		si temp = rnd(randcoors,lenrand);
		x = temp / 10;
		y = temp % 10;
	}
	else{
		if (y > 0 && z == 0)y--;
		else if (y < 9 && z == 1)y++;
		else if (x < 9 && z == 2) x++; 
		else if (x > 0 && z == 3)x--;
	}
	if (z >= 4) { check = true; z = 0; }
	if (bigtable[y][x] == sp) {
		ShowBigTable(bigtable, size, player1, player2, mousex, mousey);
		Sleep(1000);
		bigtable[y][x] = 'H';
		check = false;
		return AIattack(bigtable, sp, mousex, mousey, size, player1, player2, check, x, y, z,randcoors,lenrand);
	}
	else if (bigtable[y][x] == ' ') {
		ShowBigTable(bigtable, size, player1, player2, mousex, mousey);
		Sleep(1000);
		bigtable[y][x] = 'X';
		if (z == 1)y--;
		if (check == false)z++;
		return;
	}
	else if (bigtable[y][x] == 'X') {
		if (check == false)z++;
	}
	else if (y == 0 || y == 9 || x == 9 || x == 0)z++;
	//if (x == 0 && y == 0 || x==9 && y==9 ) check = true;
	return AIattack(bigtable, sp,mousex,mousey,size,player1,player2,check,x,y,z,randcoors, lenrand);

}
*/





/////////////////////



void AIattack2(char**& bigtable, char sp, si& mousex, si& mousey, si size, Game* player1, Game* player2, bool& check, si& x, si& y, si& z,int*& coortable,si& len) {
	//Sleep(1000);
	int mdw=12;
	if (check) {
		//x = rand() % 10+10;
		//y = rand() % 10;
		mdw = rnd(coortable,len);
		if(mdw!=0)x = mdw / 10+10;
		else if (mdw == 0)x = 10;
		y = mdw % 10;
	}
	else {
		if (y > 0 && z == 0)y--;
		else if (y < 9 && z == 1)y++;
		else if (x < 19 && z == 2) x++; 
		else if (x > 10 && z == 3)x--;
	}
	if (z >= 4) { check = true; z = 0; }
	//heh
	if (y == -1)y++;
	if (bigtable[y][x] == sp) {
		ShowBigTable(bigtable, size, player1, player2, mousex, mousey);
		cout << len;
		//Sleep(1000);
		//cout << "vurduuuuuuuuuuuuu" << endl;
		bigtable[y][x] = 'H';
		check = false;
		return AIattack2(bigtable, sp, mousex, mousey, size, player1, player2, check, x, y, z,coortable,len);
	}
	else if (bigtable[y][x] == ' ') {
		ShowBigTable(bigtable, size, player1, player2, mousex, mousey);
		cout << len;
		//Sleep(1000);
		bigtable[y][x] = 'X';
		if (z == 1 && y > 0)y--;
		if (check == false)z++;
		return;
	}
	else if (bigtable[y][x] == 'X') {
		if (check == false)z++;
	}
	else if (y == 0 || y == 9 || x == 19 || x == 10)z++;
	//if (x == 0 && y == 0 || x==9 && y==9 ) check = true;
	return AIattack2(bigtable, sp, mousex, mousey, size, player1, player2, check, x, y, z,coortable,len);

}



void AIattack(char** bigtable, char sp, si& mousex, si& mousey, si size, Game* player1, Game* player2, bool& check, si& x, si& y, si& z, int*& randcoors, si& lenrand) {
	//Sleep(1000);
	if (check) {
		si temp = rnd(randcoors, lenrand);
		x = temp / 10;
		y = temp % 10;
	}
	else {
		if (y > 0 && z == 0)y--;
		else if (y < 9 && z == 1)y++;
		else if (x < 9 && z == 2) x++;
		else if (x > 0 && z == 3)x--;
		else if (x == 0 || x == 9 || y == 0 || y == 9)z++;
	}
	if (z >= 4) { check = true; z = 0; }
	if (bigtable[y][x] == sp) {
		ShowBigTable(bigtable, size, player1, player2, mousex, mousey);
		Sleep(1000);
		bigtable[y][x] = 'H';
		check = false;
		shipControl(player1, bigtable);
		if (player1->aliveShip <= 0) return;
		return AIattack(bigtable, sp, mousex, mousey, size, player1, player2, check, x, y, z, randcoors, lenrand);
	}
	else if (bigtable[y][x] == ' ') {
		ShowBigTable(bigtable, size, player1, player2, mousex, mousey);
		Sleep(1000);
		bigtable[y][x] = 'X';
		if (check == false)z++;
		if (z == 2 && y!=9) y--;
		return;
	}
	else if (bigtable[y][x] == 'X') {
		if (check == false)z++;
	}
	return AIattack(bigtable, sp, mousex, mousey, size, player1, player2, check, x, y, z, randcoors, lenrand);

}