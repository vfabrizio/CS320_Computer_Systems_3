#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include "LinkedList.h"

using namespace std;

ifstream input;
ofstream output;

//LinkedList * data = new LinkedList();

typedef struct branch {
	unsigned int address;
	string type;
}branch;

vector<branch> data;

unsigned int correct = 0;
unsigned int total = -1;
unsigned int tableSize = 0;

void readfile() {
	unsigned int address = 0;
	string type;
	while (!input.eof()) {
		type.clear();
		input >> hex >> address;
		input >> type;

		data.push_back({address, type});
		total++;
	}
}

void iterate(string prediction) {
	for (auto &temp : data) {
		if (temp.type == prediction) {
			correct++;
		}
	}
}

void alwaysTaken() {
	string prediction = "T";

	iterate(prediction);

	output << correct << "," << total << ";" << endl;
}

void alwaysNotTaken() {
	string prediction = "NT";
	correct = 0;

	iterate(prediction);

	output << correct << "," << total << ";" << endl;
}

void iterateBimodalSingle(list<string> &table) {
	list<string>::iterator it = table.begin();
	unsigned int index = 0;
	correct = 0;

	for (auto &temp : data) {
		index = temp.address % tableSize;
		it = table.begin();
		std::advance(it, index);

		if (temp.type == *it) {
			correct++;
		}else {
			*it = temp.type;
		}
	}
}

void bimodalSingle() {
	tableSize = 16;
	list<string> table (tableSize, "T");
	iterateBimodalSingle(table);
	output << correct << "," << total << "; ";

	tableSize = 32;
	table.assign(tableSize, "T");
	iterateBimodalSingle(table);
	output << correct << "," << total << "; ";

	tableSize = 128;
	table.assign(tableSize, "T");
	iterateBimodalSingle(table);
	output << correct << "," << total << "; ";

	tableSize = 256;
	table.assign(tableSize, "T");
	iterateBimodalSingle(table);
	output << correct << "," << total << "; ";

	tableSize = 512;
	table.assign(tableSize, "T");
	iterateBimodalSingle(table);
	output << correct << "," << total << "; ";

	tableSize = 1024;
	table.assign(tableSize, "T");
	iterateBimodalSingle(table);
	output << correct << "," << total << "; ";

	tableSize = 2048;
	table.assign(tableSize, "T");
	iterateBimodalSingle(table);
	output << correct << "," << total << "; ";
	
	output << endl;
}

void iterateBimodalDouble(list<string> &table) {
	//TT = strongly taken, WT = weakly taken
	//WN = weakly not taken, NN = strongly not taken
	list<string>::iterator it = table.begin();
	unsigned int index = 0;
	correct = 0;

	for (auto &temp : data) {
		index = temp.address % tableSize;
		it = table.begin();
		std::advance(it, index);

		if (*it == "TT") {
			if (temp.type == "T") {
				correct++;
			}else if (temp.type == "NT") {
				*it = "WT";
			}
		}else if (*it == "WT") {
			if (temp.type == "T") {
				correct++;
				*it = "TT";
			}else if (temp.type == "NT") {
				*it = "WN";
			}
		}else if (*it == "WN") {
			if (temp.type == "T") {
				*it = "WT";
			}else if (temp.type == "NT") {
				correct++;
				*it = "NN";
			}
		}else if (*it == "NN") {
			if (temp.type == "T") {
				*it = "WN";
			}else if (temp.type == "NT") {
				correct++;
			}
		}
	}
}

void bimodalDouble() {
	//TT = strongly taken, WT = weakly taken
	//WN = weakly not taken, NN = strongly not taken
	tableSize = 16;
	list<string> table (tableSize, "TT");
	iterateBimodalDouble(table);
	output << correct << "," << total << "; ";

	tableSize = 32;
	table.assign(tableSize, "TT");
	iterateBimodalDouble(table);
	output << correct << "," << total << "; ";

	tableSize = 128;
	table.assign(tableSize, "TT");
	iterateBimodalDouble(table);
	output << correct << "," << total << "; ";

	tableSize = 256;
	table.assign(tableSize, "TT");
	iterateBimodalDouble(table);
	output << correct << "," << total << "; ";

	tableSize = 512;
	table.assign(tableSize, "TT");
	iterateBimodalDouble(table);
	output << correct << "," << total << "; ";

	tableSize = 1024;
	table.assign(tableSize, "TT");
	iterateBimodalDouble(table);
	output << correct << "," << total << "; ";

	tableSize = 2048;
	table.assign(tableSize, "TT");
	iterateBimodalDouble(table);
	output << correct << "," << total << "; ";

	output << endl;
}

