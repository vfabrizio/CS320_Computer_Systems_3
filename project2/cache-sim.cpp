#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <cmath>
#include <utility> //pair
#include <algorithm> //find

using namespace std;

int direct_mapped(unsigned int address, pair<short int, int> table[], int size) {
	int num_bits = floor(log2(size));

	int index = address & (size-1); //get the last num_bits bits
	int tag = address >> num_bits; // get the rest without the index;

	if (table[index].first == 1) {
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

int set_associative(unsigned int address, pair<short int, int> table[], deque<pair<int,int>> list[], int ways) {
	//all tables are 512 but if in another set then we will check
	//		index + num of lines
	int num_lines = 512 / ways;
	int num_bits = floor(log2(num_lines));

	int index = address & (num_lines-1); //get the last num_bits bits
	int tag = address >> num_bits; // get the rest without the index;
	int tempindex = index;

	int i = 0;
	while (i < ways) {
		//check valid
		if (table[index].first == 1) {
			//check tag
			if (table[index].second == tag) {
				pair<int,int> curr = make_pair(tag, i);
				deque<pair<int,int>>::iterator loc = find(list[tempindex].begin(), list[tempindex].end(), curr);
				pair<int,int> temp = *loc;
				list[tempindex].erase(loc);
				list[tempindex].push_front(temp);
				return 1;
			}
		}
		//didn't find in that way, go to the next
		i++;
		index = index + num_lines;
	}
	//cache miss
	//didn't find in any way
	index = tempindex;
	i = 0;
	//look in ways for open slot
	while (i < ways) {
		if (table[index].first == 0) {
			table[index].first = 1;
			table[index].second = tag;
			list[tempindex].pop_back();
			list[tempindex].push_front(make_pair(tag, i));
			return 0;
		}
		i++;
		index = index + num_lines;
	}
	//no empty slots in cache, use LRU
	int way = list[tempindex].back().second;
	list[tempindex].pop_back();
	list[tempindex].push_front(make_pair(tag, way));
	table[tempindex + (way*num_lines)].first = 1;
	table[tempindex + (way*num_lines)].second = tag;
	return 0;
}

int fully_associative_lru(unsigned int address, pair<short int, int> table[], deque<pair<int,int>> list) {
//all tables are 512 but if in another set then we will check
	//		index + num of lines
	int ways = 512;
	int num_lines = 512 / ways;
	int num_bits = floor(log2(num_lines));

	int index = address & (num_lines-1); //get the last num_bits bits
	int tag = address >> num_bits; // get the rest without the index;
	int tempindex = index;

	int i = 0;
	while (i < ways) {
		//check valid
		if (table[index].first == 1) {
			//check tag
			if (table[index].second == tag) {
				pair<int,int> curr = make_pair(tag, i);
				deque<pair<int,int>>::iterator loc = find(list.begin(), list.end(), curr);
				pair<int,int> temp = *loc;
				list.erase(loc);
				list.push_front(temp);
				return 1;
			}
		}
		//didn't find in that way, go to the next
		i++;
		index = index + num_lines;
	}
	//cache miss
	//didn't find in any way
	index = tempindex;
	i = 0;
	//look in ways for open slot
	while (i < ways) {
		if (table[index].first == 0) {
			table[index].first = 1;
			table[index].second = tag;
			list.pop_back();
			list.push_front(make_pair(tag, i));
			return 0;
		}
		i++;
		index = index + num_lines;
	}
	//no empty slots in cache, use LRU
	int way = list.back().second;
	list.pop_back();
	list.push_front(make_pair(tag, way));
	//table[tempindex + (way*num_lines)].first = 1;
	//table[tempindex + (way*num_lines)].second = tag;
	table[way].first = 1;
	table[way].second = tag;
	return 0;
}

int fully_associative_hc() {

}

int set_no_alloc(string type, unsigned int address, pair<short int, int> table[], deque<pair<int,int>> list[], int ways) {
	//all tables are 512 but if in another set then we will check
	//		index + num of lines
	int num_lines = 512 / ways;
	int num_bits = floor(log2(num_lines));

	int index = address & (num_lines-1); //get the last num_bits bits
	int tag = address >> num_bits; // get the rest without the index;
	int tempindex = index;

	int i = 0;
	while (i < ways) {
		//check valid
		if (table[index].first == 1) {
			//check tag
			if (table[index].second == tag) {
				pair<int,int> curr = make_pair(tag, i);
				deque<pair<int,int>>::iterator loc = find(list[tempindex].begin(), list[tempindex].end(), curr);
				pair<int,int> temp = *loc;
				list[tempindex].erase(loc);
				list[tempindex].push_front(temp);
				return 1;
			}
		}
		//didn't find in that way, go to the next
		i++;
		index = index + num_lines;
	}
	//cache miss
	//didn't find in any way
	if (type != "S") {
		index = tempindex;
		i = 0;
		//look in ways for open slot
		while (i < ways) {
			if (table[index].first == 0) {
				table[index].first = 1;
				table[index].second = tag;
				list[tempindex].pop_back();
				list[tempindex].push_front(make_pair(tag, i));
				return 0;
			}
			i++;
			index = index + num_lines;
		}
		//no empty slots in cache, use LRU
		int way = list[tempindex].back().second;
		list[tempindex].pop_back();
		list[tempindex].push_front(make_pair(tag, way));
		table[tempindex + (way*num_lines)].first = 1;
		table[tempindex + (way*num_lines)].second = tag;
		return 0;
	}
	return 0;
}

int set_prefetch(unsigned int address, pair<short int, int> table[], deque<pair<int,int>> list[], int ways) {
	//all tables are 512 but if in another set then we will check
	//		index + num of lines
	int num_lines = 512 / ways;
	int num_bits = floor(log2(num_lines));

	int index = address & (num_lines-1); //get the last num_bits bits
	int tag = address >> num_bits; // get the rest without the index;
	int tempindex = index;

	//prefetch is the index that we have to go to for the next line
	int prefetch = (address + 1) & (num_lines-1);
	int tempprefetch = prefetch;
	//can't be sure they will go in the same way so you can't exit
	//	the first while loop when you found original access
	bool found = false;
	bool added = false;
	bool foundprefetch = false;

	int i = 0;
	while (i < ways) {
		//check valid
		if (table[index].first == 1) {
			//check tag
			if (table[index].second == tag) {
				pair<int,int> curr = make_pair(tag, i);
				deque<pair<int,int>>::iterator loc = find(list[tempindex].begin(), list[tempindex].end(), curr);
				pair<int,int> temp = *loc;
				list[tempindex].erase(loc);
				list[tempindex].push_front(temp);
				found = true;
				break;
			}
		}
		//didn't find in that way, go to the next
		i++;
		index = index + num_lines;
	}
	if (found == false) {
		//cache miss for the original cache access
		//didn't find in any way
		index = tempindex;
		i = 0;
		//look in ways for open slot
		while (i < ways) {
			if (table[index].first == 0) {
				table[index].first = 1;
				table[index].second = tag;
				list[tempindex].pop_back();
				list[tempindex].push_front(make_pair(tag, i));
				added = true;
				break;
			}
			i++;
			index = index + num_lines;
		}
		if (added == false) {
			//no empty slots in cache, use LRU
			int way = list[tempindex].back().second;
			list[tempindex].pop_back();
			list[tempindex].push_front(make_pair(tag, way));
			table[tempindex + (way*num_lines)].first = 1;
			table[tempindex + (way*num_lines)].second = tag;	
			added = true;
		}
	}

	//check if prefetch is in cache 
	i = 0;
	while (i < ways) {
		//check valid
		if (table[prefetch].first == 1) {
			//check tag
			if (table[prefetch].second == tag) {
				pair<int,int> curr = make_pair(tag, i);
				deque<pair<int,int>>::iterator loc = find(list[tempprefetch].begin(), list[tempprefetch].end(), curr);
				pair<int,int> temp = *loc;
				list[tempprefetch].erase(loc);
				list[tempprefetch].push_front(temp);
				if (found == true) return 1;
				else return 0;
			}
		}
		//didn't find in that way, go to the next
		i++;
		prefetch = prefetch + num_lines;
	}
	//if the prefetch isnt in the cache, put it in
	prefetch = tempprefetch;
	i = 0;
	//look in ways for open slot
	while (i < ways) {
		if (table[prefetch].first == 0) {
			table[prefetch].first = 1;
			table[prefetch].second = tag;
			list[tempprefetch].pop_back();
			list[tempprefetch].push_front(make_pair(tag, i));
			if (found == true) return 1;
			else return 0;
		}
		i++;
		prefetch = prefetch + num_lines;
	}
	//no empty slots in cache, use LRU
	int way = list[tempprefetch].back().second;
	list[tempprefetch].pop_back();
	list[tempprefetch].push_front(make_pair(tag, way));
	table[tempprefetch + (way*num_lines)].first = 1;
	table[tempprefetch + (way*num_lines)].second = tag;
	if (found == true) return 1;
	else return 0;
}

int set_prefetch_miss(unsigned int address, pair<short int, int> table[], deque<pair<int,int>> list[], int ways) {
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
	//pair in deque <tag, way>
	pair<short int, int> twoset[512] = {};
	fill_n(twoset, 512, make_pair(0, 0));
	deque<pair<int,int>> two[256] = {};
	fill_n(two, 256, deque<pair<int,int>>(2, make_pair(0,0)));

	pair<short int, int> fourset[512] = {};
	fill_n(fourset, 512, make_pair(0, 0));
	deque<pair<int,int>> four[128] = {};
	fill_n(four, 128, deque<pair<int,int>>(4, make_pair(0,0)));

	pair<short int, int> eightset[512] = {};
	fill_n(eightset, 512, make_pair(0, 0));
	deque<pair<int,int>> eight[64] = {};
	fill_n(eight, 64, deque<pair<int,int>>(8, make_pair(0,0)));

	pair<short int, int> sixteenset[512] = {};
	fill_n(sixteenset, 512, make_pair(0, 0));
	deque<pair<int,int>> sixteen[32] = {};
	fill_n(sixteen, 32, deque<pair<int,int>>(16, make_pair(0,0)));

	int correctSA2 = 0;
	int correctSA4 = 0;
	int correctSA8 = 0;
	int correctSA16 = 0;

	//fully associative lru
	//pair in deque <tag, index>
	pair<short int, int> full_lru[512] = {};
	fill_n(full_lru, 512, make_pair(0, 0));
	deque<pair<int,int>> lru (512, make_pair(0,0));
	int correctFLRU = 0;

	//fully associative hot cold
	pair<short int, int> full_hc[512] = {};
	fill_n(full_hc, 512, make_pair(0, 0));

	int correctFHC = 0;

	//set-associative no allocation for write miss
	//all 16kb == 512 lines
	//pair in array <tag, way>
	pair<short int, int> twoset2[512] = {};
	fill_n(twoset2, 512, make_pair(0, 0));
	deque<pair<int,int>> two2[256] = {};
	fill_n(two2, 256, deque<pair<int,int>>(2, make_pair(0,0)));

	pair<short int, int> fourset2[512] = {};
	fill_n(fourset2, 512, make_pair(0, 0));
	deque<pair<int,int>> four2[128] = {};
	fill_n(four2, 128, deque<pair<int,int>>(4, make_pair(0,0)));

	pair<short int, int> eightset2[512] = {};
	fill_n(eightset2, 512, make_pair(0, 0));
	deque<pair<int,int>> eight2[64] = {};
	fill_n(eight2, 64, deque<pair<int,int>>(8, make_pair(0,0)));

	pair<short int, int> sixteenset2[512] = {};
	fill_n(sixteenset2, 512, make_pair(0, 0));
	deque<pair<int,int>> sixteen2[32] = {};
	fill_n(sixteen2, 32, deque<pair<int,int>>(16, make_pair(0,0)));

	int correctWM2 = 0;
	int correctWM4 = 0;
	int correctWM8 = 0;
	int correctWM16 = 0;

	//set-associative prefetching
	pair<short int, int> twoset3[512] = {};
	fill_n(twoset3, 512, make_pair(0, 0));
	deque<pair<int,int>> two3[256] = {};
	fill_n(two3, 256, deque<pair<int,int>>(2, make_pair(0,0)));

	pair<short int, int> fourset3[512] = {};
	fill_n(fourset3, 512, make_pair(0, 0));
	deque<pair<int,int>> four3[128] = {};
	fill_n(four3, 128, deque<pair<int,int>>(4, make_pair(0,0)));

	pair<short int, int> eightset3[512] = {};
	fill_n(eightset3, 512, make_pair(0, 0));
	deque<pair<int,int>> eight3[64] = {};
	fill_n(eight3, 64, deque<pair<int,int>>(8, make_pair(0,0)));

	pair<short int, int> sixteenset3[512] = {};
	fill_n(sixteenset3, 512, make_pair(0, 0));
	deque<pair<int,int>> sixteen3[32] = {};
	fill_n(sixteen3, 32, deque<pair<int,int>>(16, make_pair(0,0)));

	int correctP2 = 0;
	int correctP4 = 0;
	int correctP8 = 0;
	int correctP16 = 0;

	//set-associative prefetching on miss
	pair<short int, int> twoset4[512] = {};
	fill_n(twoset4, 512, make_pair(0, 0));
	deque<pair<int,int>> two4[256] = {};
	fill_n(two4, 256, deque<pair<int,int>>(2, make_pair(0,0)));

	pair<short int, int> fourset4[512] = {};
	fill_n(fourset4, 512, make_pair(0, 0));
	deque<pair<int,int>> four4[128] = {};
	fill_n(four4, 128, deque<pair<int,int>>(4, make_pair(0,0)));

	pair<short int, int> eightset4[512] = {};
	fill_n(eightset4, 512, make_pair(0, 0));
	deque<pair<int,int>> eight4[64] = {};
	fill_n(eight4, 64, deque<pair<int,int>>(8, make_pair(0,0)));

	pair<short int, int> sixteenset4[512] = {};
	fill_n(sixteenset4, 512, make_pair(0, 0));
	deque<pair<int,int>> sixteen4[32] = {};
	fill_n(sixteen4, 32, deque<pair<int,int>>(16, make_pair(0,0)));

	int correctPM2 = 0;
	int correctPM4 = 0;
	int correctPM8 = 0;
	int correctPM16 = 0;

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
		//set-associative
		if (set_associative(address, twoset, two, 2) == 1) {
			correctSA2++;
		}
		if (set_associative(address, fourset, four, 4) == 1) {
			correctSA4++;
		}
		if (set_associative(address, eightset, eight, 8) == 1) {
			correctSA8++;
		}
		if (set_associative(address, sixteenset, sixteen, 16) == 1) {
			correctSA16++;
		}
		//fully-associative
		/*if (fully_associative_lru(address, full_lru, lru) == 1) {
			correctFLRU++;
		}
		if (fully_associative_hc() == 1) {
			correctFHC++;
		}*/
		//set-associative with no allocation on write miss
		if (set_no_alloc(type, address, twoset2, two2, 2) == 1) {
			correctWM2++;
		}
		if (set_no_alloc(type, address, fourset2, four2, 4) == 1) {
			correctWM4++;
		}
		if (set_no_alloc(type, address, eightset2, eight2, 8) == 1) {
			correctWM8++;
		}
		if (set_no_alloc(type, address, sixteenset2, sixteen2, 16) == 1) {
			correctWM16++;
		}
		//set-associative with next-line prefetching
		if (set_prefetch(address, twoset3, two3, 2) == 1) {
			correctP2++;
		}
		if (set_prefetch(address, fourset3, four3, 4) == 1) {
			correctP4++;
		}
		if (set_prefetch(address, eightset3, eight3, 8) == 1) {
			correctP8++;
		}
		if (set_prefetch(address, sixteenset3, sixteen3, 16) == 1) {
			correctP16++;
		}
		//set-associative with prefetch only on a miss
		/*if (set_prefetch_miss(address, twoset4, two4, 2) == 1) {
			correctP2++;
		}
		if (set_prefetch_miss(address, fourset4, four4, 4) == 1) {
			correctP4++;
		}
		if (set_prefetch_miss(address, eightset4, eight4, 8) == 1) {
			correctP8++;
		}
		if (set_prefetch_miss(address, sixteenset4, sixteen4, 16) == 1) {
			correctP16++;
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

	output << correctFLRU << "," << total << ";" << endl;
	output << correctFHC << "," << total << ";" << endl;

	output << correctWM2 << "," << total << "; ";
	output << correctWM4 << "," << total << "; ";
	output << correctWM8 << "," << total << "; ";
	output << correctWM16 << "," << total << ";" << endl;

	output << correctP2 << "," << total << "; ";
	output << correctP4 << "," << total << "; ";
	output << correctP8 << "," << total << "; ";
	output << correctP16 << "," << total << ";" << endl;

	output << correctPM2 << "," << total << "; ";
	output << correctPM4 << "," << total << "; ";
	output << correctPM8 << "," << total << "; ";
	output << correctPM16 << "," << total << ";" << endl;
}