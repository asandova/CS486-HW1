#include "strFreqSet.h"

StringFSet::StringFSet() {
	words = vector<string>();
	freq = vector<size_t>();
}

void StringFSet::add(string s) {
	if ( !check(s) ) {
		words.push_back(s);
		freq.push_back(1); 
	}
	else {
		for (size_t i = 0; i < words.size(); i++) {
			if (words[i] == s) {
				freq[i]++;
				return;
			}
		}
	}
}

bool StringFSet::check(string s) {
	for (vector<string>::iterator itr = words.begin(); itr != words.end(); ++itr) {
		if (*itr == s) {
			return true;
		}
	}
	return false;
}

void StringFSet::remove(string s) {
	vector<string>::iterator Witr = words.begin();
	vector<size_t>::iterator Fitr = freq.begin();
	for (; Witr != words.end(), Fitr != freq.end(); ++Witr, ++Fitr ) {
		if (*Witr == s) {
			words.erase(Witr);
			freq.erase(Fitr);
			return;
		}
	
	}
}

vector<string> StringFSet::mostFreq() {
	vector<string> most = vector<string>();
	size_t highest = 0;
	for (int i = 0; i < words.size(); i++) {
		if (freq[i] > highest) {
			most.clear();
			highest = freq[i];
			most.push_back(words[i]);
		}
		else if (freq[i] == highest) {
			most.push_back(words[i]);
		}
	}
	return most;
}