void iterateGshare(list<string> &table, short int &gr, int grLen) {
	list<string>::iterator it = table.begin();
	unsigned int index = 0;
	correct = 0;

	for (auto &temp : data) {
		index = (temp.address % tableSize) ^ (gr & (short int)(pow(2, grLen) -1));
		it = table.begin();
		std::advance(it, index);

		if (*it == "TT") {
			if (temp.type == "T") {
				correct++;
			}else if (temp.type == "NT") {
				*it = "WT";
			}
		}else if (*it == "WT") {
			if (temp.type == "T") {
				correct++;
				*it = "TT";
			}else if (temp.type == "NT") {
				*it = "WN";
			}
		}else if (*it == "WN") {
			if (temp.type == "T") {
				*it = "WT";
			}else if (temp.type == "NT") {
				correct++;
				*it = "NN";
			}
		}else if (*it == "NN") {
			if (temp.type == "T") {
				*it = "WN";
			}else if (temp.type == "NT") {
				correct++;
			}
		}
		//shift gr left one to put in the recent outcome
		gr = gr << 1;
		//clear the grLen+1 bit
		gr &= ~(1 << (grLen+1));
		//push new into back
		if (temp.type == "T") {
			gr ^= 1 << 0;
		}
	}
}

void gshare() {
	tableSize = 2048;

	list<string> table (tableSize, "TT");
	short int gr = 0;
	iterateGshare(table, gr, 3);
	output << correct << "," << total << "; ";

	table.assign(tableSize, "TT");
	gr = 0;
	iterateGshare(table, gr, 4);
	output << correct << "," << total << "; ";

	table.assign(tableSize, "TT");
	gr = 0;
	iterateGshare(table, gr, 5);
	output << correct << "," << total << "; ";

	table.assign(tableSize, "TT");
	gr = 0;
	iterateGshare(table, gr, 6);
	output << correct << "," << total << "; ";

	table.assign(tableSize, "TT");
	gr = 0;
	iterateGshare(table, gr, 7);
	output << correct << "," << total << "; ";

	table.assign(tableSize, "TT");
	gr = 0;
	iterateGshare(table, gr, 8);
	output << correct << "," << total << "; ";

	table.assign(tableSize, "TT");
	gr = 0;
	iterateGshare(table, gr, 9);
	output << correct << "," << total << "; ";

	table.assign(tableSize, "TT");
	gr = 0;
	iterateGshare(table, gr, 10);
	output << correct << "," << total << "; ";

	table.assign(tableSize, "TT");
	gr = 0;
	iterateGshare(table, gr, 11);
	output << correct << "," << total << "; ";

	output << endl;
}

void tournament() {
	//0 prefer gshare, 1 weakly prefer gshare
	//2 weakly prefer bimodal, 3 prefer bimodal
	tableSize = 2048;
	list<short int> bimodal (tableSize, 3);
	list<short int> gshareT (tableSize, 3);
	list<short int> selector (tableSize, 0);

	correct = iterateTournament();

	output << correct << "," << total << "; " << endl;
}

int main(int argc, char *argv[]) {
	string infilename;
	string outfilename;

	if (argc == 3) {
		infilename = argv[1];
		outfilename = argv[2];
	} 
	else {
		cout << "error reading command line" << endl;
		return 0;
	}

	input.open(infilename);
	output.open(outfilename);

	readfile();
	alwaysTaken();
	alwaysNotTaken();
	bimodalSingle();
	bimodalDouble();
	gshare();
	//tournament();

	input.close();
	output.close();
}
