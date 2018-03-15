#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "LinkedList.h"

using namespace std;

ifstream input;
ofstream output;

LinkedList * data = new LinkedList();

unsigned int correct = 0;
unsigned int total = -1;
unsigned int tableSize = 0;

void readfile() {
	unsigned int address = 0;
	string type;
	short int type_num = 0;
	while (!input.eof()) {
		type.clear();
		type_num = 0;
		input >> hex >> address;
		input >> type;

		if (type == "T") {
			type_num = 1;
		} else if (type == "NT") {
			type_num = 0;
		}

		data->insert(address, type_num);
		total++;
	}
}

void alwaysTaken() {
	short int prediction = 1;

	correct = data->iterate(prediction);

	output << correct << "," << total << ";" << endl;
}

void alwaysNotTaken() {
	short int prediction = 0;

	correct = data->iterate(prediction);

	output << correct << "," << total << ";" << endl;
}

void bimodalSingle() {
	tableSize = 16;
	list<short int> table (tableSize, 1);
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 32;
	table.assign(tableSize, 1);
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 128;
	table.assign(tableSize, 1);
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 256;
	table.assign(tableSize, 1);
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 512;
	table.assign(tableSize, 1);
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 1024;
	table.assign(tableSize, 1);
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 2048;
	table.assign(tableSize, 1);
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";
	
	output << endl;
}

void bimodalDouble() {
	//3 = strongly taken, 2 = weakly taken
	//1 = weakly not taken, 0 = strongly not taken
	tableSize = 16;
	list<short int> table (tableSize, 3);
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 32;
	table.assign(tableSize, 3);
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 128;
	table.assign(tableSize, 3);
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 256;
	table.assign(tableSize, 3);
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 512;
	table.assign(tableSize, 3);
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 1024;
	table.assign(tableSize, 3);
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 2048;
	table.assign(tableSize, 3);
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	output << endl;
}

void gshare() {
	tableSize = 2048;

	list<short int> table (tableSize, 3);
	short int gr = 0;
	correct = data->iterateGshare(table, tableSize, gr, 3);
	output << correct << "," << total << "; ";

	table.assign(tableSize, 3);
	gr = 0;
	correct = data->iterateGshare(table, tableSize, gr, 4);
	output << correct << "," << total << "; ";

	table.assign(tableSize, 3);
	gr = 0;
	correct = data->iterateGshare(table, tableSize, gr, 5);
	output << correct << "," << total << "; ";

	table.assign(tableSize, 3);
	gr = 0;
	correct = data->iterateGshare(table, tableSize, gr, 6);
	output << correct << "," << total << "; ";

	table.assign(tableSize, 3);
	gr = 0;
	correct = data->iterateGshare(table, tableSize, gr, 7);
	output << correct << "," << total << "; ";

	table.assign(tableSize, 3);
	gr = 0;
	correct = data->iterateGshare(table, tableSize, gr, 8);
	output << correct << "," << total << "; ";

	table.assign(tableSize, 3);
	gr = 0;
	correct = data->iterateGshare(table, tableSize, gr, 9);
	output << correct << "," << total << "; ";

	table.assign(tableSize, 3);
	gr = 0;
	correct = data->iterateGshare(table, tableSize, gr, 10);
	output << correct << "," << total << "; ";

	table.assign(tableSize, 3);
	gr = 0;
	correct = data->iterateGshare(table, tableSize, gr, 11);
	output << correct << "," << total << "; ";

	cout << endl;
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

	input.close();
	output.close();
}
