#include "stdafx.h"
#include "AI_MonteCarlo.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <random>
#include <math.h>
#include <time.h>
using namespace std;
#define _1  placeholders::_1
#define _2  placeholders::_2 

AI_MonteCarlo::AI_MonteCarlo()
{
}


AI_MonteCarlo::~AI_MonteCarlo()
{
}
//void AI_MonteCarlo::initiation() 


void AI_MonteCarlo::runsimulation(int GameNum,int max_depth)
{
	unsigned N1, N2;
	vector<pair<unsigned, unsigned>> visited_state;
	random_device seed;
	default_random_engine GameEngine1(seed()), GameEngine2(seed());
	bool expand = true;
	int currentstate = accumulate(State.begin(), State.end(), 0);
	vector<pair<pair<unsigned, unsigned>, int>> GameContainer;

	N1 = BetTotal1- accumulate(GameContainer.begin(), GameContainer.end(), 0, bind(plus<unsigned>(), _1, bind(&pair<unsigned, unsigned>::first, bind(&pair<pair<unsigned, unsigned>, int>::first, _2))));
	N2 = BetTotal2- accumulate(GameContainer.begin(), GameContainer.end(), 0, bind(plus<unsigned>(), _1, bind(&pair<unsigned, unsigned>::second, bind(&pair<pair<unsigned, unsigned>, int>::first, _2))));
	uniform_int_distribution<unsigned> u1(0, N1), u2(0, N2);
	//normal_distribution<> u1(mean,mean/10,0, N1), u2(0, N2);
	unsigned randomNum1 = u1(GameEngine1);
	unsigned randomNum2 = u2(GameEngine2);
	for (int i = 0; i < GameTotal - GameNum; i++) {  //判断是否分支有统计plays和wins
		int Score;
		for (int j = 0; j < BetTotal; j++) {
			if (Plays[make_pair(j, GameNum + i)] == 0)    
				break;
			if (j == BetTotal - 1)                  //如果整个子分支都有统计，取UCB最大值
			{
				auto TotalPlays = accumulate(Plays.begin(), Plays.end(), 0, bind(plus<unsigned>(), _1, bind(&pair<pair<unsigned, unsigned>,unsigned>::second, _2)));
				for (auto iter = Plays.begin(); iter != Plays.end(); iter++)
				{
					UCBChoice[iter->first] = Wins[iter->first] / Plays[iter->first] +C* sqrt(log(TotalPlays) / Plays[iter->first]);
				}
				auto randomiter = max_element(UCBChoice.begin(), UCBChoice.end(), bind(less<double>(), bind(&pair<pair<unsigned, unsigned>, double>::second, _1), bind(&pair<pair<unsigned, unsigned>, double>::second, _2)));
				randomNum1 = (randomiter->first).first;
			}
			

		}
		if (expand&Plays.find(make_pair(randomNum1, GameNum+i)) == Plays.end()) //如果分支没有全部统计，
			                                                                      //则加入统计，否则计入                                                           下一分支
		{
			expand = false;
			Plays[make_pair(randomNum1, GameNum + i)] = 0;
			Wins[make_pair(randomNum1, GameNum + i)] = 0;
			if (i > max_depth)
				max_depth = i;
		

		}

		if (i == GameTotal - 1)
		{
			randomNum1 = BetTotal1 - accumulate(GameContainer.begin(), GameContainer.end(), 0, bind(plus<unsigned>(), _1, bind(&pair<unsigned, unsigned>::first, bind(&pair<pair<unsigned, unsigned>, int>::first, _2))));
			randomNum2 = BetTotal2 - accumulate(GameContainer.begin(), GameContainer.end(), 0, bind(plus<unsigned>(), _1, bind(&pair<unsigned, unsigned>::second, bind(&pair<pair<unsigned, unsigned>, int>::first, _2))));
		}
		if (randomNum1 > randomNum2)
			Score = 1;
		else if (randomNum1 < randomNum2)
			Score = -1;
		else
			Score = 0;

		GameContainer.push_back({ make_pair(randomNum1,randomNum2),Score });
		visited_state.push_back(make_pair(randomNum1, GameNum + i));

	}
	for (auto iter =visited_state.begin(); iter != visited_state.end(); iter++)//将本次模拟计入统计
	{
		if (Plays.find(*iter) == Plays.end())
			continue;
		Plays[*iter] += 1;
		if (accumulate(GameContainer.begin(), GameContainer.end(), 0, bind(plus<unsigned>(), _1, bind(&pair<pair<unsigned, unsigned>,unsigned>::second, _2)))>-accumulate(State.begin(), State.end(), 0)) {
			Wins[*iter] += 1;
		}
	
	}
	visited_state.clear();
	GameContainer.clear();
}

unsigned AI_MonteCarlo::Get_Play(int GameNum) 
{
	int max_depth = 0;
	double winrate;
	map<double, unsigned> Winratemap;
	auto begin = time(0);
	while (auto duration = time(0) - begin > 20) 
	{
		runsimulation(GameNum,max_depth);
	}
	for (auto iter = Plays.begin(); iter != Plays.end(); iter++)
	{
		if (iter->first.second == GameNum)
		{
			winrate = Wins[make_pair(iter->first.first, iter->first.second)] / iter->second;
			Winratemap[winrate] = iter->first.first;
		}
	}
	auto winrate_iter = Winratemap.rbegin();
	cout << "the depth is " << max_depth << endl;
	return winrate_iter->second;
	
}
