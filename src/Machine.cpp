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

#include "Machine.h"
#include "TransitionTable.h"
#include "State.h"
#include "Tape.h"
#include "Header.h"

#include <fstream>

using namespace std;
using namespace json_spirit;

Machine::Machine(const std::set< State >& states,
                 const std::set< char >& gamma,
                 const std::set< char >& sigma,
                 const TransitionTable& transitions,
                 const State initialState,
                 const std::set< State >& finalStates)
{

}

Machine::Machine(const char* file)
{
    ifstream ifs(file);
    mValue root;
    mObject rootObj;

    try {
        read(ifs, root);
        rootObj = root.get_obj();

        mObject sections = rootObj.find("TuringMachine")->second.get_obj();
        mArray alphabet = sections.find("Alphabet")->second.get_array();
		mArray states = sections.find("StateList")->second.get_array();

        buildAlphabets(alphabet);
		buildStateSet(states);
    } catch (Error_position err) {
        cout << err.reason_ << endl;
    }
}

bool Machine::run(const char* str)
{
    return false;
}

Machine::~Machine()
{

}

bool Machine::buildStateSet(const mArray& states)
{
	for (mValue state : states) {
		
	}
}

bool Machine::buildAlphabets(const mArray& alphabet) // FIXME: usar char, no string
{
    for (mValue c : alphabet) {
        switch (c.type()) {
        case Value_type::str_type:
			m_sigmaAlphabet.insert(c.get_str());
			m_gammaAlphabet.insert(c.get_str());
            break;
        case Value_type::int_type:
			m_gammaAlphabet.insert(c.get_str());
            break;
        default:
            return false;
            break;
        }
    }
    return true;
}
