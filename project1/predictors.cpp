#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream input;
ofstream output;

void alwaysTaken() {
	long address = 0;
	string type;
	string prediction = "T";
	long correct = 0;
	long total = -1;

	while (!input.eof()) {
		type.clear();
		input >> hex >> address;
		input >> type;

		if (type == prediction) {
			correct++;
		}
		total++;
	}

	output << correct << "," << total << ";" << endl;
}

void alwaysNotTaken() {
	long address = 0;
	string type;
	string prediction = "NT";
	long correct = 0;
	long total = -1;

	while (!input.eof()) {
		type.clear();
		input >> hex >> address;
		input >> type;

		if (type == prediction) {
			correct++;
		}
		total++;
	}

	output << correct << "," << total << ";" << endl;
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
	}

	input.open(infilename);
	output.open(outfilename);

	alwaysTaken();
	input.clear();
	input.seekg(0, input.beg);
	
	alwaysNotTaken();
	
	input.close();
	output.close();
}
