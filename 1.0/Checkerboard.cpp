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
	// ��ʼ������
	checkerboard_ = cv::Mat(rows_, cols_, CV_8UC3, checkerboardBackgrandColor_);
	// ���Ӿ��� 15*15
	chesspiece_ = std::vector<std::vector<int>>(15, std::vector<int>(15, 0));
	
	windowName_ = windowName;
	
	// ��������
	drawCheckerboard();
}

void Checkerboard::drawCheckerboard() 
{
	// ������������	
	for (int i = 0; i < allChesspiece_; i++) {
		// ����
		cv::line(checkerboard_, cv::Point(xStart_, yStart_ + i * preCellSize_), cv::Point(xEnd_, yStart_ + i * preCellSize_), checkerboardLineColor_, thickness_, lineType_);
		// ����
		cv::line(checkerboard_, cv::Point(xStart_ + i * preCellSize_, yStart_), cv::Point(xStart_ + i * preCellSize_, yEnd_), checkerboardLineColor_, thickness_, lineType_);
	}
}

void Checkerboard::showCheckerboard(std::string windowName) 
{
	// drawCheckerboard();  // ���ܷ�����
	cv::imshow(windowName, checkerboard_);

	cv::waitKey(5000);   // ���ͼƬ��ʾ���ڵ�δ��Ӧ���� �ȴ���Ϊ�˸�OpenCVʱ�����ͼƬ �ٷ���������ô˵��
}

void Checkerboard::putChesspiece(cv::Point center, bool isBlack)  
{
	cv::circle(checkerboard_, center, radius_, isBlack ? black_ : white_, -1, lineType_);
}

void Checkerboard::putChesspiece(int row, int col, bool isBlack) 
{
	// �ı�chesspiece_�����ֵ
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
	// int nowChesspiece = isBlack ? 2 : 1;  // �����Ѿ����� ��ôchesspiece_�����Ѿ�������
	int cnt = 1;
	int i, j;

	i = row;
	j = col;

	// ����
	// ����
	while (--j >= 0 && chesspiece_[row][j] == chesspiece_[row][col])
		cnt++;
	// ����
	j = col;
	while (++j < allChesspiece_ && chesspiece_[row][j] == chesspiece_[row][col])
		cnt++;
	if (cnt >= winNum_)
		return true;

	// ����
	cnt = 1;
	i = row;
	j = col;
	// ����
	while (--i >= 0 && chesspiece_[i][col] == chesspiece_[row][col])
		cnt++;
	// ����
	i = row;
	while (++i < allChesspiece_ && chesspiece_[i][col] == chesspiece_[row][col])
		cnt++;
	if (cnt >= winNum_)
		return true;

	// ���Խ���
	cnt = 1;
	i = row;
	j = col;
	// ������
	while (--i >= 0 && --j >= 0 && chesspiece_[i][j] == chesspiece_[row][col])
		cnt++;
	// ������
	i = row;
	j = col;
	while (++i < allChesspiece_ && ++j < allChesspiece_ && chesspiece_[i][j] == chesspiece_[row][col])
		cnt++;
	if (cnt >= winNum_)
		return true;

	// ���Խ���
	cnt = 1;
	i = row;
	j = col;
	// ������
	while (--i >= 0 && ++j < allChesspiece_ && chesspiece_[i][j] == chesspiece_[row][col])
		cnt++;
	// ������
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
	// �������Ӿ��� ��������һ��������
	chesspiece_[row][col] = isBlack_ ? 2 : 1;
	isBlack_ = !isBlack_;
}


void Checkerboard::onMouse(int event, int x, int y, int flags, void* param)
{
	int row, col;
	// ����¼����
	// https://blog.csdn.net/qq_29540745/article/details/52562101
	// https://docs.opencv.org/4.2.0/d7/dfc/group__highgui.html#ga927593befdddc7e7013602bca9b079b0
	if (event == cv::EVENT_LBUTTONDBLCLK) {  // ˫������������
		// ������������ÿ�����񽻵���Χ5�����ص��λ�õ����Ч

		//x_ = x;
		//y_ = y;
		row = (y + 5) / 25;
		col = (x + 5) / 25;

		Checkerboard* cb = (Checkerboard*)param;

		std::cout << "Push: " << row - 1 << " " << col - 1  << " " << x << " " << y << std::endl;

		// ˫��λ�ô�����Ч���� �� �ô�֮ǰû������
		if (x <= col * 25 + 5 && x >= col * 25 - 5 && y <= row * 25 + 5 && y >= row * 25 - 5 && !cb->isOccupied(row - 1, col - 1)) {
			cb->putChesspiece(row - 1, col - 1, cb->isBlack_);						

			cb->updateParams(row - 1, col - 1);
			// �ж��Ƿ����Ӯ�� ����һЩ����
			cb->doSomethingAfterWinnerAppear(row - 1, col - 1);

			cb->showCheckerboard(cb->windowName_);
		}
	}
}

void Checkerboard::doSomethingAfterWinnerAppear(int row, int col)
{
	if (!win(row, col))
		return;

	// isBlack_�Ѿ���ת��
	std::cout << "Winner is " << (isBlack_ ? "White" : "Black") << std::endl;


}

void Checkerboard::startGame()
{
	showCheckerboard(windowName_);
	cv::setMouseCallback(windowName_, onMouse, this);
	cv::waitKey(0);
}
