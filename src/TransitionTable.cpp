/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  Juan Hernández Hernández <janukato@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "TransitionTable.h"

#include <iostream>

using namespace std;

TransitionTable::TransitionTable()
{
	
}

TransitionTable::~TransitionTable()
{

}

void TransitionTable::addContentToCell(const transition_table_content_t& content, const transition_table_cell_t& cell)
{
	cout << "transition " << get<0>(cell).name() << "," << get<1>(cell);
	cout << ": " << get<0>(content) << "," << get<1>(content) << ";" << get<2>(content).name() << endl;
	tuple<signed char, transition_table_content_t> caca(get<1>(cell), content);
	this->at(get<0>(cell).id()).push_back(caca);
}

const transition_table_content_t& TransitionTable::getCellContent(const transition_table_cell_t& cell)
{
}

const transition_table_content_t& TransitionTable::getCellContent(const State& state, char from)
{
	return getCellContent(transition_table_cell_t(state, from));
}

const char TransitionTable::getCellSymbol(const transition_table_cell_t& cell)
{

}

const char TransitionTable::getCellSymbol(const State& state, char from)
{
	return getCellSymbol(transition_table_cell_t(state, from));
}

const Header::Direction TransitionTable::getCellDirection(const transition_table_cell_t& cell)
{
}

const Header::Direction TransitionTable::getCellDirection(const State& state, char from)
{
	return getCellDirection(transition_table_cell_t(state, from));
}

const State& TransitionTable::getCellState(const transition_table_cell_t& cell)
{
}

const State& TransitionTable::getCellState(const State& state, char from)
{
	return getCellState(transition_table_cell_t(state, from));
}

void TransitionTable::caca()
{
	cout << this->size();
}
