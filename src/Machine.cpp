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

Machine::Machine(const char* file) : m_wellFormedMachine(false), m_initialState(0)
{
    ifstream ifs(file);
    mValue root;
    mObject rootObj;

    try {
		read(ifs, root);
		rootObj = root.get_obj();
		mValue type;

		mObject sections = rootObj.find("TuringMachine")->second.get_obj();
		mArray alphabet = sections.find("Alphabet")->second.get_array();
		mArray states = sections.find("StateList")->second.get_array();
		mArray transitions = sections.find("TransitionGraph")->second.get_array();
		if (sections.find("Type") != sections.end()) {
			type = sections.find("Type")->second.get_str();
		}

		if (buildAlphabets(alphabet)) {
			cout << "Alphabet successfully built." << endl;
			
			if (buildStateSet(states)) {
				cout << "States successfully built." << endl;
				if (!type.is_null()) {
					if (type == "multiTape") {
						if (buildMultitapeTransitionTable(transitions)) {
							cout << "Transition table successfully built." << endl;
							m_wellFormedMachine = true;
						}
					}
				} else {
					if (buildTransitionTable(transitions)) {
						cout << "Transition table successfully built." << endl;
						m_wellFormedMachine = true;
					}
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
	for (Tape* it : m_tape) {
		delete it;
	}
	for (Header* it : m_header) {
		delete it;
	}
	delete m_transitionTable;
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
			m_gammaAlphabet.insert(static_cast<symbol_t>(val.get_int()));
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
	m_transitionTable = new TransitionTable(m_states.size());

	return true;
}

bool Machine::buildTransitionTable(const mArray& graph)
{
	mObject graphObj;
	symbol_t read;
	symbol_t write;
	symbol_t move;
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
						read = transitionObj.find("read")->second.get_str()[0];
						break;
					case Value_type::int_type:
						read = static_cast<symbol_t>(transitionObj.find("read")->second.get_int());
						break;
					default:
						return false;
						break;
				}

				switch(transitionObj.find("write")->second.type()) {
					case Value_type::str_type:
						write = transitionObj.find("write")->second.get_str()[0];
						break;
					case Value_type::int_type:
						write = static_cast<symbol_t>(transitionObj.find("write")->second.get_int());
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

				transition_table_cell_t cell(*compareState, vector<symbol_t>{read});
				transition_table_content_t content(vector<symbol_t>{write}, vector<Header::Direction>{dir}, *toState);
				m_transitionTable->addContentToCell(content, cell);

				delete toState;
			}
		} else {
			return false;
		}
		delete compareState;
	}
	return true;
}

bool Machine::buildMultitapeTransitionTable(const mArray& graph)
{
	mObject graphObj;
	vector<symbol_t> read;
	vector<symbol_t> write;
	vector<Header::Direction> dir;
	State* compareState;
	State* toState;
	
	for (mValue node : graph) {
		graphObj = node.get_obj();
		compareState = new State(graphObj.find("State")->second.get_int());
		
		if (m_states.find(*compareState) != m_states.end()) {
			mArray transitions = graphObj.find("Transitions")->second.get_array();

			for (mValue transition : transitions) {
				read.clear();
				write.clear();
				dir.clear();

				mObject transitionObj = transition.get_obj();
				
				mArray readArray = transitionObj.find("read")->second.get_array();
				for (mValue readSymbol : readArray) {
					switch(readSymbol.type()) {
						case Value_type::str_type:
							read.push_back(readSymbol.get_str()[0]);
							break;
						case Value_type::int_type:
							read.push_back(static_cast<symbol_t>(readSymbol.get_int()));
							break;
						default:
							return false;
							break;
					}
				}
				
				mArray writeArray = transitionObj.find("write")->second.get_array();
				for (mValue writeSymbol : writeArray) {
					switch(writeSymbol.type()) {
						case Value_type::str_type:
							write.push_back(writeSymbol.get_str()[0]);
							break;
						case Value_type::int_type:
							write.push_back(static_cast<symbol_t>(writeSymbol.get_int()));
							break;
						default:
							break;
					}
				}
				
				mArray moveArray = transitionObj.find("move")->second.get_array();
				for (mValue moveSymbol : moveArray) {
					if (moveSymbol == "R") {
						dir.push_back(Header::Direction::RIGHT);
					} else if (moveSymbol == "L") {
						dir.push_back(Header::Direction::LEFT);
					} else {
						dir.push_back(Header::Direction::HALT);
					}
				}
				
				if (transitionObj.find("toState") != transitionObj.end()) {
					toState = new State(transitionObj.find("toState")->second.get_int());
				} else {
					toState = new State(-1);
				}
				
				transition_table_cell_t cell(*compareState, read);
				transition_table_content_t content(write, dir, *toState);
				m_transitionTable->addContentToCell(content, cell);

				delete toState;
			}
			
		} else {
			return false;
		}
		delete compareState;
	}

	// m_transitionTable->printTable();
	return true;
}

bool Machine::run(const char* str, bool stepping)
{
	Tape* tape = new Tape(str);
	m_tape.push_back(tape);
	Header* header = new Header;
	header->attachTape(*m_tape[0]);
	m_header.push_back(header);
	
	bool success = false;
	symbol_t currentSymbol;
	vector<symbol_t> writeSymbol;
	vector<Header::Direction> nextMove;
	State nextState;
	State currentState = m_initialState;
	
	if (!m_wellFormedMachine) {
		cout << "The machine is not well formed and cannot be run." << endl;
		return false;
	}

	while (1) {
		currentSymbol = m_header[0]->read();
		cout << "Read symbol " << currentSymbol << " in tape " << m_tape[0]->stdString() << ". ";
		cout << "Looking up transition in (" << currentState.name() << ", " <<
			currentSymbol << "). ";

			
		if (m_transitionTable->existsTransition(currentState.id(), vector<symbol_t>{currentSymbol})) {
			if (m_finalStates.find(currentState) != m_finalStates.end()) {
				cout << "Reached a final state." << endl;
				success = true;
			} else {
				cout << "Reached a dead state." << endl;
			}
			break;
		}

		writeSymbol = m_transitionTable->getCellSymbol(currentState.id(), vector<symbol_t>{currentSymbol});
		nextMove = m_transitionTable->getCellDirection(currentState.id(), vector<symbol_t>{currentSymbol});
		nextState = m_transitionTable->getCellState(currentState.id(), vector<symbol_t>{currentSymbol});

		cout << "Writing " << writeSymbol[0] << ", Moving " <<
			(nextMove[0] == Header::Direction::LEFT?'L':'R');
		if (nextState.id() != -1) { cout << ", changing state to " << nextState.name(); }

		m_header[0]->write(writeSymbol[0]);
		m_header[0]->move(nextMove[0]);
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

bool Machine::runMultitape(const char* str, bool stepping)
{
	for (auto tapeStr : multiTapeStrings(str)) {
		Tape* newTape = new Tape(tapeStr);
		Header* newHeader = new Header;
		newHeader->attachTape(*newTape);
		m_tape.push_back(newTape);
		m_header.push_back(newHeader);
	}

	bool success = false;
	vector<symbol_t> currentSymbol;
	vector<symbol_t> writeSymbol;
	vector<Header::Direction> nextMove;
	State nextState;
	State currentState = m_initialState;
	
	if (!m_wellFormedMachine) {
		cout << "The machine is not well formed and cannot be run." << endl;
		return false;
	}
	
	while (1) {
		currentSymbol.clear();
		for (Header* header : m_header) {
			currentSymbol.push_back(header->read());
		}
		cout << "Read symbols ";
		for (symbol_t sym : currentSymbol)
			cout << sym;
		cout << " in tapes ";
		for (Tape* tape : m_tape)
			cout << tape->stdString() << ", ";
		cout << ". ";
		cout << "Looking up transition in (" << currentState.name() << ", ";
		for (symbol_t sym : currentSymbol)
			cout << sym;
		cout << "). ";

		if (m_transitionTable->existsTransition(currentState, currentSymbol)) {
			if (m_finalStates.find(currentState) != m_finalStates.end()) {
				cout << "Reached a final state." << endl;
				success = true;
			} else {
				cout << "Reached a dead state." << endl;
			}
			break;
		}
		
		writeSymbol = m_transitionTable->getCellSymbol(currentState.id(), currentSymbol);
		nextMove = m_transitionTable->getCellDirection(currentState.id(), currentSymbol);
		nextState = m_transitionTable->getCellState(currentState.id(), currentSymbol);
		
		cout << "Writing ";
		for (symbol_t sym : writeSymbol)
			cout << sym;
		cout << ", Moving ";
		for (Header::Direction dir : nextMove)
			cout << (dir == Header::Direction::LEFT?'L':'R');
		if (nextState.id() != -1) { cout << ", changing state to " << nextState.name(); }

		for (uint i = 0; i < m_header.size(); ++i) {
			m_header[i]->write(writeSymbol[i]);
			m_header[i]->move(nextMove[i]);
		}

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

const vector< string >& Machine::multiTapeStrings(const string& str)
{
	vector<string> tmp;
	int start = 0;
	int end = str.length();
	
	while ((end = str.find(',', start)) != string::npos) {
		tmp.push_back(str.substr(start, end));
		start = end + 1;
	}
	tmp.push_back(str.substr(start));
	
	return *(new vector<string>(tmp));
}
