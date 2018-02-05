#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <regex>
#include <cctype>
#include <limits>
#include <fstream>
#include "strFreqSet.h"

//#include <stdlib.h>

using namespace std;

//  [[Rcpp::export]]
void OriginWraper(string s) {

}
//  [[Rcpp::export]]
void FreqWrapper(string s) {
	
}

string removePunc(string str) {
	for (string::iterator itr = str.begin(); itr != str.end(); ++itr) {

		if (*itr == '.' || *itr == '?' || *itr == '!' || *itr == '-' || *itr == ',' || *itr == '\'' ) {
			string::iterator itr1 = itr;
			if ((++itr1) == str.end()) {
				str.erase(itr);
				break;
			}
			str.erase(itr);

		}
		else if (isupper(*itr)) {
			*itr = tolower(*itr);
		}
	}
	return str;
}

vector<string> StringtoWords(string str) {
	vector<string> freq = vector<string>();
	for (size_t s = 0; s < str.length(); s++) {
		for (size_t e = s; e < str.length(); e++) {
			char cur = str[e];
			if (cur == ' ') {
				freq.push_back(str.substr(s, e - s) );
				s = e+1;
			}
		}
	}
	return freq;
}

vector<string> FrequentWords(string filename, int wordlen) {
	fstream iFile;
	string l;
	string Lines;
	iFile.open(filename, ifstream::in);
	if (iFile.is_open()) {
		while (!iFile.eof()) {
			getline(iFile, l);
			Lines = Lines + " " + l;
		}
	}
	iFile.close();
	vector<string> words = StringtoWords(removePunc(Lines));
	StringFSet frequency = StringFSet();
	string len;
	stringstream strS;
	strS << wordlen;
	len = strS.str();
	//regex r("[a-zA-Z]{2}");
	regex r("[a-zA-Z]{" + len + "}");
	for (vector<string>::iterator itr = words.begin(); itr != words.end(); ++itr) {
		bool match = regex_match(*itr, r);
		if (match) {
			frequency.add(*itr);
		}
	}
	return frequency.mostFreq();
}

size_t FindOrigin(string filename){
	fstream iFile;
	string l;
	string Lines;
	iFile.open(filename, ifstream::in);
	if (iFile.is_open()) {
		while (!iFile.eof()) {
			getline(iFile, l);
			Lines = Lines + l;
		}
	}
	iFile.close();

	size_t Cnum = 0, Gnum = 0;
	int Clow = numeric_limits<int>::max(), GHigh = numeric_limits<int>::min();
	size_t CLowIndex = 0 , GHighIndex = 0;
	char cur;
	for (size_t i = 0; i < Lines.length(); i++) {
		cur = Lines[i];
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

	//testiing Word Frequency
	//test 1;
	vector<string> most = FrequentWords("FreqWordTest1.txt", 2);
	cout << "Test 1" << endl;
	cout << "Correct Answer:" << endl;
	cout << "\tmost Common word(s): \"he\"" << endl ;
	for (vector<string>::iterator itr = most.begin(); itr != most.end(); ++itr) {
		cout << *itr << ", ";
	}
	cout << endl;

	//test 2
	most = FrequentWords("FreqWordTest2.txt", 3);
	cout << "Test 2" << endl;
	cout << "Correct Answer:" << endl;
	cout << "\tmost Common word(s): \"the\"" << endl;
	for (vector<string>::iterator itr = most.begin(); itr != most.end(); ++itr) {
		cout << *itr << ", ";
	}
	cout << endl;
	//test 3
	most = FrequentWords("FreqWordTest3.txt", 4);
	cout << "Test 3" << endl;
	cout << "Correct Answer:" << endl;
	cout << "\tmost Common word(s): \"loud\"" << endl;
	for (vector<string>::iterator itr = most.begin(); itr != most.end(); ++itr) {
		cout << *itr << ", ";
	}
	cout << endl;
	//test 4
	most = FrequentWords("FreqWordTest4.txt", 5);
	cout << "Test 4" << endl;
	cout << "Correct Answer:" << endl;
	cout << "\tmost Common word(s): \"quiet\"" << endl;
	for (vector<string>::iterator itr = most.begin(); itr != most.end(); ++itr) {
		cout << *itr << ", ";
	}
	cout << endl;

	//test 5
	most = FrequentWords("FreqWordTest5.txt", 6);
	cout << "Test 5" << endl;
	cout << "Correct Answer:" << endl;
	cout << "\tmost Common word(s): \"eldest\"" << endl;
	for (vector<string>::iterator itr = most.begin(); itr != most.end(); ++itr) {
		cout << *itr << ", ";
	}
	cout << endl;
	/*
	//testing origin finder

	//test 1
	cout << "Possable origin Location: " << FindOrigin("DNAOrigin1.txt") << endl;
	//test 2
	cout << "Possable origin Location: " << FindOrigin("DNAOrigin1.txt") << endl;
	//test 3
	cout << "Possable origin Location: " << FindOrigin("DNAOrigin1.txt") << endl;
	//test 4
	cout << "Possable origin Location: " << FindOrigin("DNAOrigin1.txt") << endl;
	//test 5
	cout << "Possable origin Location: " << FindOrigin("DNAOrigin1.txt") << endl;
	*/
	}

int main() {
	cout << "starting" << endl;
	testall();
	return 0;
}


/** R


*/