#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	ifstream input;
	ofstream output;
	
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

	long address = 0;
	string type;

	while (!input.eof()) {
		
	}


}
