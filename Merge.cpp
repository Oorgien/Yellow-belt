#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (distance(range_begin, range_end) < 2) return;
	else {
		vector<typename RandomIt::value_type> elements(range_begin, range_end);
		//vector<typename RandomIt::value_type> a, b;
		auto middle = begin(elements) + distance(begin(elements), end(elements)) / 2;
		/*a.assign(range_begin, middle);
		b.assign(middle, range_end);
		MergeSort(begin(a), end(a));
		MergeSort(begin(b), end(b));
		*/
		MergeSort(begin(elements), middle);
		MergeSort(middle,end(elements));
		std::merge(begin(elements), middle, middle, end(elements), range_begin);
	}
}

int main() {
	vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}