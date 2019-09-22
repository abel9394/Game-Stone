#pragma once
#include "GameStoneBoard.h"
#include <map>
#include <vector>
#define C 1.4
class AI_MonteCarlo :
	public GameStoneBoard
{
public:
	AI_MonteCarlo();
	~AI_MonteCarlo();
	void runsimulation(int,int);
	//void initiation();
	unsigned Get_Play(int);
	std::vector<int> State;
private:
	std::map<std::pair<unsigned,unsigned>, unsigned> Wins;
	std::map<std::pair<unsigned, unsigned>, unsigned> Plays;
	std::map<std::pair<unsigned, unsigned>, double> UCBChoice;
	
	
	
};

