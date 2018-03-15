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
void LinkedList::insert(unsigned int addr, short int t) {
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

unsigned int LinkedList::iterate(short int prediction) {
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

unsigned int LinkedList::iterateBimodalSingle(std::list<short int> &table, unsigned int tableSize) {
	std::list<short int>::iterator it = table.begin();
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

unsigned int LinkedList::iterateBimodalDouble(std::list<short int> &table, unsigned int tableSize) {
	//3 = strongly taken, 2 = weakly taken
	//1 = weakly not taken, 0 = strongly not taken
	std::list<short int>::iterator it = table.begin();
	unsigned int index = 0;

	Node * temp = head;
	unsigned int correct = 0;

	while (temp != NULL) {
		index = temp->address % tableSize;
		it = table.begin();
		std::advance(it, index);

		if (*it == 3) {
			if (temp->type == 1) {
				correct++;
			}else if (temp->type == 0) {
				*it = 2;
			}
		}else if (*it == 2) {
			if (temp->type == 1) {
				correct++;
				*it = 3;
			}else if (temp->type == 0) {
				*it = 1;
			}
		}else if (*it == 1) {
			if (temp->type == 1) {
				*it = 2;
			}else if (temp->type == 0) {
				correct++;
				*it = 0;
			}
		}else if (*it == 0) {
			if (temp->type == 1) {
				*it = 1;
			}else if (temp->type == 0) {
				correct++;
			}
		}
		temp = temp->next;
	}
	return correct;
}

unsigned int LinkedList::iterateGshare(std::list<short int> &table, unsigned int tableSize, short int &gr, int grLen) {
	std::list<short int>::iterator it = table.begin();
	unsigned int index = 0;

	Node * temp = head;
	unsigned int correct = 0;

	while (temp != NULL) {
		index = (temp->address % tableSize) ^ (gr & (short int)(pow(2, grLen) -1));
		it = table.begin();
		std::advance(it, index);

		if (*it == 3) {
			if (temp->type == 1) {
				correct++;
			}else if (temp->type == 0) {
				*it = 2;
			}
		}else if (*it == 2) {
			if (temp->type == 1) {
				correct++;
				*it = 3;
			}else if (temp->type == 0) {
				*it = 1;
			}
		}else if (*it == 1) {
			if (temp->type == 1) {
				*it = 2;
			}else if (temp->type == 0) {
				correct++;
				*it = 0;
			}
		}else if (*it == 0) {
			if (temp->type == 1) {
				*it = 1;
			}else if (temp->type == 0) {
				correct++;
			}
		}
		//shift gr left one to put in the recent outcome
		gr = gr << 1;
		//clear the grLen+1 bit
		gr &= ~(1 << (grLen+1));
		//push new into back
		if (temp->type == 1) {
			gr ^= 1 << 0;
		}


		temp = temp->next;
	}
	return correct;
}