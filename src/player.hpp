#ifndef CONNECT_PLAYER_H
#define CONNECT_PLAYER_H


#include "game.hpp"
#include "position.hpp"
#include <optional>


class Player
{
protected:
	std::optional<Position> random(Board& board)
	{
		ConnectSize blank_count = 0;
		for (ConnectSize y = 0; y < board.rows; ++y)
			for (ConnectSize x = 0; x < board.columns; ++x)
				blank_count += board.get_state(y, x) == State::BLANK;

		if (!blank_count)
			return {};

		ConnectSize random_choice = rand() % blank_count;
		ConnectSize counter = 0;

		for (ConnectSize y = 0; y < board.rows; ++y) {
			for (ConnectSize x = 0; x < board.columns; ++x) {
				if (board.get_state(y, x) == State::BLANK) {
					if (counter == random_choice)
						return Position(y, x);

					counter += 1;
				}
			}
		}

		return {};
	}

	std::optional<Position> attack(Board& board)
	{
		return {};
	}

public:
	State state;

	Player(State state)
		: state(state)
	{}

	std::optional<Position> position(Board& board, Player opponent)
	{
		auto attack_position = attack(board);
		if (attack_position.has_value())
			return attack_position;

		auto defence_position = opponent.attack(board);
		if (defence_position.has_value())
			return defence_position;

		return this->random(board);
	}

	std::optional<Move> move(Board& board, Player opponent)
	{
		auto position = this->position(board, opponent);
		if (position.has_value())
			return Move(position.value(), state);

		return {};
	}
};


class Random : public Player
{
public:
	Random(State state)
		: Player(state)
	{}

	std::optional<Position> position(Board& board, Player opponent)
	{
		return this->random(board);
	}
};


#endif // CONNECT_PLAYER_H