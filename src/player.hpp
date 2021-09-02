#ifndef CONNECT_PLAYER_H
#define CONNECT_PLAYER_H


#include "game.hpp"
#include "position.hpp"
#include <optional>


template <ConnectSize R, ConnectSize C>
class Player
{
protected:
	std::optional<Position> random(Board<R, C>& board)
	{
		ConnectSize blank_count = 0;
		for (ConnectSize y = 0; y < R; ++y)
			for (ConnectSize x = 0; x < C; ++x)
				blank_count += board.get_state(y, x) == State::BLANK;

		if (!blank_count)
			return {};

		ConnectSize random_choice = rand() % blank_count;
		ConnectSize counter = 0;

		for (ConnectSize y = 0; y < R; ++y) {
			for (ConnectSize x = 0; x < C; ++x) {
				if (board.get_state(y, x) == State::BLANK) {
					if (counter == random_choice)
						return Position(y, x);

					counter += 1;
				}
			}
		}

		return {};
	}

	std::optional<Position> attack(Board<R, C>& board)
	{
		return {};
	}

public:
	State state;

	Player(State state)
		: state(state)
	{}

	std::optional<Position> position(Board<R, C>& board, Player<R, C> opponent)
	{
		auto attack_position = attack(board);
		if (attack_position.has_value())
			return attack_position;

		auto defence_position = opponent.attack(board);
		if (defence_position.has_value())
			return defence_position;

		return this->random(board);
	}

	std::optional<Move> move(Board<R, C>& board, Player<R, C> opponent)
	{
		auto position = position(board, opponent);
		if (position.has_value())
			return Move(position.value(), state);

		return {};
	}
};


template <ConnectSize R, ConnectSize C>
class Random : public Player<R, C>
{
public:
	Random(State state)
		: Player<R, C>(state)
	{}

	std::optional<Position> position(Board<R, C>& board, Player<R, C> opponent)
	{
		return this->random(board);
	}
};


#endif // CONNECT_PLAYER_H