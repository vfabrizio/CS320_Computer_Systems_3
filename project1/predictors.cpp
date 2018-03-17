#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

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

int bimodalSingle(string * table, int len, unsigned int address, string type) {
	unsigned int index = address % len;

	if (type == table[index]) {
		return 1;
	}else {
		table[index] = type;
	}
	return 0;
}

int bimodalDouble(string * table, int len, unsigned int address, string type) {
	
	unsigned int index = address % len;

	if (type == "T") {
		if (table[index] == "TT") {
			return 1;
		} else if (table[index] == "WT") {
			table[index] = "TT";
			return 1;
		} else if (table[index] == "WN") {
			table[index] = "WT";
			return 0;
		}
		table[index] = "WN";
		return 0;
	} else {
		if (table[index] == "TT") {
			table[index] = "WT";
			return 0;
		} else if (table[index] == "WT") {
			table[index] = "WN";
			return 0;
		} else if (table[index] == "WN") {
			table[index] = "NN";
			return 1;
		}
		return 1;
	}
	return 0;
}

int gshare(string * table, int len, short int &gr, int grLen, unsigned int address, string type) {
	
	unsigned int index = (address % len) ^ (gr & (short int)(pow(2, grLen)-1));

	if (type == "T") {
		//shift gr left one to put in the recent outcome
		gr = gr << 1;
		//clear the grLen+1 bit
		gr &= ~(1 << (grLen+1));
		//push new into back
		gr ^= 1 << 0;
		if (table[index] == "TT") {
			return 1;
		} else if (table[index] == "WT") {
			table[index] = "TT";
			return 1;
		} else if (table[index] == "WN") {
			table[index] = "WT";
			return 0;
		}
		table[index] = "WN";
		return 0;
	} else {
		//shift gr left one to put in the recent outcome
		gr = gr << 1;
		//clear the grLen+1 bit
		gr &= ~(1 << (grLen+1));
		if (table[index] == "TT") {
			table[index] = "WT";
			return 0;
		} else if (table[index] == "WT") {
			table[index] = "WN";
			return 0;
		} else if (table[index] == "WN") {
			table[index] = "NN";
			return 1;
		}
		return 1;
	}
	return 0;
}

