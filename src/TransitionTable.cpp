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

TransitionTable::TransitionTable(size_t states, size_t tapes) :
m_tapeCount(tapes),
m_stateCount(states)
{
	m_table = new std::map<signed char, transition_table_content_t>[m_stateCount];
}

TransitionTable::~TransitionTable()
{
	delete m_table;
}

void TransitionTable::addContentToCell(const transition_table_content_t& content, const transition_table_cell_t& cell)
{
	if (get<0>(cell).id() >= 0 && get<0>(cell).id() < m_stateCount) {
		m_table[get<0>(cell).id()].insert(pair<signed char, transition_table_content_t>(get<1>(cell), content));
	}
}

const transition_table_content_t& TransitionTable::getCellContent(const transition_table_cell_t& cell)
{
	return m_table[get<0>(cell).id()][get<1>(cell)];
}

const transition_table_content_t& TransitionTable::getCellContent(const State& state, char from)
{
	return getCellContent(transition_table_cell_t(state, from));
}

const char TransitionTable::getCellSymbol(const transition_table_cell_t& cell)
{
	return get<0>(m_table[get<0>(cell).id()][get<1>(cell)]);
}

const char TransitionTable::getCellSymbol(const State& state, char from)
{
	return getCellSymbol(transition_table_cell_t(state, from));
}

const Header::Direction TransitionTable::getCellDirection(const transition_table_cell_t& cell)
{
	return get<1>(m_table[get<0>(cell).id()][get<1>(cell)]);
}

const Header::Direction TransitionTable::getCellDirection(const State& state, char from)
{
	return getCellDirection(transition_table_cell_t(state, from));
}

const State& TransitionTable::getCellState(const transition_table_cell_t& cell)
{
	return get<2>(m_table[get<0>(cell).id()][get<1>(cell)]);
}

const State& TransitionTable::getCellState(const State& state, char from)
{
	return getCellState(transition_table_cell_t(state, from));
}
