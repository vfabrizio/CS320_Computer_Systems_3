#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdlib>
#include <list>
#include <string>

class LinkedList {
	private:
		class Node {
			public:
				unsigned int address;
				std::string type;
				Node * next;
				Node(unsigned int addr, std::string t) { address = addr; type = t; next = NULL; }
				Node(unsigned int addr, std::string t, Node *n) {
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
		void insert(unsigned int addr, std::string t);
	    bool empty();
		bool remove(unsigned int &addr);
		unsigned int iterate(std::string prediction);
		unsigned int iterateBimodalSingle(std::list<std::string> &table, unsigned int tableSize);
		unsigned int iterateBimodalDouble(std::list<std::string> &table, unsigned int tableSize);
		unsigned int iterateGshare(std::list<std::string> &table, unsigned int tableSize, short int gr, int grLen);
};

#endif
