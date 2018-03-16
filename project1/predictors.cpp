#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

ifstream input;
ofstream output;

typedef struct branch {
	unsigned int address;
	string type;
}branch;

vector<branch> data;

unsigned int total = -1;

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

int alwaysTaken(string type) {
	string prediction = "T";
	if (type == prediction) {
			return 1;
	}
	return 0;
}

int alwaysNotTaken(string type) {
	string prediction = "NT";
	if (type == prediction) {
			return 1;
	}
	return 0;
}

int bimodalSingle(list<string> &table, unsigned int address, string type) {
	list<string>::iterator it = table.begin();
	unsigned int index = 0;

	index = address % table.size();
	it = table.begin();
	std::advance(it, index);

	if (type == *it) {
		return 1;
	}else {
		*it = type;
	}
	return 0;
}

int bimodalDouble(list<string> &table, unsigned int address, string type) {
	list<string>::iterator it = table.begin();
	unsigned int index = 0;

	index = address % table.size();
	it = table.begin();
	std::advance(it, index);

	if (*it == "TT") {
		if (type == "T") {
			return 1;
		}
		*it = "WT";
		return 0;
	}else if (*it == "WT") {
		if (type == "T") {
			*it = "TT";
			return 1;
		}
		*it = "WN";
		return 0;
	}else if (*it == "WN") {
		if (type == "T") {
			*it = "WT";
			return 0;
		}
		*it = "NN";
		return 1;
	}else if (*it == "NN") {
		if (type == "T") {
			*it = "WN";
			return 0;
		}
		return 1;
	}
	return 0;
}
#if 0
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

void iterateTournament(list<short int> &selector) {
	short int gr = 0;
	int grLen = 11;
	for (auto &temp : data) {
		//do gshare
		index = (temp.address % 2048) ^ (gr & (short int)(pow(2, grLen) -1));
		it = selector.begin();
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

void tournament() {
	//0 prefer gshare, 1 weakly prefer gshare
	//2 weakly prefer bimodal, 3 prefer bimodal
	tableSize = 2048;
	list<string> bimodal (tableSize, "TT");
	list<string> gshareT (tableSize, "TT");
	list<short int> selector (tableSize, 0);

	correct = iterateTournament();

	output << correct << "," << total << "; " << endl;
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
		return 0;
	}

	input.open(infilename);
	output.open(outfilename);

	readfile();

	//always
	int correctAT = 0;
	int correctNT = 0;

	//bimodal single
	list<string> tableS16 (16, "T");
	list<string> tableS32 (32, "T");
	list<string> tableS128 (128, "T");
	list<string> tableS256 (256, "T");
	list<string> tableS512 (512, "T");
	list<string> tableS1024 (1024, "T");
	list<string> tableS2048 (2048, "T");
	int correctS16 = 0;
	int correctS32 = 0;
	int correctS128 = 0;
	int correctS256 = 0;
	int correctS512 = 0;
	int correctS1024 = 0;
	int correctS2048 = 0;

	//bimodal double
	list<string> tableD16 (16, "TT");
	list<string> tableD32 (32, "TT");
	list<string> tableD128 (128, "TT");
	list<string> tableD256 (256, "TT");
	list<string> tableD512 (512, "TT");
	list<string> tableD1024 (1024, "TT");
	list<string> tableD2048 (2048, "TT");
	int correctD16 = 0;
	int correctD32 = 0;
	int correctD128 = 0;
	int correctD256 = 0;
	int correctD512 = 0;
	int correctD1024 = 0;
	int correctD2048 = 0;

	for (auto &temp : data) {
		if (alwaysTaken(temp.type) == 1) {
			correctAT++;
		}
		if (alwaysNotTaken(temp.type) == 1) {
			correctNT++;
		}
		if (bimodalSingle(tableS16, temp.address, temp.type) == 1) {
			correctS16++;
		}
		if (bimodalSingle(tableS32, temp.address, temp.type) == 1) {
			correctS32++;
		}
		if (bimodalSingle(tableS128, temp.address, temp.type) == 1) {
			correctS128++;
		}
		if (bimodalSingle(tableS256, temp.address, temp.type) == 1) {
			correctS256++;
		}
		if (bimodalSingle(tableS512, temp.address, temp.type) == 1) {
			correctS512++;
		}
		if (bimodalSingle(tableS1024, temp.address, temp.type) == 1) {
			correctS1024++;
		}
		if (bimodalSingle(tableS2048, temp.address, temp.type) == 1) {
			correctS2048++;
		}
		if (bimodalDouble(tableD16, temp.address, temp.type) == 1) {
			correctD16++;
		}
		if (bimodalDouble(tableD32, temp.address, temp.type) == 1) {
			correctD32++;
		}
		if (bimodalDouble(tableD128, temp.address, temp.type) == 1) {
			correctD128++;
		}
		if (bimodalDouble(tableD256, temp.address, temp.type) == 1) {
			correctD256++;
		}
		if (bimodalDouble(tableD512, temp.address, temp.type) == 1) {
			correctD512++;
		}
		if (bimodalDouble(tableD1024, temp.address, temp.type) == 1) {
			correctD1024++;
		}
		if (bimodalDouble(tableD2048, temp.address, temp.type) == 1) {
			correctD2048++;
		}
	}

	output << correctAT << "," << total << "; " << endl;
	output << correctNT << "," << total << "; " << endl;
	
	output << correctS16 << "," << total << "; ";
	output << correctS32 << "," << total << "; ";
	output << correctS128 << "," << total << "; ";
	output << correctS256 << "," << total << "; ";
	output << correctS512 << "," << total << "; ";
	output << correctS1024 << "," << total << "; ";
	output << correctS2048 << "," << total << "; ";
	output << endl;

	output << correctD16 << "," << total << "; ";
	output << correctD32 << "," << total << "; ";
	output << correctD128 << "," << total << "; ";
	output << correctD256 << "," << total << "; ";
	output << correctD512 << "," << total << "; ";
	output << correctD1024 << "," << total << "; ";
	output << correctD2048 << "," << total << "; ";
	output << endl;


	//bimodalDouble();
	//gshare();
	//tournament();

	input.close();
	output.close();
}
