#pragma once

#include "Checkerboard.h"
#include <memory>

class Gobang
{
public:
	// Ĭ�Ϻ������� ���������������
	Gobang(bool isBlack = true);
	~Gobang();
	// ��ʼ����Ϸ����
	void init(bool isBlack);
    // ����һ������  �����õ�
	void putChesspiece(int row, int col);
	// �ж��Ƿ���Ӯ�Ҳ���
	//bool haveWiner(int row, int col);
	// ��Ϸ��ʼ
	void startGame();

	

	//static void onMouse(int event, int x, int y, int flags, void* param);

private:
	bool isBlack_;   // ��ʱ��������ĺ��ӻ��ǰ���
	//bool isFull_;    // ����������
	//int cntChesspiece;   // �������������ӵ�����
	//const int allChesspiece_ = 375;  // �����ܹ����Է��µ���������

	Checkerboard* checkerboard_;
	const std::string windowName_ = std::string("Gobang");

	//const int preCellSize_ = 25;

	// �������λ��
	//int x_;
	//int y_;
};



