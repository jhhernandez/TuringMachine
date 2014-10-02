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

#ifndef STATE_H
#define STATE_H

#include <tuple>
#include <string>

class State
{
private:
	State(const State& other);
	State& operator=(const State& other);
	
	std::tuple<int, std::string> m_state;
public:
    State(int id);
	inline int id() { return std::get<0>(m_state); }
	inline std::string name() { return std::get<1>(m_state); }
    ~State();
    bool operator==(const State& other) const;
};

#endif // STATE_H
