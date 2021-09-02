#ifndef CONNECT_POSITION_H
#define CONNECT_POSITION_H


#include "game.hpp"
#include <iostream>


using ConnectSize = std::uint16_t;


struct Position
{
	ConnectSize row, column;	

	Position(ConnectSize row, ConnectSize column)
		: row(row), column(column)
	{}

	friend std::ostream& operator << (std::ostream& os, const Position& self);
};


std::ostream& operator << (std::ostream& os, const Position& self)
{
	os << "Position { " << self.row << ", " << self.column << " }" << std::endl;
	return os;
}


#endif // CONNECT_POSITION_H