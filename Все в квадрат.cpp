#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <utility>
using namespace std;

template <typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second>& p1, const pair<First, Second>& p2) {
	First f = p1.first * p2.first;
	Second s = p1.second * p2.second;
	return { f, s };
}

template <typename T>
vector<T> operator*(const vector<T>& v1, const vector<T>& v2) {
	vector<T> res;
	for (size_t i = 0; i < v1.size(); i++) {
		T k = v1[i] * v2[i];
		res.push_back(k);
	}
	return res;
}

template <class Key, class Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
	map<Key, Value> result_map;
	for (const auto& item : m) {
		result_map[item.first] = item.second * item.second;
	}
	return result_map;
}

template <typename T>
T Sqr(const T x) {
	T y = x * x;
	return y;
}

template <typename T>
vector<T> Sqr(vector<T>& v1) {
	for (auto& item : v1) {
		item = Sqr(item);
	}
	return v1;
}

int main() {
	// Пример вызова функции
 	vector<map<int, vector<double>>> it = {
		{ {2, { 3, 4,5, 6.8 }}}, 
	{ {5, {6, 7, 0.01}} } 
	};
	Sqr(it);
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;
	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}

