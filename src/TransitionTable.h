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

#ifndef TRANSITIONTABLE_H
#define TRANSITIONTABLE_H

#include <map>
#include <tuple>

#include "Header.h"
#include "State.h"

class State;

typedef std::tuple<char, Header::Direction, State> transition_table_cell;
typedef std::map<char, transition_table_cell> transition_table_col;

class TransitionTable
{
private:
	const std::map<State, transition_table_col> m_table;
public:
    TransitionTable();
    ~TransitionTable();
};

#endif // TRANSITIONTABLE_H
