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
#include <json_spirit.h>

class Tape;
class State;
class TransitionTable;

class Machine
{
public:
    Machine(const std::set<State>& states,
			const std::set<char>& gamma,
			const std::set<char>& sigma,
			const TransitionTable& transitions,
			const State initialState,
			const std::set<State>& finalStates
	);
	Machine(const char* file);
    virtual ~Machine();
	bool run(const char* str);

private:
	std::set<State*> m_states; //!< Set of the states of the machine
	std::set<std::string> m_sigmaAlphabet; //!< Alphabet set
	std::set<std::string> m_gammaAlphabet; //!< Alphabet set plus blank character
	static const char m_blankSymbol = -1;
	TransitionTable* m_transitionTable;
	
	Tape* m_tape;
	Header* m_header;
	
	Machine(const Machine& other);
	Machine& operator=(const Machine& other);
	bool buildStateSet(const json_spirit::mArray& states);
	bool buildAlphabets(const json_spirit::mArray& alphabet);
};

#endif // MACHINE_H
