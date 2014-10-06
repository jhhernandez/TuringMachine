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

#ifndef MACHINE_H
#define MACHINE_H

#include <set>
#include <tuple>
#include <map>
#include <vector>
#include "Header.h"
#include "State.h"
#include <json_spirit.h>

class Tape;
class TransitionTable;

typedef std::tuple<const State, signed char> transition_table_cell_t;
typedef std::tuple<signed char, Header::Direction, const State> transition_table_content_t;

class Machine
{
public:
	Machine(const char* file);
    virtual ~Machine();
	bool run(const char* str, bool stepping = false);

private:
	std::set<State> m_states; //!< Set of the states of the machine
	std::set<State> m_finalStates;
	std::set<signed char> m_sigmaAlphabet; //!< Alphabet set
	std::set<signed char> m_gammaAlphabet; //!< Alphabet set plus blank character
	static const char m_blankSymbol = -1;
	// TransitionTable* m_transitionTable;
	std::vector<std::map<signed char, transition_table_content_t> > m_transitionTable;
	
	Tape* m_tape;
	Header* m_header;
	
	State m_initialState;
	bool m_wellFormedMachine;
	
	Machine(const Machine& other);
	Machine& operator=(const Machine& other);
	bool buildStateSet(const json_spirit::mArray& states);
	bool buildAlphabets(const json_spirit::mArray& alphabet);
	bool buildTransitionTable(const json_spirit::mArray& graph);
};

#endif // MACHINE_H
