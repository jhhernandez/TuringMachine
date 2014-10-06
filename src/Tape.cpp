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

const string& Tape::to_string() const
{
	return m_tape;
}

const char Tape::operator[](int index) const
{
	return m_tape.at(index);
}
