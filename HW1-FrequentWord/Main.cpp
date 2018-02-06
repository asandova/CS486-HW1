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

size_t FindOrigin(string filename);
vector<string> FrequentWords(string filename, int wordlen);
//  [[Rcpp::export]]
void OriginWraper(string s) {
	FindOrigin(s);
}
//  [[Rcpp::export]]
void FreqWrapper(string s) {
	FrequentWords(s, 3);
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
	cout << "\tmost Common word(s): \"he\"" << endl;
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

	//testing origin finder
	size_t location;
	//test 1
	location = FindOrigin("DNAOrigin1.txt");
	cout << "Test 1:\nPossable origin Location: " << location << endl;
	if (location == 503) {
		cout << "Test 1: Passed" << endl;
	}
	else {
		cout << "Test 1: Failed" << endl;
	}
	//test 2
	location = FindOrigin("DNAOrigin2.txt");
	cout << "Possable origin Location: " << location << endl;
	if (location == 0) {
		cout << "Test 2: Passed" << endl;
	}
	else {
		cout << "Test 2: Failed" << endl;
	}
	//test 3
	location = FindOrigin("DNAOrigin3.txt");
	cout << "Possable origin Location: " << location << endl;
	if (location == 7) {
		cout << "Test 3: Passed" << endl;
	}
	else {
		cout << "Test 3: Failed" << endl;
	}
	//test 4
	location = FindOrigin("DNAOrigin4.txt");
	cout << "Possable origin Location: " << location << endl;
	if (location == 5) {
		cout << "Test 4: Passed" << endl;
	}
	else {
		cout << "Test 4: Failed" << endl;
	}
	//test 5
	location = FindOrigin("DNAOrigin5.txt");
	cout << "Possable origin Location: " << location << endl;
	if (location == 11) {
		cout << "Test 5: Passed" << endl;
	}
	else {
		cout << "Test 5: Failed" << endl;
	}
}

int main() {
	cout << "starting" << endl;
	testall();
	return 0;
}


/** R
freq.files <- c("FreqWordRTest1.txt","FreqWordRTest2.txt","FreqWordRTest3.txt","FreqWordRTest4.txt","FreqWordRTest5.txt")
word.num <- c(500,600,700,800,900)

runtime <- vector(lenght = 5)
for(i in c(1:5)){
	runtime[i] <- system.time( FreqWrapper(freq.files[i]) )["user.self"]
}
plot(word.num,runtime, type="b", xlab="word count", ylab = "runtime(seconds)")
*/