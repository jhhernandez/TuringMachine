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

#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <set>

#include "Tape.h"

using symbol_t = signed char;

class Header
{
public:
    enum class Direction {
        LEFT,
        RIGHT,
        HALT
    };

    Header(Tape& tape);
    bool move(Direction dir);
    symbol_t read();
    void write(symbol_t c);

private:
    Tape& m_tape;
    int m_position;
};

#endif // HEADER_H
