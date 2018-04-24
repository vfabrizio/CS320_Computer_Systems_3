#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <cmath>
#include <utility> //pair

using namespace std;

int direct_mapped(unsigned int address, pair<short int, int> table[], int size) {
	int num_bits = floor(log2(size));

	int index = address & (size-1); //get the last num_bits bits
	int tag = address >> num_bits; // get the rest without the index;
	//cout << address << '\t' << index << '\t' << tag << endl;

	if (table[index].first == 1) {
		//cout << "yo" << endl;
		if (table[index].second == tag) {
			return 1;
		} else {
			table[index].second = tag;
			return 0;
		}
	} else {
		table[index].second = tag;
		table[index].first = 1;
		return 0;
	}
	return 0;
}

int set_associative(unsigned int address, pair<short int, int> table[], vector<deque<pair<int,int>>> list, int ways) {
	//all tables are 512 but if in another set then we will check
	//		index + num of lines
	int num_lines = 512 / ways;
	int num_bits = floor(log2(num_lines));

	int index = address & (num_lines-1); //get the last num_bits bits
	int tag = address >> num_bits; // get the rest without the index;
	int tempindex = index;

	int i = 0;
	while (i < ways) {
		if (table[index].first == 1 && table[index].second == tag) {
			return 1;
		}
		//didn't find in that way, go to the next
		i++;
		index = index+num_lines;
	}
	//didn't find in any way
	if (list[tempindex].front().first == 0) {
		//first element has way value = 0 so there's nothing there
		table[tempindex].first = 1;
		table[tempindex].second = tag;
		list[tempindex].pop_back();
		list[tempindex].push_front(make_pair(tag, 0));
	} else if (list[tempindex].back().second == 0) {
		//if the last way is 0 then there's still room
		int i = 0;
		while (i < ways) {
			if (list[tempindex][i].first != 0) break;
			i++;
		}
		int way_num = i;
		list[tempindex].pop_back();
		list[tempindex].push_front(make_pair(tag, way_num));
		table[tempindex + (way_num*num_lines)].first = 1;
		table[tempindex + (way_num*num_lines)].second = tag;
	} else {
		//returns last element in LL == LRU
		int way = list[tempindex].back().second;
		int oldTag = list[tempindex].back().first;
		list[tempindex].pop_back();
		list[tempindex].push_front(make_pair(tag, way)); //new way = old way
		table[tempindex + (way*num_lines)].first = 1;
		table[tempindex + (way*num_lines)].second = tag;
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
	output.open(outfilename, ios::out);

	int total = -1;

	//direct-mapped
	// pair <valid bit, tag>
	pair<short int, int> oneKB[32] = {};
	fill_n(oneKB, 32, make_pair(0, 0));
	pair<short int, int> fourKB[128] = {};
	fill_n(fourKB, 128, make_pair(0, 0));
	pair<short int, int> sixteenKB[512] = {};
	fill_n(sixteenKB, 512, make_pair(0, 0));
	pair<short int, int> thirtytwoKB[1024] = {};
	fill_n(thirtytwoKB, 1024, make_pair(0, 0));
	int correct1 = 0;
	int correct4 = 0;
	int correct16 = 0;
	int correct32 = 0;

	//set-associative
	//all 16kb == 512 lines
	//pair in array <tag, way>
	pair<short int, int> twoset[512] = {};
	fill_n(twoset, 512, make_pair(0, 0));
	vector<deque<pair<int,int>> > two (256, deque<pair<int,int>>(2, make_pair(0,0)));

	pair<short int, int> fourset[512] = {};
	fill_n(fourset, 512, make_pair(0, 0));
	vector<deque<pair<int,int>> > four (128, deque<pair<int,int>>(4, make_pair(0,0)));

	pair<short int, int> eightset[512] = {};
	fill_n(eightset, 512, make_pair(0, 0));
	vector<deque<pair<int,int>> > eight (64, deque<pair<int,int>>(8, make_pair(0,0)));

	pair<short int, int> sixteenset[512] = {};
	fill_n(sixteenset, 512, make_pair(0, 0));
	vector<deque<pair<int,int>> > sixteen (32, deque<pair<int,int>>(16, make_pair(0,0)));

	int correctSA2 = 0;
	int correctSA4 = 0;
	int correctSA8 = 0;
	int correctSA16 = 0;

	unsigned int address = 0;
	string type; //type is L = load or S = store
	while (!input.eof()) {
		type.clear();
		input >> type;
		input >> hex >> address;

		total++;

		//shift out the offset bits (2^5 = 32 byte line size)
		address = address >> 5;
		
		//direct-mapped
		if (direct_mapped(address, oneKB, 32) == 1) {
			correct1++;
		}
		if (direct_mapped(address, fourKB, 128) == 1) {
			correct4++;
		}
		if (direct_mapped(address, sixteenKB, 512) == 1) {
			correct16++;
		}
		if (direct_mapped(address, thirtytwoKB, 1024) == 1) {
			correct32++;
		}
		if (set_associative(address, twoset, two, 2) == 1) {
			correctSA2++;
		}
		/*if (set_associative(address, fourset, four, 4) == 1) {
			correctSA4++;
		}
		if (set_associative(address, eightset, eight, 8) == 1) {
			correctSA8++;
		}
		if (set_associative(address, sixteenset, sixteen, 16) == 1) {
			correctSA16++;
		}*/

	}

	output << correct1 << "," << total << "; ";
	output << correct4 << "," << total << "; ";
	output << correct16 << "," << total << "; ";
	output << correct32 << "," << total << ";" << endl;

	output << correctSA2 << "," << total << "; ";
	output << correctSA4 << "," << total << "; ";
	output << correctSA8 << "," << total << "; ";
	output << correctSA16 << "," << total << ";" << endl;
}