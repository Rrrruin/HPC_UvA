#include <iostream>
#include "HPCGameLife.h"

using namespace std;

using namespace hpcGameLife;

void defaultStartGame()
{
	//initial game with ramdom alive or dead cells
	hpcGameLife::HPCGameLife game;

	// pinrt map, x is alive, space is dead
	cout << game.GetLifeMap() << endl;

	for (int i = 0; i < 10; i++)
	{
		// Game move to next generation
		game.SkipOneTime();
		cout << game.GetLifeMap() << endl;
	}


	return;
}



// 

int main()
{
	defaultStartGame();
	return 0;
}