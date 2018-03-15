#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdlib>
#include <list>

class LinkedList {
	private:
		class Node {
			public:
				unsigned int address;
				short int type;
				Node * next;
				Node(unsigned int addr, short int t) { address = addr; type = t; next = NULL; }
				Node(unsigned int addr, short int t, Node *n) {
					address = addr;
					type = t;
					next = n;
				}
		};
		Node *head;
		Node *current;
		Node * tail;
			
	public:
		LinkedList();
		LinkedList(const LinkedList &l);
		~LinkedList();
		void insert(unsigned int addr, short int t);
	    bool empty();
		bool remove(unsigned int &addr);
		unsigned int iterate(short int prediction);
		unsigned int iterateBimodalSingle(std::list<short int> &table, unsigned int tableSize);
		unsigned int iterateBimodalDouble(std::list<short int> &table, unsigned int tableSize);
		unsigned int iterateGshare(std::list<short int> &table, unsigned int tableSize, short int &gr, int grLen);
};

#endif
