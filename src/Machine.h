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
#include <map>
#include <vector>
#include <string>

class Tape;
class Header;

class Machine
{
public:
    Machine();
    virtual ~Machine();
private:
	std::map<int, std::string> m_states;
	std::set<char> m_sigmaAlphabet;
	std::set<char> m_gammaAlphabet;
	char m_blankChar;
	std::map<char, std::map<char, char> > m_transitionTable;
	
	Tape* m_tape;
	Header* m_header;
	
	Machine(const Machine& other);
	Machine& operator=(const Machine& other);
};

#endif // MACHINE_H
