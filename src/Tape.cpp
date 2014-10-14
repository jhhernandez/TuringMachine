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

#include "Tape.h"
#include <iostream>

using namespace std;

Tape::Tape(const string& str)
{
	signed char blank = static_cast<signed char>(-1);
	string tmp;
	tmp += blank;
	tmp += blank;
	tmp += str;
	tmp += blank;
	tmp += blank;
	m_tape = tmp;
}

Tape::~Tape()
{

}

Tape& Tape::operator=(const Tape& other)
{

}

const string& Tape::stdString() const
{
	return m_tape;
}

char& Tape::operator[](size_t npos)
{
	if (npos >= m_tape.length() - 1) {
		m_tape.resize(m_tape.length() + 1, static_cast<signed char>(-1));
	} else if (npos < 1) {
		string tmp;
		tmp.append(1, static_cast<signed char>(-1));
		tmp.append(m_tape);
		m_tape = tmp;
	}
	return m_tape[npos];
}
