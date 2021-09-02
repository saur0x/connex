#ifndef CONNECT_MCTS_H
#define CONNECT_MCTS_H


#include "player.hpp"


template <ConnectSize R, ConnectSize C>
class MCTS : public Player<R, C>
{

	
public:
	std::optional<Position> position(Board<R, C>& board, Player<R, C> opponent)
	{

	}
};


#endif // CONNECT_MCTS_H