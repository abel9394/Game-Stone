// GameStone.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <utility>
#include <functional>
#include <iterator>
#include "AI_MonteCarlo.h"
#include "GameStoneBoard.h"

using namespace std;





int main()

{
	AI_MonteCarlo AI;
	int HumanBet=0;
	int MachineBet=0;
	cout << "�������ܶԾ���:" << endl;
	cin >>AI.GameTotal;
	cout << "���������������" << endl;
	cin >> AI.BetTotal;
	for (int Game = 1; Game<=AI.GameTotal; Game++)
	{
		AI.BetTotal2 = AI.BetTotal - HumanBet;
		AI.BetTotal1 = AI.BetTotal - MachineBet;
		cout << "�� "<<Game<<" �֣�(�㻹ʣ��������"<<AI.BetTotal2<<")"<< endl;
		cout << "�������㱾�ֵĳ������� " << endl;
		cin >> HumanBet;
		if (HumanBet > AI.BetTotal2 || HumanBet < 0)
			cout << "����:���벻����߲�����ȷ�ĳ���" << endl;
		MachineBet = AI.Get_Play(Game);
		cout << "�����ĳ������ǣ�" << MachineBet << endl;
		if (MachineBet > HumanBet)
		{
			cout << "���ź�����������һ��" << endl;
			AI.State.push_back(1);
		}
		else if (MachineBet < HumanBet)
		{
			cout << "Ү���㾡ȻӮ����һ�֣��˲���" << endl;
			AI.State.push_back(-1);
		}
		else
		{
			cout << "������ִ�ƽ��" << endl;
			AI.State.push_back(0);
		}

	}
	if (accumulate(AI.State.begin(), AI.State.end(), 0)>0)
		cout << "������" << endl;
	else if (accumulate(AI.State.begin(), AI.State.end(), 0) < 0)
		cout << "��Ӯ��" << endl;
	else
		cout << "���Ǵ�ƽ��" << endl;
	}