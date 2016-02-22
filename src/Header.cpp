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

#include "Header.h"
#include "Tape.h"

#include <iostream>

using namespace std;

Header::Header() : m_position(2), m_tape(nullptr)
{

}

Header::~Header()
{

}

void Header::attachTape(Tape& tape)
{
	m_tape = &tape;
}

bool Header::move(Header::Direction dir)
{
	switch(dir) {
            case Direction::RIGHT:
			if (m_position + 1 > m_tape->length()) {
				m_position = 0;
			} else {
				++m_position;
			}
			break;
            case Direction::LEFT:
			if (m_position - 1 < 0) {
				m_position = m_tape->length();
			} else {
				--m_position;
			}
			break;
            case Direction::HALT:
			break;
		default:
			return false;
			break;
	}
	return true;
}

char Header::read()
{
	return (*m_tape)[m_position];
}

void Header::write(symbol_t c)
{
	if (m_position < 1) {
		m_position++;
	}
	(*m_tape)[m_position] = c;
}