int tournament(string * grtable, string * bitable, short int * selector, short int &gr, unsigned int address, string type) {

	int bires = bimodalDouble(bitable, 2048, address, type);
	int grres = gshare(grtable, 2048, gr, 11, address, type);

	if (bires == grres) {
		if (bires == 1) return 1;
		else return 0;
	}
	else {
		unsigned int index = address % 2048;

		//0 prefer gshare, 1 weakly prefer gshare
		//2 weakly prefer bimodal, 3 prefer bimodal
		if (bires == 1) {
			if (selector[index] == 0) {
				selector[index] = 1;
				return 0;
			} else if (selector[index] == 1) {
				selector[index] = 2;
				return 0;
			} else if (selector[index] == 2) {
				selector[index] = 3;
				return 1;
			} else {
				return 1;
			}
		} else if (grres == 1) {
			if (selector[index] == 0) {
				return 1;
			} else if (selector[index] == 1) {
				selector[index] = 0;
				return 1;
			} else if (selector[index] == 2) {
				selector[index] = 1;
				return 0;
			} else {
				selector[index] = 2;
				return 0;
			}
		}
	}
	return 0;
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

	ifstream input;
	ofstream output;

	input.open(infilename);
	output.open(outfilename);

	unsigned int total = -1;

	//always
	int correctAT = 0;
	int correctNT = 0;

	//bimodal single
	string tableS16[16] = {};
	fill_n(tableS16, 16, "T");
	string tableS32[32] = {};
	fill_n(tableS32, 32, "T");
	string tableS128[128] = {};
	fill_n(tableS128, 128, "T");
	string tableS256[256] = {};
	fill_n(tableS256, 256, "T");
	string tableS512[512] = {};
	fill_n(tableS512, 512, "T");
	string tableS1024[1024] = {};
	fill_n(tableS1024, 1024, "T");
	string tableS2048[2048] = {};
	fill_n(tableS2048, 2048, "T");
	int correctS16 = 0;
	int correctS32 = 0;
	int correctS128 = 0;
	int correctS256 = 0;
	int correctS512 = 0;
	int correctS1024 = 0;
	int correctS2048 = 0;

	//bimodal double
	string tableD16[16] = {};
	fill_n(tableD16, 16, "TT");
	string tableD32[32] = {};
	fill_n(tableD32, 32, "TT");
	string tableD128[128] = {};
	fill_n(tableD128, 128, "TT");
	string tableD256[256] = {};
	fill_n(tableD256, 256, "TT");
	string tableD512[512] = {};
	fill_n(tableD512, 512, "TT");
	string tableD1024[1024] = {};
	fill_n(tableD1024, 1024, "TT");
	string tableD2048[2048] = {};
	fill_n(tableD2048, 2048, "TT");
	int correctD16 = 0;
	int correctD32 = 0;
	int correctD128 = 0;
	int correctD256 = 0;
	int correctD512 = 0;
	int correctD1024 = 0;
	int correctD2048 = 0;

	//gshare
	string tableGr3[2048] = {};
	fill_n(tableGr3, 2048, "TT");
	string tableGr4[2048] = {};
	fill_n(tableGr4, 2048, "TT");
	string tableGr5[2048] = {};
	fill_n(tableGr5, 2048, "TT");
	string tableGr6[2048] = {};
	fill_n(tableGr6, 2048, "TT");
	string tableGr7[2048] = {};
	fill_n(tableGr7, 2048, "TT");
	string tableGr8[2048] = {};
	fill_n(tableGr8, 2048, "TT");
	string tableGr9[2048] = {};
	fill_n(tableGr9, 2048, "TT");
	string tableGr10[2048] = {};
	fill_n(tableGr10, 2048, "TT");
	string tableGr11[2048] = {};
	fill_n(tableGr11, 2048, "TT");
	int correctGr3 = 0;
	int correctGr4 = 0;
	int correctGr5 = 0;
	int correctGr6 = 0;
	int correctGr7 = 0;
	int correctGr8 = 0;
	int correctGr9 = 0;
	int correctGr10 = 0;
	int correctGr11 = 0;
	short int gr3 = 0, gr4 = 0, gr5 = 0, gr6 = 0, gr7 = 0, gr8 = 0, gr9 = 0, gr10 = 0, gr11 = 0;

	//tournament
	//0 prefer gshare, 1 weakly prefer gshare
	//2 weakly prefer bimodal, 3 prefer bimodal
	short int selector[2048] = {};
	fill_n(selector, 2048, 0);
	string grtable[2048] = {};
	fill_n(grtable, 2048, "TT");
	string bitable[2048] = {};
	fill_n(bitable, 2048, "TT");
	int correcttour = 0;
	short int tourgr11 = 0;


	unsigned int address = 0;
	string type;
	while (!input.eof()) {
		type.clear();
		input >> hex >> address;
		input >> type;

		total++;

		if (alwaysTaken(type) == 1) {
			correctAT++;
		}
		if (alwaysNotTaken(type) == 1) {
			correctNT++;
		}
		if (bimodalSingle(tableS16, 16, address, type) == 1) {
			correctS16++;
		}
		if (bimodalSingle(tableS32, 32, address, type) == 1) {
			correctS32++;
		}
		if (bimodalSingle(tableS128, 128, address, type) == 1) {
			correctS128++;
		}
		if (bimodalSingle(tableS256, 256, address, type) == 1) {
			correctS256++;
		}
		if (bimodalSingle(tableS512, 512, address, type) == 1) {
			correctS512++;
		}
		if (bimodalSingle(tableS1024, 1024, address, type) == 1) {
			correctS1024++;
		}
		if (bimodalSingle(tableS2048, 2048, address, type) == 1) {
			correctS2048++;
		}
		if (bimodalDouble(tableD16, 16, address, type) == 1) {
			correctD16++;
		}
		if (bimodalDouble(tableD32, 32, address, type) == 1) {
			correctD32++;
		}
		if (bimodalDouble(tableD128, 128, address, type) == 1) {
			correctD128++;
		}
		if (bimodalDouble(tableD256, 256, address, type) == 1) {
			correctD256++;
		}
		if (bimodalDouble(tableD512, 512, address, type) == 1) {
			correctD512++;
		}
		if (bimodalDouble(tableD1024, 1024, address, type) == 1) {
			correctD1024++;
		}
		if (bimodalDouble(tableD2048, 2048, address, type) == 1) {
			correctD2048++;
		}
		if (gshare(tableGr3, 2048, gr3, 3, address, type) == 1) {
			correctGr3++;
		}
		if (gshare(tableGr4, 2048, gr4, 4, address, type) == 1) {
			correctGr4++;
		}
		if (gshare(tableGr5, 2048, gr5, 5, address, type) == 1) {
			correctGr5++;
		}
		if (gshare(tableGr6, 2048, gr6, 6, address, type) == 1) {
			correctGr6++;
		}
		if (gshare(tableGr7, 2048, gr7, 7, address, type) == 1) {
			correctGr7++;
		}
		if (gshare(tableGr8, 2048, gr8, 8, address, type) == 1) {
			correctGr8++;
		}
		if (gshare(tableGr9, 2048, gr9, 9, address, type) == 1) {
			correctGr9++;
		}
		if (gshare(tableGr10, 2048, gr10, 10, address, type) == 1) {
			correctGr10++;
		}
		if (gshare(tableGr11, 2048, gr11, 11, address, type) == 1) {
			correctGr11++;
		}
		if (tournament(grtable, bitable, selector, tourgr11, address, type) == 1) {
			correcttour++;
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

	output << correctGr3 << "," << total << "; ";
	output << correctGr4 << "," << total << "; ";
	output << correctGr5 << "," << total << "; ";
	output << correctGr6 << "," << total << "; ";
	output << correctGr7 << "," << total << "; ";
	output << correctGr8 << "," << total << "; ";
	output << correctGr9 << "," << total << "; ";
	output << correctGr10 << "," << total << "; ";
	output << correctGr11 << "," << total << "; ";
	output << endl;

	output << correcttour << "," << total << "; " << endl;

	//tournament();

	input.close();
	output.close();
}
