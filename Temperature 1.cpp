

#include <iostream>
#include <vector>

using namespace std;

void PrintVector(vector<int> v) {
	for (auto item : v) {
		cout << item << " ";
	}
	cout << endl;
}

int main() {
	size_t N;
	int T;
	int64_t sum = 0;
	vector<int> temp, res;
	cin >> N;
	for (size_t i = 0; i < N; i++) {
		cin >> T;
		temp.push_back(T);
		sum += T;

	}
	sum = sum / static_cast<int64_t>(temp.size());
	for (size_t i = 0; i < N; i++) {
		if (temp[i] > sum) {
			res.push_back(i);
		}
	}
	cout << res.size() << endl;
	PrintVector(res);
	return 0;
}

