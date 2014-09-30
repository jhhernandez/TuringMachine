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

class Tape;
class Header;
class State;

class Machine
{
public:
    Machine();
    virtual ~Machine();

private:
	std::set<State*> m_states; //!< Set of the states of the machine
	std::set<char> m_sigmaAlphabet; //!< Alphabet set
	std::set<char> m_gammaAlphabet; //!< Alphabet set plus blank character
	static const char m_blankChar = -1; //!< Blank character
	std::map<std::tuple<State*, char>, std::map<State*, char> > m_transitionTable;
	
	Tape* m_tape;
	Header* m_header;
	
	Machine(const Machine& other);
	Machine& operator=(const Machine& other);
};

#endif // MACHINE_H
