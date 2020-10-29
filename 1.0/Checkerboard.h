#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/core.hpp>

class Checkerboard
{
public:
	Checkerboard(std::string windowName);

	void init(std::string windowName);   // 初始化棋盘

	void drawCheckerboard();

	void showCheckerboard(std::string windowName);

	// 在棋盘上(x, y)处放置棋子指定颜色的棋子  row col 从0开始
	void putChesspiece(int row, int col, bool isBlack);

	void putChesspiece(cv::Point circle, bool isBlack);

	void flush();  // 将棋盘恢复到初始状态

	// 判断这个棋子落下后是否会产生赢家
	bool win(int row, int col);

	// 判断指定位置是否已经存在棋子
	bool isOccupied(int row, int col);

	void setIsBlack(bool isBlack);

	// 落子后更新相关参数
	void updateParams(int row, int col);

	void startGame();

	static void onMouse(int event, int x, int y, int flags, void* param);

	// 保存对局功能和恢复对局功能


	// 判断是否有赢家出现 并做一些处理
	void doSomethingAfterWinnerAppear(int row, int col);


private:
	cv::Mat checkerboard_;   // 五指棋棋盘图像
	// 记录棋盘上已有棋子的矩阵  0表示空位 1表示白子 2表示黑子
	std::vector<std::vector<int>> chesspiece_; 

	std::string windowName_;

	bool isBlack_;

	// 获胜时行或者列或者对角线相连棋子数目
	const int winNum_ = 5;
	// 棋盘每行每列的棋子总数
	const int allChesspiece_ = 15;
	// 棋盘左上角第一个棋子可以放置的位置
	const int xStart_ = 25;
	const int yStart_ = 25;
	// 棋盘右下角位置
	const int xEnd_ = 375;
	const int yEnd_ = 375;
	// 棋盘大小
	const int rows_ = 400;
	const int cols_ = 400;
	// 棋盘线型线宽
	const int thickness_ = 2;
	const int lineType_ = 8;
	// 棋盘每一格边长
	const int preCellSize_ = 25; 
	// 棋盘颜色
	const cv::Scalar checkerboardBackgrandColor_ = cv::Scalar(99, 175, 229);;
	// 棋盘上分割线颜色
	const cv::Scalar checkerboardLineColor_ = cv::Scalar(39, 105, 154);
	// 棋子半径
	const int radius_ = 7;
	// 棋子颜色
	const cv::Scalar black_ = cv::Scalar(0, 0, 0);
	const cv::Scalar white_ = cv::Scalar(255, 255, 255);
};

