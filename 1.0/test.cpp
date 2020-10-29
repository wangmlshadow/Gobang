#include <iostream>
#include <string>
#include "Checkerboard.h"
#include "Gobang.h"

int main(void) {
	std::cout << "Start..." << std::endl;

	Gobang game(false);
	//game.startGame();

	//Checkerboard game;
	//game.startGame("Test");

	std::cout << "End..." << std::endl;

	cv::waitKey(0);
	return 0;
}
