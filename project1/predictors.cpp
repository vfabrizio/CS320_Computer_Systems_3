#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

ifstream input;
ofstream output;

multimap<long,string> data;

long correct = 0;
long total = -1;
int tableSize = 0;

void readfile() {
	long address = 0;
	string type;
	while (!input.eof()) {
		type.clear();
		input >> hex >> address;
		input >> type;

		data.insert(pair<long,string>(address, type));
		total++;
	}
}

void alwaysTaken() {
	string prediction = "T";
	correct = 0;

	for (multimap<long,string>::iterator i = data.begin(); i != data.end(); i++) {
		if (i->second == prediction) {
			correct++;
		}
	}

	output << correct << "," << total << ";" << endl;
}

void alwaysNotTaken() {
	string prediction = "NT";
	correct = 0;

	for (multimap<long,string>::iterator i = data.begin(); i != data.end(); i++) {
		if (i->second == prediction) {
			correct++;
		}
	}

	output << correct << "," << total << ";" << endl;
}

void checkBimodalSingle(list<string> &table) {
	list<string>::iterator it = table.begin();
	correct = 0;
	long index = 0;

	for (multimap<long,string>::iterator i = data.begin(); i != data.end(); i++) {
		index = ((*i).first) % tableSize;
		it = table.begin();
		advance(it, index);

		if ((*i).second == *it) {
			correct++;
		}else {
			*it = (*i).second;
		}
	}

	/*while (!input.eof()) {
		type.clear();
		input >> hex >> address;
		input >> type;

		address = address % tableSize;
		it = table.begin();
		advance(it, address);

		if (type == *it) {
			correct++;
		}else {
			*it = type;
		}
	}*/

	output << correct << "," << total << "; ";
}

void bimodalSingle() {
	tableSize = 16;
	list<string> table (tableSize, "T");
	checkBimodalSingle(table);
	
	tableSize = 32;
	table.assign(tableSize, "T");
	checkBimodalSingle(table);

	tableSize = 128;
	table.assign(tableSize, "T");
	checkBimodalSingle(table);

	tableSize = 256;
	table.assign(tableSize, "T");
	checkBimodalSingle(table);

	tableSize = 512;
	table.assign(tableSize, "T");
	checkBimodalSingle(table);

	tableSize = 1024;
	table.assign(tableSize, "T");
	checkBimodalSingle(table);

	tableSize = 2048;
	table.assign(tableSize, "T");
	checkBimodalSingle(table);
	
	output << endl;
}
#if 0
void checkBimodalDouble(list<string> &table) {
	list<string>::iterator it = table.begin();
	correct = 0;
	input.clear();
	input.seekg(0, input.beg);

	while (!input.eof()) {
		type.clear();
		input >> hex >> address;
		input >> type;

		address = address % tableSize;
		it = table.begin();
		advance(it, address);

		if (*it == "TT") {
			if (type == "T") {
				correct++;
			}else if (type == "NT") {
				*it = "WT";
			}
		}else if (*it == "WT") {
			if (type == "T") {
				correct++;
				*it = "TT";
			}else if (type == "NT") {
				*it = "WN";
			}
		}else if (*it == "WN") {
			if (type == "T") {
				*it = "WT";
			}else if (type == "NT") {
				correct++;
				*it = "NN";
			}
		}else if (*it == "NN") {
			if (type == "T") {
				*it = "WN";
			}else if (type == "NT") {
				correct++;
			}
		}
	}

	output << correct << "," << total << "; ";
}

void bimodalDouble() {
	//TT = strongly taken, WT = weakly taken
	//WN = weakly not taken, NN = strongly not taken
	tableSize = 16;
	list<string> table (tableSize, "TT");
	checkBimodalDouble(table);

	tableSize = 32;
	table.assign(tableSize, "TT");
	checkBimodalDouble(table);

	tableSize = 128;
	table.assign(tableSize, "TT");
	checkBimodalDouble(table);

	tableSize = 256;
	table.assign(tableSize, "TT");
	checkBimodalDouble(table);

	tableSize = 512;
	table.assign(tableSize, "TT");
	checkBimodalDouble(table);

	tableSize = 1024;
	table.assign(tableSize, "TT");
	checkBimodalDouble(table);

	tableSize = 2048;
	table.assign(tableSize, "TT");
	checkBimodalDouble(table);

	output << endl;
}
#endif

int main(int argc, char *argv[]) {
	string infilename;
	string outfilename;

	if (argc == 3) {
		infilename = argv[1];
		outfilename = argv[2];
	} 
	else {
		cout << "error reading command line" << endl;
	}

	input.open(infilename);
	output.open(outfilename);

	readfile();
	alwaysTaken();
	alwaysNotTaken();
	bimodalSingle();

	/*
	bimodalDouble();
	input.clear();
	input.seekg(0, input.beg);

	input.close();
	output.close();
	*/
}
