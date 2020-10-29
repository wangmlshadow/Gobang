#pragma once

#include "Checkerboard.h"
#include <memory>

class Gobang
{
public:
	// 默认黑子先行 但这可以自行设置
	Gobang(bool isBlack = true);
	~Gobang();
	// 初始化游戏参数
	void init(bool isBlack);
    // 放置一个棋子  测试用的
	void putChesspiece(int row, int col);
	// 判断是否有赢家产生
	//bool haveWiner(int row, int col);
	// 游戏开始
	void startGame();

	

	//static void onMouse(int event, int x, int y, int flags, void* param);

private:
	bool isBlack_;   // 此时正在下棋的黑子还是白子
	//bool isFull_;    // 棋盘下满了
	//int cntChesspiece;   // 棋盘上现有棋子的数量
	//const int allChesspiece_ = 375;  // 棋盘总共可以放下的棋子总数

	Checkerboard* checkerboard_;
	const std::string windowName_ = std::string("Gobang");

	//const int preCellSize_ = 25;

	// 鼠标点击的位置
	//int x_;
	//int y_;
};



