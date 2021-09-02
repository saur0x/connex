#ifndef CONNECT_GAME_H
#define CONNECT_GAME_H


#include "position.hpp"
#include <cstdint>
#include <iostream>
#include <vector>


enum class State : std::uint8_t
{
	BLANK, CIRCLE, CROSS
};

std::ostream& operator << (std::ostream& os, const State& self)
{
	switch (self) {
	default:
	case State::BLANK:
		os << " ";
		break;
	case State::CIRCLE:
		os << "O";
		break;
	case State::CROSS:
		os << "X";
	}

	return os;
}

struct Move
{
	Position position;
	State state;

	Move(Position position, State state)
		: position(position), state(state)
	{}

	Move(ConnectSize row, ConnectSize column, State state)
		: position(row, column), state(state)
	{}
};

struct Board
{
	ConnectSize rows;
	ConnectSize columns;
	std::vector<std::vector<State>> board;

	Board(ConnectSize rows, ConnectSize columns)
		: rows(rows), columns(columns), board(rows, std::vector<State>(columns, State::BLANK))
	{}

	void reset(State state = State::BLANK)
	{
		for (ConnectSize y = 0; y < columns; ++y)
			for (ConnectSize x = 0; x < rows; ++x)
				board[y][x] = state;
	}

	bool is_valid(ConnectSize row, ConnectSize column)
	{
		return row >= 0 && row < rows && column >= 0 && column < columns;
	}

	bool is_valid(Position position)
	{
		return is_valid(position.row, position.column);
	}

	bool is_draw()
	{
		for (ConnectSize y = 0; y < columns; ++y)
			for (ConnectSize x = 0; x < rows; ++x)
				if (board[y][x] == State::BLANK)
					return false;

		return get_winner() == State::BLANK;
	}

	State get_state(ConnectSize row, ConnectSize column)
	{
		if (is_valid(row, column))
			return board[row][column];

		return State::BLANK;
	}

	bool set_state(ConnectSize row, ConnectSize column, State state)
	{
		if (is_valid(row, column)) {
			board[row][column] = state;
			return true;
		}

		return false;
	}

	bool set_state(Position position, State state)
	{
		return set_state(position.row, position.column, state);
	}

	State get_winner()
	{
		return State::BLANK;
	}

	// Temporary
	void show()
	{
		std::cout << "------" << std::endl;

		for (ConnectSize y = 0; y < rows; ++y) {
			for (ConnectSize x = 0; x < columns; ++x) {
				std::cout << board[y][x] << " ";
			}

			std::cout << std::endl;
		}

		std::cout << "------" << std::endl;
	}
};


#endif // CONNECT_GAME_H