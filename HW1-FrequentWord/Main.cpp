#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

vector<string> FrequentWord(string textSample, int wordlengh) {
	vector<string> FreqText = vector<string>();
	vector<int> FreqNum = vector<int>();
	//[a-zA-Z]{7}

}

int FindOrigin(string DNA){
	int Cnum = 0, Gnum = 0;
	int Clow = 0, GHigh = 0,
	int CLowIndex, GHighIndex;
	char cur;
	for (int i = 0; i < DNA.length; i++) {
		cur = DNA[i];
		if (cur == 'c' || cur == 'C') {
			Cnum++;
		}
		else if (cur == 'g' || cur == 'G') {
			Gnum++;
		}
		if (Gnum - Cnum < Clow) {
			Clow = Gnum - Cnum;
			CLowIndex = i;
		}
		else if (Gnum - Cnum > GHigh ) {
			GHigh = Gnum - Cnum;
			GHighIndex = i;
		}
	}
	return CLowIndex;
}

void testall() {
	string s = "Welcome to the unofficial encyclopedia for Virtual Villagers—the puzzling video game series created by Last Day of Work. This wiki currently has 1,877 pages, and 153 articles. The series consists of five games in which you have to help a group of villagers survive on the mysterious island of Isola. Along the way, you will solve interesting puzzles that will test your mind—whether it be harvesting food, breeding, or creating shelter—and learn different skills in order to survive! |}";
	FrequentWord(s, 9);
}

int main() {
	testall();
}