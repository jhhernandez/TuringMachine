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
	m_table = new std::map<vector<symbol_t>, transition_table_content_t>[m_stateCount];
}

TransitionTable::~TransitionTable()
{
	delete [] m_table;
}

void TransitionTable::addContentToCell(const transition_table_content_t& content, const transition_table_cell_t& cell)
{
	if (get<0>(cell).id() >= 0 && get<0>(cell).id() < m_stateCount) {
		m_table[get<0>(cell).id()].insert(pair<vector<symbol_t>, transition_table_content_t>(get<1>(cell), content));
	}
}

const transition_table_content_t& TransitionTable::getCellContent(const transition_table_cell_t& cell)
{
	return m_table[get<0>(cell).id()][get<1>(cell)];
}

const transition_table_content_t& TransitionTable::getCellContent(const State& state, std::vector<symbol_t> read)
{
	return getCellContent(transition_table_cell_t(state, read));
}

const vector<symbol_t>& TransitionTable::getCellSymbol(const transition_table_cell_t& cell)
{
	return get<0>(m_table[get<0>(cell).id()][get<1>(cell)]);
}

const vector<symbol_t>& TransitionTable::getCellSymbol(const State& state, std::vector<symbol_t> read)
{
	return getCellSymbol(transition_table_cell_t(state, read));
}

const vector<Header::Direction> TransitionTable::getCellDirection(const transition_table_cell_t& cell)
{
	return get<1>(m_table[get<0>(cell).id()][get<1>(cell)]);
}

const vector<Header::Direction> TransitionTable::getCellDirection(const State& state, std::vector<symbol_t> read)
{
	return getCellDirection(transition_table_cell_t(state, read));
}

const State& TransitionTable::getCellState(const transition_table_cell_t& cell)
{
	return get<2>(m_table[get<0>(cell).id()][get<1>(cell)]);
}

const State& TransitionTable::getCellState(const State& state, std::vector<symbol_t> read)
{
	return getCellState(transition_table_cell_t(state, read));
}

bool TransitionTable::existsTransition(const transition_table_cell_t& cell)
{
	if (get<0>(cell).id() >= 0 && get<0>(cell).id() < m_stateCount) {
		return (m_table[get<0>(cell).id()].find(get<1>(cell)) == m_table[get<0>(cell).id()].end());
	}
	return false;
}

bool TransitionTable::existsTransition(const State& state, std::vector<symbol_t> read)
{
	return existsTransition(transition_table_cell_t(state.id(), read));
}

void TransitionTable::printTable()
{
	for (uint i = 0; i < m_stateCount; ++i) {
		cout << "q_" << i << ": ";
		for (auto it : m_table[i]) {
			for (symbol_t c :get<0>(it.second)) {
				cout << c;
			}
			cout << " ";
			for (Header::Direction dir : get<1>(it.second)) {
				cout << (dir == Header::Direction::LEFT?'L':'R');
			}
			cout << " ";
			cout << get<2>(it.second).name() << "\t";
		}
		cout << endl;
	}
}
