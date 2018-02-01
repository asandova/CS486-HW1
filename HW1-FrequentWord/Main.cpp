#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <regex>
#include <cctype>
#include <limits>
//#include <stdlib.h>

using namespace std;

struct WordFreq {
	int freq;
	string word;
};

string removePunc(string str) {

	// .!?
	for (string::iterator itr = str.begin(); itr != str.end(); ++itr) {
		if (isupper(*itr)) {
			*itr = tolower(*itr);
		}
		if (*itr == '.' || *itr == '?' || *itr == '!' || *itr == '-' || *itr == ',') {
			string::iterator itr1 = itr;
			if ((++itr1) == str.end()) {
				str.erase(itr);
				break;
			}
			str.erase(itr);

		}
	}
	return str;
}

vector<WordFreq> StringtoWords(string str) {
	vector<WordFreq> freq = vector<WordFreq>();
	for (size_t s = 0; s < str.length(); s++) {
		for (size_t e = s; e < str.length(); e++) {
			char cur = str[e];
			if (cur == ' ') {
				WordFreq temp;
				temp.freq = 0;
				temp.word = str.substr(s, e - s);
				freq.push_back( temp );
				s = e+1;
			}
		}
	}
	return freq;
}

vector<WordFreq> FrequentWords(string text, int wordlen) {
	string clnText = removePunc(text);
	vector<WordFreq> words = StringtoWords(clnText);
	string len;
	stringstream strS;
	strS << wordlen;
	len = strS.str();
	//regex r("[a-zA-Z]{2}");
	regex r("[a-zA-Z]{" + len + "}");
	for (vector<WordFreq>::iterator itr = words.begin(); itr != words.end(); ++itr) {
		bool match = regex_match(itr->word, r);
		if (match) {
			itr->freq++;
		}
	}
	vector<WordFreq> highestFreq = vector<WordFreq>();
	int highest = 0;
	for (vector<WordFreq>::iterator itr = words.begin(); itr != words.end(); ++itr) {
		if (itr->freq > highest) {
			highest = itr->freq;
			highestFreq.clear();
			highestFreq.push_back(*itr);
		}
		else if (itr->freq == highest) {
			highestFreq.push_back( *itr );
		}
	}
	return highestFreq;
}

size_t FindOrigin(string DNA){
	size_t Cnum = 0, Gnum = 0;
	int Clow = 0, GHigh = 0;
	size_t CLowIndex = numeric_limits<size_t>::max() , GHighIndex = 0;
	char cur;
	for (size_t i = 0; i < DNA.length(); i++) {
		cur = DNA[i];
		if (cur == 'c' || cur == 'C') {
			Cnum++;
		}
		else if (cur == 'g' || cur == 'G') {
			Gnum++;
		}
		int GCDif = (int)Gnum - (int)Cnum;
		if (GCDif < Clow) {
			Clow = (int)Gnum - (int)Cnum;
			CLowIndex = i;
		}
		else if (GCDif > GHigh ) {
			GHigh = (int)Gnum - (int)Cnum;
			GHighIndex = i;
		}
	}
	return CLowIndex;
}

void testall() {
	/*
	string s = "Welcome to the unofficial encyclopedia for Virtual Villagers the puzzling video game series created by Last Day of Work. This wiki currently has 1,877 pages, and 153 articles. The series consists of five games in which you have to help a group of villagers survive on the mysterious island of Isola. Along the way, you will solve interesting puzzles that will test your mind-whether it be harvesting food, breeding, or creating shelter-and learn different skills in order to survive!";
	vector<WordFreq> most;
	most = FrequentWords(s, 9);
	for (vector<WordFreq>::iterator itr = most.begin(); itr != most.end(); ++itr) {
		cout << itr->word << ", ";
	}*/
	cout << endl;
	string dna = "aatgatgatgacgtcaaaaggatccggataaaacatggtgattgcctcgcataacgcggtatgaaaatggattgaagcccgggccgtggattctactcaactttgtcggcttgagaaagacctgggatcctgggtattaaaaagaagatctatttatttagagatctgttctattgtgatctcttattaggatcgcactgccctgtggataacaaggatccggcttttaagatcaacaacctggaaaggatcattaactgtgaatgatcggtgatcctggaccgtataagctgggatcagaatgaggggttatacacaactcaaaaactgaacaacagttgttctttggataactaccggttgatccaagcttcctgacagagttatccacagtagatcgcacgatctgtatacttatttgagtaaattaacccacgatcccagccattcttctgccggatcttccggaatgtcgtgatcaagaatgttgatcttcagtg";
	cout << "origin index: " <<FindOrigin(dna) << endl;

}

int main() {
	cout << "starting" << endl;
	testall();
	return 0;
}


/**
#R code

*/