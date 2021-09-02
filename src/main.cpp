#include <iostream>
#include <string>
#include <optional>
#include <cstdlib>
#include <ctime>

#include "game.hpp"
#include "player.hpp"


int main(int argc, char **argv)
{
	std::srand(std::time(NULL));

	constexpr ConnectSize ROWS = 8;
	constexpr ConnectSize COLUMNS = 8;

	Board<ROWS, COLUMNS> board;
	board.show();

	Player<ROWS, COLUMNS> player(State::CROSS);
	Random<ROWS, COLUMNS> random(State::CIRCLE);

	for (int chance, time = 0; time < ROWS * COLUMNS; chance = (chance + 1) % 2, ++time) {
		if (chance & 1) {
			auto position = random.position(board, random);
			if (position.has_value())
				board.set_state(position.value(), random.state);
		}
		else {
			auto position = player.position(board, random);
			if (position.has_value())
				board.set_state(position.value(), player.state);
		}

		board.show();
	}
}