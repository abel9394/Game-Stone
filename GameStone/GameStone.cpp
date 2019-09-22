// GameStone.cpp : 定义控制台应用程序的入口点。
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
	cout << "请输入总对局数:" << endl;
	cin >>AI.GameTotal;
	cout << "请输入筹码总数：" << endl;
	cin >> AI.BetTotal;
	for (int Game = 1; Game<=AI.GameTotal; Game++)
	{
		AI.BetTotal2 = AI.BetTotal - HumanBet;
		AI.BetTotal1 = AI.BetTotal - MachineBet;
		cout << "第 "<<Game<<" 局：(你还剩筹码数是"<<AI.BetTotal2<<")"<< endl;
		cout << "请输入你本局的筹码数： " << endl;
		cin >> HumanBet;
		if (HumanBet > AI.BetTotal2 || HumanBet < 0)
			cout << "错误:筹码不足或者不是正确的筹码" << endl;
		MachineBet = AI.Get_Play(Game);
		cout << "机器的筹码数是：" << MachineBet << endl;
		if (MachineBet > HumanBet)
		{
			cout << "真遗憾，你输了这一局" << endl;
			AI.State.push_back(1);
		}
		else if (MachineBet < HumanBet)
		{
			cout << "耶，你尽然赢了这一局，了不起" << endl;
			AI.State.push_back(-1);
		}
		else
		{
			cout << "你们这局打平了" << endl;
			AI.State.push_back(0);
		}

	}
	if (accumulate(AI.State.begin(), AI.State.end(), 0)>0)
		cout << "你输了" << endl;
	else if (accumulate(AI.State.begin(), AI.State.end(), 0) < 0)
		cout << "你赢了" << endl;
	else
		cout << "你们打平了" << endl;
	}