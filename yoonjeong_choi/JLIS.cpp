#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class JLIS {
private:
	vector<int> A,B;
	vector<vector<int>> cache;

	void setProblem(const vector<int>& a, const vector<int>& b) {
		A = vector<int>(a.size() + 1);
		B = vector<int>(b.size() + 1);
		A[0] = numeric_limits<int>::min();
		B[0] = numeric_limits<int>::min();

		copy(a.begin(), a.end(), A.begin()+1);
		copy(b.begin(), b.end(), B.begin()+1);

		// 캐시 초기화 -1
		cache = vector<vector<int>>(A.size(), vector<int>(B.size(), -1));
	}

	int DP(int aIdx, int bIdx) {
		// A[aIdx], B[bIdx]를 선택한다고 가정
		// A[aIdx], B[bIdx]보다 큰 값을 A or B 수열에서 뽑아야 한다

		if (aIdx == A.size() || bIdx == B.size()) {
			return 0;
		}
		
		int& ret = cache[aIdx][bIdx];
		if (ret != -1) {
			return ret;
		}

		ret = 2;

		int maxElement = max(A[aIdx], B[bIdx]);

		// Case 1 : A에서 뽑는다
		for (int i = aIdx + 1; i < A.size(); i++) {
			if (A[i] > maxElement) {
				ret = max(ret, 1 + DP(i, bIdx));
			}
		}

		// Case 2 : B에서 뽑는다
		for (int i = bIdx + 1; i < B.size(); i++) {
			if (B[i] > maxElement) {
				ret = max(ret, 1 + DP(aIdx, i));
			}
		}
		
		return ret;
	}

	int solveProblem(const vector<int>& A, const vector<int>& B) {
		setProblem(A, B);

		int ret = DP(0, 0) - 2; // 2개는 dummy 데이터이므로
		return ret;
	}

public:
	void MAIN() {
		int C;
		int n, m;
		vector<int> sol;

		cout << "Test Case : "; cin >> C;
		sol.resize(C);

		for (int i = 0; i < C; i++) {
			cout << "Size : "; 
			cin >> n >> m;
			vector<int> A(n);
			vector<int> B(m);

			for (int j = 0; j < n; j++) {
				cin >> A[j];
			}

			for (int j = 0; j < m; j++) {
				cin >> B[j];
			}

			sol[i] = solveProblem(A, B);
		}

		for (int i = 0; i < C; i++) {
			cout << sol[i] << endl;
		}
	}

	void example() {
		vector<int> a1 = { 1,2,4 };
		vector<int> b1 = { 3,4,7 };
		vector<int> a2 = { 1,2,3 };
		vector<int> b2 = { 4,5,6 };
		vector<int> a3 = { 10,20,30,1,2 };
		vector<int> b3 = { 10,20,30 };
		vector<int> a4 = { 7,1,2,3,4,5,6 };
		vector<int> b4 = { 2,3,4, };

		cout << solveProblem(a1, b1) << endl;
		cout << solveProblem(a2, b2) << endl;
		cout << solveProblem(a3, b3) << endl;
		cout << solveProblem(a4, b4) << endl;
	}
};


int main() {
	JLIS j;
	j.MAIN();
	return 0;
}