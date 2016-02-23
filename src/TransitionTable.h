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

#include <vector>
#include <map>
#include <tuple>

#include "Header.h"
#include "State.h"

using transition_table_cell_t = std::tuple<const State, std::vector<symbol_t> >;
using transition_table_content_t = std::tuple<std::vector<symbol_t>, std::vector<Header::Direction>, const State>;

class TransitionTable
{
private:
    std::map<std::vector<symbol_t>, transition_table_content_t>* m_table;
    size_t m_tapeCount;
    size_t m_stateCount;
public:
    TransitionTable(size_t states, size_t tapes = 1);
    ~TransitionTable();

    void addContentToCell(const transition_table_content_t& content, const transition_table_cell_t& cell);

    const transition_table_content_t& getCellContent(const transition_table_cell_t& cell);
    const transition_table_content_t& getCellContent(const State& state, std::vector<symbol_t> read);

    const std::vector<symbol_t>& getCellSymbol(const transition_table_cell_t& cell);
    const std::vector<symbol_t>& getCellSymbol(const State& state, std::vector<symbol_t> read);
    const std::vector<Header::Direction> getCellDirection(const transition_table_cell_t& cell);
    const std::vector<Header::Direction> getCellDirection(const State& state, std::vector<symbol_t> read);
    const State& getCellState(const transition_table_cell_t& cell);
    const State& getCellState(const State& state, std::vector<symbol_t> read);
    bool existsTransition(const transition_table_cell_t& cell);
    bool existsTransition(const State& state, std::vector<symbol_t> read);
    void printTable();

    size_t tapes() const { return m_tapeCount; }
    size_t size() const { return m_stateCount; }
};

#endif // TRANSITIONTABLE_H
