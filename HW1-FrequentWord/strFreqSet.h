#pragma once
#ifndef STRFREQSET_H
#define STRFREQSET_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class StringFSet {
	private:
		vector<string> words;
		vector<size_t> freq;
	public:
		StringFSet();
		void add(string s);
		bool check(string s);
		void remove(string s);
		vector<string> mostFreq();

};
#endif // !STRFREQSET_H