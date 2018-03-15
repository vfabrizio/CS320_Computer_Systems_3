#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "LinkedList.h"

using namespace std;

ifstream input;
ofstream output;

LinkedList * data = new LinkedList();

long correct = 0;
long total = -1;
long tableSize = 0;

void readfile() {
	long address = 0;
	string type;
	while (!input.eof()) {
		type.clear();
		input >> hex >> address;
		input >> type;

		data->insert(address, type);
		total++;
	}
}

void alwaysTaken() {
	string prediction = "T";

	correct = data->iterate(prediction);

	output << correct << "," << total << ";" << endl;
}

void alwaysNotTaken() {
	string prediction = "NT";

	correct = data->iterate(prediction);

	output << correct << "," << total << ";" << endl;
}

void bimodalSingle() {
	tableSize = 16;
	list<string> table (tableSize, "T");
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 32;
	table.assign(tableSize, "T");
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 128;
	table.assign(tableSize, "T");
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 256;
	table.assign(tableSize, "T");
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 512;
	table.assign(tableSize, "T");
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 1024;
	table.assign(tableSize, "T");
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 2048;
	table.assign(tableSize, "T");
	correct = data->iterateBimodalSingle(table, tableSize);
	output << correct << "," << total << "; ";
	
	output << endl;
}

void bimodalDouble() {
	//TT = strongly taken, WT = weakly taken
	//WN = weakly not taken, NN = strongly not taken
	tableSize = 16;
	list<string> table (tableSize, "TT");
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 32;
	table.assign(tableSize, "TT");
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 128;
	table.assign(tableSize, "TT");
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 256;
	table.assign(tableSize, "TT");
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 512;
	table.assign(tableSize, "TT");
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 1024;
	table.assign(tableSize, "TT");
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	tableSize = 2048;
	table.assign(tableSize, "TT");
	correct = data->iterateBimodalDouble(table, tableSize);
	output << correct << "," << total << "; ";

	output << endl;
}

void gshare() {
	tableSize = 2048;
	list<string> table (tableSize, "TT");

	short int gr = 0;
	correct = data->iterateGshare(table, tableSize, gr, 3);


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

	input.close();
	output.close();
}
