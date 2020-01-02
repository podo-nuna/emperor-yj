#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class PI {
private:
	const int MAXINF = 987654321;
	vector<int> numbers;
	vector<int> cache;

	void setProblem(const string& numberStr) {
		numbers.clear();
		numbers.reserve(numberStr.length());

		for (int i = 0; i < numberStr.length(); i++) {
			numbers.push_back(atoi(numberStr.substr(i, 1).c_str()));
		}

		cache = vector<int>(numbers.size(), -1);
	}

	// 난이도 관련 함수들 : [start, end) 배열에 대한 함수들
	bool isAllSame(int start,int end) {

		for (int i = start+1; i < end; i++) {
			if (numbers[start] != numbers[i]) {
				return false;
			}
		}
		return true;
	}

	bool isMonotoneDeg1(int start, int end){
		int dist = numbers[start + 1] - numbers[start];

		if (dist != -1 && dist != 1) {
			return false;
		}

		for (int i = start + 1; i < end-1; i++) {
			if (dist != numbers[i + 1] - numbers[i]) {
				return false;
			}
		}
		return true;
	}

	bool isAlternating(int start, int end) {
		int first = numbers[start];
		int second = numbers[start + 1];

		for (int i = 2; i < end-start; i++) {
			if (i % 2 == 0 && numbers[start+i] != first) {
				return false;
			}
			if (i % 2 == 1 && numbers[start+i] != second) {
				return false;
			}
		}

		return true;
	}

	bool isArithmeticSeq(int start, int end) {
		int dist = numbers[start + 1] - numbers[start];

		for (int i = start + 1; i < end-1; i++) {
			if (dist != numbers[i + 1] - numbers[i]) {
				return false;
			}
		}
		return true;
	}

	int getDifficulty(int start, int end) {
		if (isAllSame(start, end)) {
			return 1;
		}
		else if (isMonotoneDeg1(start, end)) {
			return 2;
		}
		else if (isAlternating(start, end)) {
			return 4;
		}
		else if (isArithmeticSeq(start, end)) {
			return 5;
		}
		else {
			return 10;
		}
	}

	int DP(int start) {
		// numbers[start:]에 대한 subproblem

		// Base Case : 남은 숫자가 0개 인경우
		if (start == numbers.size()) {
			return 0;
		}

		int& ret = cache[start];
		if (ret != -1) {
			return ret;
		}

		ret = MAXINF;

		// 숫자를 3~5개를 골라서 난이도 테스트
		for (int i = 3; i <= 5; i++) {
			if (start + i <= numbers.size()) {
				ret = min(ret, getDifficulty(start, start + i) + DP(start + i));
			}
		}
		return ret;
	}

	int solveProblem(const string& str) {
		setProblem(str);
		return DP(0);

	}
public:
	void MAIN() {
		int C;
		cout << "Test Case : "; cin >> C;
		vector<int> sol(C);
		string inputStr;

		for (int i = 0; i < C; i++) {
			cin >> inputStr;
			sol[i] = solveProblem(inputStr);
		}

		for (int i = 0; i < C; i++) {
			cout << sol[i] << endl;
		}
	}
	
	void example() {
		string v1 = "12341234";
		string v2 = "11111222";
		string v3 = "12122222";
		string v4 = "22222222";
		string v5 = "12673939";

		cout << solveProblem(v1) << endl;
		cout << solveProblem(v2) << endl;
		cout << solveProblem(v3) << endl;
		cout << solveProblem(v4) << endl;
		cout << solveProblem(v5) << endl;
	}
};

int main() {
	PI p;
	p.MAIN();
	return 0;
}