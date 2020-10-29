#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/core.hpp>

class Checkerboard
{
public:
	Checkerboard(std::string windowName);

	void init(std::string windowName);   // ��ʼ������

	void drawCheckerboard();

	void showCheckerboard(std::string windowName);

	// ��������(x, y)����������ָ����ɫ������  row col ��0��ʼ
	void putChesspiece(int row, int col, bool isBlack);

	void putChesspiece(cv::Point circle, bool isBlack);

	void flush();  // �����ָ̻�����ʼ״̬

	// �ж�����������º��Ƿ�����Ӯ��
	bool win(int row, int col);

	// �ж�ָ��λ���Ƿ��Ѿ���������
	bool isOccupied(int row, int col);

	void setIsBlack(bool isBlack);

	// ���Ӻ������ز���
	void updateParams(int row, int col);

	void startGame();

	static void onMouse(int event, int x, int y, int flags, void* param);

	// ����Ծֹ��ܺͻָ��Ծֹ���


	// �ж��Ƿ���Ӯ�ҳ��� ����һЩ����
	void doSomethingAfterWinnerAppear(int row, int col);


private:
	cv::Mat checkerboard_;   // ��ָ������ͼ��
	// ��¼�������������ӵľ���  0��ʾ��λ 1��ʾ���� 2��ʾ����
	std::vector<std::vector<int>> chesspiece_; 

	std::string windowName_;

	bool isBlack_;

	// ��ʤʱ�л����л��߶Խ�������������Ŀ
	const int winNum_ = 5;
	// ����ÿ��ÿ�е���������
	const int allChesspiece_ = 15;
	// �������Ͻǵ�һ�����ӿ��Է��õ�λ��
	const int xStart_ = 25;
	const int yStart_ = 25;
	// �������½�λ��
	const int xEnd_ = 375;
	const int yEnd_ = 375;
	// ���̴�С
	const int rows_ = 400;
	const int cols_ = 400;
	// ���������߿�
	const int thickness_ = 2;
	const int lineType_ = 8;
	// ����ÿһ��߳�
	const int preCellSize_ = 25; 
	// ������ɫ
	const cv::Scalar checkerboardBackgrandColor_ = cv::Scalar(99, 175, 229);;
	// �����Ϸָ�����ɫ
	const cv::Scalar checkerboardLineColor_ = cv::Scalar(39, 105, 154);
	// ���Ӱ뾶
	const int radius_ = 7;
	// ������ɫ
	const cv::Scalar black_ = cv::Scalar(0, 0, 0);
	const cv::Scalar white_ = cv::Scalar(255, 255, 255);
};

