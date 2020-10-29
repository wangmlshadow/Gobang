#include "Gobang.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

Gobang::Gobang(bool isBlack)
{
	init(isBlack);
	//checkerboard_->showCheckerboard(windowName_);
	startGame();
}

Gobang::~Gobang()
{
	delete(checkerboard_);
	checkerboard_ = NULL;
}

void Gobang::init(bool isBlack)
{
	// 黑子先行 默认
	isBlack_ = isBlack;
	//isFull_ = false;
	//cntChesspiece = 0;

	//x_ = -1;
	//y_ = -1;

	// 创建棋盘
	checkerboard_ = new Checkerboard(windowName_);
	checkerboard_->setIsBlack(isBlack_);
}

void Gobang::putChesspiece(int row, int col)
{
	if (checkerboard_->isOccupied(row, col)) {  // 指定位置已经有棋子
		return;
	}

	// 在指定位置放置棋子
	checkerboard_->putChesspiece(row, col, isBlack_);
	checkerboard_->showCheckerboard(windowName_);
	
	// 变换下棋对象 黑白子转换
	isBlack_ = !isBlack_;
}

/*
bool Gobang::haveWiner(int row, int col)
{
	return checkerboard_->win(row, col);
}
*/

void Gobang::startGame()
{
	checkerboard_->startGame();
}







