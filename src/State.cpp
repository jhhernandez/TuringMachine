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

State::State() : m_id(-1)
{
	m_name = "q_" + to_string(m_id);
}

State::State(int id) : m_id(id)
{
	m_name = "q_" + to_string(m_id);
}

State::State(const State& other) : m_id(other.m_id)
{
	m_name = "q_" + to_string(m_id);
}

State& State::operator=(const State& other)
{
	return *new State(other.id());
}

State::~State()
{

}

bool State::operator==(const State& other) const
{
	return (m_id == other.id());
}

bool State::operator<(const State& other) const
{
	return (id() < other.id());
}
