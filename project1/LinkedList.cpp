#include <cstdlib>
#include <list>
#include <cmath>
#include "LinkedList.h"


LinkedList::LinkedList() {
	head = NULL;
	current = NULL;
	tail = NULL;
}

LinkedList::LinkedList(const LinkedList &l) {
	head = current = NULL;
	Node * temp = l.head;
	while (temp != NULL) {
		this->insert(temp->address, temp->type);
	}
}

LinkedList::~LinkedList() {
	if (this->empty() == true) return;
	Node *temp = head;
	Node *next = NULL;
	while (temp != NULL) {
		next = temp->next;
		delete temp;
		temp = next;
	}

}

//inserts to the back of the list
void LinkedList::insert(unsigned int addr, std::string t) {
	Node * new_node = new Node(addr, t);
	if (head == NULL) {
		head = new_node;
		tail = new_node;
		return;
	}

	tail->next = new_node;
	tail = tail->next;
}

bool LinkedList::empty() {
	if (head == NULL) {
		return true;
	}
	return false;

}

bool LinkedList::remove(unsigned int &addr) {
	Node *temp = NULL;
	Node *next = NULL;
	Node *prev = NULL;

	if (head->address == addr) {
		temp = head->next;
		delete head;
		head = temp;
		return true;
	}else {
		temp = head;
		while (temp != NULL) {
			if (temp->address == addr) {
				next = temp->next;
				delete temp;
				prev->next = next;
				return true;
			}
			prev = temp;
			temp = temp->next;
		}
	}
	return false;
}

unsigned int LinkedList::iterate(std::string prediction) {
	Node * temp = head;
	unsigned int correct = 0;
	while (temp != NULL) {
		if (temp->type == prediction) {
			correct++;
		}
		temp = temp->next;
	}
	return correct;
}

unsigned int LinkedList::iterateBimodalSingle(std::list<std::string> &table, unsigned int tableSize) {
	std::list<std::string>::iterator it = table.begin();
	unsigned int index = 0;

	Node * temp = head;
	unsigned int correct = 0;
	while (temp != NULL) {
		index = temp->address % tableSize;
		it = table.begin();
		std::advance(it, index);

		if (temp->type == *it) {
			correct++;
		}else {
			*it = temp->type;
		}
		temp = temp->next;
	}
	return correct;
}

unsigned int LinkedList::iterateBimodalDouble(std::list<std::string> &table, unsigned int tableSize) {
	std::list<std::string>::iterator it = table.begin();
	unsigned int index = 0;

	Node * temp = head;
	unsigned int correct = 0;

	while (temp != NULL) {
		index = temp->address % tableSize;
		it = table.begin();
		std::advance(it, index);

		if (*it == "TT") {
			if (temp->type == "T") {
				correct++;
			}else if (temp->type == "NT") {
				*it = "WT";
			}
		}else if (*it == "WT") {
			if (temp->type == "T") {
				correct++;
				*it = "TT";
			}else if (temp->type == "NT") {
				*it = "WN";
			}
		}else if (*it == "WN") {
			if (temp->type == "T") {
				*it = "WT";
			}else if (temp->type == "NT") {
				correct++;
				*it = "NN";
			}
		}else if (*it == "NN") {
			if (temp->type == "T") {
				*it = "WN";
			}else if (temp->type == "NT") {
				correct++;
			}
		}
		temp = temp->next;
	}
	return correct;
}

unsigned int LinkedList::iterateGshare(std::list<std::string> &table, unsigned int tableSize, short int gr, int grLen) {
	std::list<std::string>::iterator it = table.begin();
	unsigned int index = 0;

	Node * temp = head;
	unsigned int correct = 0;

	while (temp != NULL) {
		index = (temp->address % tableSize) ^ (gr & (short int)(pow(2, grLen) -1));
		it = table.begin();
		std::advance(it, index);

		if (*it == "TT") {
			if (temp->type == "T") {
				correct++;
			}else if (temp->type == "NT") {
				*it = "WT";
			}
		}else if (*it == "WT") {
			if (temp->type == "T") {
				correct++;
				*it = "TT";
			}else if (temp->type == "NT") {
				*it = "WN";
			}
		}else if (*it == "WN") {
			if (temp->type == "T") {
				*it = "WT";
			}else if (temp->type == "NT") {
				correct++;
				*it = "NN";
			}
		}else if (*it == "NN") {
			if (temp->type == "T") {
				*it = "WN";
			}else if (temp->type == "NT") {
				correct++;
			}
		}
		//shift gr left one to put in the recent outcome
		gr = gr << 1;
		//clear the grLen+1 bit
		gr &= ~(1 << (grLen+1));
		//push new into back
		if (temp->type == "T") {
			gr ^= 1 << 0;
		}


		temp = temp->next;
	}
	return correct;
}