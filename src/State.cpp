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

#include "State.h"

using namespace std;

State::State(int id)
{
	string name = "q_" + to_string(id);
	m_state = make_tuple(id, name);
}

State::State(const State& other)
{
	m_state = other.m_state;
}

State::~State()
{

}

State& State::operator=(const State& other)
{
	return *(new State(get<0>(other.m_state)));
}

bool State::operator==(const State& other) const
{
	return (m_state == other.m_state);
}
