#include "Checkerboard.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

Checkerboard::Checkerboard(std::string windowName)
{
	//checkerboardBackgrandColor_ = cv::Scalar(99, 175, 229);

	//checkerboardLineColor_ = cv::Scalar(39, 105, 154);

	init(windowName);
	// showCheckerboard("Test");

	//drawCheckerboard();

	//putChesspiece(2, 5, false);
}

void Checkerboard::init(std::string windowName)
{
	// 初始化棋盘
	checkerboard_ = cv::Mat(rows_, cols_, CV_8UC3, checkerboardBackgrandColor_);
	// 棋子矩阵 15*15
	chesspiece_ = std::vector<std::vector<int>>(15, std::vector<int>(15, 0));
	
	windowName_ = windowName;
	
	// 绘制棋盘
	drawCheckerboard();
}

void Checkerboard::drawCheckerboard() 
{
	// 绘制棋盘网格	
	for (int i = 0; i < allChesspiece_; i++) {
		// 横向
		cv::line(checkerboard_, cv::Point(xStart_, yStart_ + i * preCellSize_), cv::Point(xEnd_, yStart_ + i * preCellSize_), checkerboardLineColor_, thickness_, lineType_);
		// 纵向
		cv::line(checkerboard_, cv::Point(xStart_ + i * preCellSize_, yStart_), cv::Point(xStart_ + i * preCellSize_, yEnd_), checkerboardLineColor_, thickness_, lineType_);
	}
}

void Checkerboard::showCheckerboard(std::string windowName) 
{
	// drawCheckerboard();  // 不能放在这
	cv::imshow(windowName, checkerboard_);

	cv::waitKey(5000);   // 解决图片显示窗口的未响应问题 等待是为了给OpenCV时间绘制图片 官方好像是这么说的
}

void Checkerboard::putChesspiece(cv::Point center, bool isBlack)  
{
	cv::circle(checkerboard_, center, radius_, isBlack ? black_ : white_, -1, lineType_);
}

void Checkerboard::putChesspiece(int row, int col, bool isBlack) 
{
	// 改变chesspiece_矩阵的值
	chesspiece_[row][col] = isBlack ? 2 : 1;

	int x = (col + 1) * preCellSize_;
	int y = (row + 1) * preCellSize_;
	putChesspiece(cv::Point(x, y), isBlack);
}

void Checkerboard::flush()
{
	init(windowName_);
}

bool Checkerboard::win(int row, int col)
{
	// int nowChesspiece = isBlack ? 2 : 1;  // 棋子已经落下 那么chesspiece_矩阵已经更新了
	int cnt = 1;
	int i, j;

	i = row;
	j = col;

	// 横向
	// 向左
	while (--j >= 0 && chesspiece_[row][j] == chesspiece_[row][col])
		cnt++;
	// 向右
	j = col;
	while (++j < allChesspiece_ && chesspiece_[row][j] == chesspiece_[row][col])
		cnt++;
	if (cnt >= winNum_)
		return true;

	// 纵向
	cnt = 1;
	i = row;
	j = col;
	// 向上
	while (--i >= 0 && chesspiece_[i][col] == chesspiece_[row][col])
		cnt++;
	// 向下
	i = row;
	while (++i < allChesspiece_ && chesspiece_[i][col] == chesspiece_[row][col])
		cnt++;
	if (cnt >= winNum_)
		return true;

	// 正对角线
	cnt = 1;
	i = row;
	j = col;
	// 向左上
	while (--i >= 0 && --j >= 0 && chesspiece_[i][j] == chesspiece_[row][col])
		cnt++;
	// 向右下
	i = row;
	j = col;
	while (++i < allChesspiece_ && ++j < allChesspiece_ && chesspiece_[i][j] == chesspiece_[row][col])
		cnt++;
	if (cnt >= winNum_)
		return true;

	// 反对角线
	cnt = 1;
	i = row;
	j = col;
	// 向右上
	while (--i >= 0 && ++j < allChesspiece_ && chesspiece_[i][j] == chesspiece_[row][col])
		cnt++;
	// 向左下
	i = row;
	j = col;
	while (++i < allChesspiece_ && --j >= 0 && chesspiece_[i][j] == chesspiece_[row][col])
		cnt++;
	if (cnt >= winNum_)
		return true;

	return false;
}

bool Checkerboard::isOccupied(int row, int col)
{
	return chesspiece_[row][col] != 0;
}

void Checkerboard::setIsBlack(bool isBlack)
{
	isBlack_ = isBlack;
}

void Checkerboard::updateParams(int row, int col)
{
	// 更新棋子矩阵 并设置下一步的棋手
	chesspiece_[row][col] = isBlack_ ? 2 : 1;
	isBlack_ = !isBlack_;
}


void Checkerboard::onMouse(int event, int x, int y, int flags, void* param)
{
	int row, col;
	// 鼠标事件相关
	// https://blog.csdn.net/qq_29540745/article/details/52562101
	// https://docs.opencv.org/4.2.0/d7/dfc/group__highgui.html#ga927593befdddc7e7013602bca9b079b0
	if (event == cv::EVENT_LBUTTONDBLCLK) {  // 双击鼠标左键下棋
		// 设置在棋盘上每个网格交点周围5个像素点的位置点击有效

		//x_ = x;
		//y_ = y;
		row = (y + 5) / 25;
		col = (x + 5) / 25;

		Checkerboard* cb = (Checkerboard*)param;

		std::cout << "Push: " << row - 1 << " " << col - 1  << " " << x << " " << y << std::endl;

		// 双击位置处于有效区域 且 该处之前没有落子
		if (x <= col * 25 + 5 && x >= col * 25 - 5 && y <= row * 25 + 5 && y >= row * 25 - 5 && !cb->isOccupied(row - 1, col - 1)) {
			cb->putChesspiece(row - 1, col - 1, cb->isBlack_);						

			cb->updateParams(row - 1, col - 1);
			// 判断是否产生赢家 并做一些处理
			cb->doSomethingAfterWinnerAppear(row - 1, col - 1);

			cb->showCheckerboard(cb->windowName_);
		}
	}
}

void Checkerboard::doSomethingAfterWinnerAppear(int row, int col)
{
	if (!win(row, col))
		return;

	// isBlack_已经反转过
	std::cout << "Winner is " << (isBlack_ ? "White" : "Black") << std::endl;


}

void Checkerboard::startGame()
{
	showCheckerboard(windowName_);
	cv::setMouseCallback(windowName_, onMouse, this);
	cv::waitKey(0);
}
