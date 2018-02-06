#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

size_t FindOrigin(string filename);

size_t FindOrigin(string filename) {
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
	size_t CLowIndex = 0, GHighIndex = 0;
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
		else if (GCDif > GHigh) {
			GHigh = (int)Gnum - (int)Cnum;
			GHighIndex = i;
		}
	}
	return CLowIndex;
}
/*
void testall() {
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
*/
/*
int main() {
	testall();
	return 0;
}*/