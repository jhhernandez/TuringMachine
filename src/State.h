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

#include <string>

class State
{
private:
	int32_t m_id;
	std::string m_name;
public:
	State();
    State(int id);
	State(const State& other);
	State& operator=(const State& other);
	~State();
	
	inline int id() const { return m_id; }
	inline std::string name() const { return m_name; }

    bool operator==(const State& other) const;
	bool operator<(const State& other) const;
};

#endif // STATE_H
