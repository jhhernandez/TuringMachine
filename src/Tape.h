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

#ifndef TAPE_H
#define TAPE_H

#include <vector>
#include <string>
#include "Header.h"

class Tape
{
private:
    std::string m_tape;

    Tape(const Tape& other);
    Tape& operator=(const Tape& other);

public:
    Tape(const std::string & str);
    virtual ~Tape();
    const std::string& stdString() const;
    char& operator[](size_t npos);
	inline const std::size_t length() const { return m_tape.size(); }
};

#endif // TAPE_H
