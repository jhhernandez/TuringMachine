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
//#include "TransitionTable.h"
#include "State.h"
#include "Tape.h"
#include "Header.h"

#include <fstream>

using namespace std;
using namespace json_spirit;

Machine::Machine(const char* file) : m_wellFormedMachine(false), m_initialState(0),
m_header(new Header)
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
		mArray transitions = sections.find("TransitionGraph")->second.get_array();

		if (buildAlphabets(alphabet)) {
			cout << "Alphabet successfully built." << endl;
			
			if (buildStateSet(states)) {
				cout << "States successfully built." << endl;
				if (buildTransitionTable(transitions)) {
						cout << "Transition table successfully built." << endl;
						m_wellFormedMachine = true;
					}
			} else {
				return;
			}
		} else {
			return;
		}
	} catch (Error_position err) {
		cout << err.reason_ << endl;
	}
}

Machine::~Machine()
{
	delete m_tape;
	delete m_header;
}

bool Machine::buildAlphabets(const mArray& alphabet)
{
    for (mValue val : alphabet) {
        switch (val.type()) {
        case Value_type::str_type:
			m_sigmaAlphabet.insert(val.get_str()[0]);
			m_gammaAlphabet.insert(val.get_str()[0]);
            break;
		case Value_type::int_type:
			m_gammaAlphabet.insert(static_cast<signed char>(val.get_int()));
            break;
        default:
            return false;
            break;
        }
    }
    return true;
}

bool Machine::buildStateSet(const mArray& states)
{
	mObject stateObj;
	int id;
	State* newState;
	
	for (mValue state : states) {
		stateObj = state.get_obj();
		id = stateObj.find("id")->second.get_int();
		newState = new State(id);
		
		m_states.insert(*newState);
		
		if (stateObj.find("initial") != stateObj.end()) {
			m_initialState = *newState;
		}
		if (stateObj.find("final") != stateObj.end()) {
			m_finalStates.insert(*newState);
		}
		
		delete newState;
	}
	m_transitionTable.resize(m_states.size());

	return true;
}

bool Machine::buildTransitionTable(const mArray& graph)
{
	mObject graphObj;
	signed char from;
	signed char to;
	signed char move;
	State* compareState;
	State* toState;
	Header::Direction dir;

	for (mValue node : graph) {
		graphObj = node.get_obj();
		compareState = new State(graphObj.find("State")->second.get_int());

		if (m_states.find(*compareState) != m_states.end()) { // state exists
			mArray transitions = graphObj.find("Transitions")->second.get_array();
			for (mValue transition : transitions) {
				mObject transitionObj = transition.get_obj();
				switch(transitionObj.find("read")->second.type()) {
					case Value_type::str_type:
						from = transitionObj.find("read")->second.get_str()[0];
						break;
					case Value_type::int_type:
						from = static_cast<signed char>(transitionObj.find("read")->second.get_int());
						break;
					default:
						return false;
						break;
				}

				switch(transitionObj.find("write")->second.type()) {
					case Value_type::str_type:
						to = transitionObj.find("write")->second.get_str()[0];
						break;
					case Value_type::int_type:
						to = static_cast<signed char>(transitionObj.find("write")->second.get_int());
						break;
					default:
						return false;
						break;
				}

				move = transitionObj.find("move")->second.get_str()[0];
 
				if (move == 'R') {
					dir = Header::Direction::RIGHT;
				} else if (move == 'L') {
					dir = Header::Direction::LEFT;
				} else {
					dir = Header::Direction::HALT;
				}

				if (transitionObj.find("toState") != transitionObj.end()) {
					toState = new State(transitionObj.find("toState")->second.get_int());
				} else {
					toState = new State(-1);
				}

				transition_table_cell_t cell(*compareState, from);
				transition_table_content_t content(to, dir, *toState);
				// m_transitionTable->addContentToCell(content, cell);
				m_transitionTable[compareState->id()].insert(
					pair<signed char, transition_table_content_t>(from, content));
			}
		} else {
			return false;
		}
	}
	return true;
}

bool Machine::run(const char* str, bool stepping)
{
	m_tape = new Tape(str);
	m_header->attachTape(*m_tape);
	
	bool success = false;
	signed char currentSymbol;
	signed char writeSymbol;
	Header::Direction nextMove;
	State nextState;
	State currentState = m_initialState;
	
	if (!m_wellFormedMachine) {
		cout << "The machine is not well formed and cannot be run." << endl;
		return false;
	}

	while (1) {
		currentSymbol = m_header->read();
		cout << "Read symbol " << currentSymbol << " in tape " << m_tape->stdString() << ". ";
		cout << "Looking up transition in (" << currentState.name() << ", " <<
			currentSymbol << "). ";

		if (m_transitionTable[currentState.id()].find(currentSymbol) == m_transitionTable[currentState.id()].end()) {
			if (m_finalStates.find(currentState) != m_finalStates.end()) {
				cout << "Reached a final state." << endl;
				success = true;
			} else {
				cout << "Reached a dead state." << endl;
			}
			break;
		}
		writeSymbol = get<0>(m_transitionTable[currentState.id()][currentSymbol]);
		nextMove = get<1>(m_transitionTable[currentState.id()][currentSymbol]);
		nextState = get<2>(m_transitionTable[currentState.id()][currentSymbol]);
		
		cout << "Writing " << writeSymbol << ", Moving " <<
			(nextMove == Header::Direction::LEFT?'L':'R');
		if (nextState.id() != -1) { cout << ", changing state to " << nextState.name(); }

		m_header->write(writeSymbol);
		m_header->move(nextMove);
		if (nextState.id() != -1) {
			currentState = nextState;
		}
		cout << endl;

		if (stepping) {
			cin.get();
		}
	}

    return success;
}

bool Machine::buildMultitapeTransitionTable(const mArray& graph)
{
	return true;
}
