#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdlib>
#include <list>
#include <string>

class LinkedList {
	private:
		class Node {
			public:
				long address;
				std::string type;
				Node * next;
				Node(long addr, std::string t) { address = addr; type = t; next = NULL; }
				Node(long addr, std::string t, Node *n) {
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
		void insert(long addr, std::string t);
	    bool empty();		
		bool remove(long &addr);
		long iterate(std::string prediction);
		long iterateBimodalSingle(std::list<std::string> &table, long tableSize);
		long iterateBimodalDouble(std::list<std::string> &table, long tableSize);
		long iterateGshare(std::list<std::string> &table, long tableSize, short int gr, int grLen);
};

#endif
