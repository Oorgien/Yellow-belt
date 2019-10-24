#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <utility>
#include <exception>
#include <stdexcept>
#include <set>
using namespace std;




template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

class Rational {
public:
	Rational() {
		// Реализуйте конструктор по умолчанию
		Num = 0;
		Denom = 1;
	}

	Rational(int numerator, int denominator) {
		// Реализуйте конструктор
		if (denominator == 0) throw invalid_argument("Invalid argument");
		int res;
		Num = numerator;
		Denom = denominator;
		int a = abs(numerator);
		int b = abs(denominator);
		while (a > 0 && b > 0) {
			if (a > b) {
				a %= b;
			}
			else {
				b %= a;
			}
		}
		res = a + b;
		Num /= res;
		Denom /= res;
		if (denominator < 0) {
			Num = -Num;
			Denom = -Denom;
		}
	}

	int Numerator() const {
		// Реализуйте этот метод
		return Num;
	}

	int Denominator() const {
		// Реализуйте этот метод
		return Denom;
	}
private:
	int Num;// Добавьте поля
	int Denom;
};

// реализация ==, - , +
Rational operator+ (const Rational& lhs, const Rational& rhs) {
	int a = lhs.Numerator() * rhs.Denominator();//левый числитель
	int b = rhs.Numerator() * lhs.Denominator(); // правый числитель
	int c = lhs.Denominator() * rhs.Denominator();//общий знаменатель
	return Rational(a + b, c);
}

Rational operator- (const Rational& lhs, const Rational& rhs) {
	int a = lhs.Numerator() * rhs.Denominator();//левый числитель
	int b = rhs.Numerator() * lhs.Denominator(); // правый числитель
	int c = lhs.Denominator() * rhs.Denominator();//общий знаменатель
	return Rational(a - b, c);
}

bool operator== (const Rational& lhs, const Rational& rhs) {
	int a = lhs.Numerator() * rhs.Denominator();//левый числитель
	int b = rhs.Numerator() * lhs.Denominator(); // правый числитель
	int c = lhs.Denominator() * rhs.Denominator();//общий знаменатель
	return a == b;
}

Rational operator* (const Rational& lhs, const Rational& rhs) {
	int a = lhs.Numerator() * rhs.Numerator();
	int b = lhs.Denominator() * rhs.Denominator();
	return Rational(a, b);
}

Rational operator/ (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) throw domain_error("Division by zero");
	int a = lhs.Numerator() * rhs.Denominator();
	int b = lhs.Denominator() * rhs.Numerator();
	return Rational(a, b);
}


ostream& operator<<(ostream& stream, const Rational& r) {
	stream << r.Numerator() << "/" << r.Denominator();
	return stream;
}

istream& operator>>(istream& stream, Rational& r) {
	int a, b;
	if (stream.tellg() == -1) {
		return stream;
	}
	else {
		stream >> a;
		stream.ignore(1);
		stream >> b;
		r = { a,b };
		return stream;
	}
}

bool operator< (const Rational& lhs, const Rational& rhs) {
	int a = lhs.Numerator() * rhs.Denominator();//левый числитель
	int b = rhs.Numerator() * lhs.Denominator(); // правый числитель
	int c = lhs.Denominator() * rhs.Denominator();//общий знаменатель
	return a < b;
}

void TestDivision() {
	Assert(Rational{ 2,3 } == Rational{ 4,6 }, "");
	Assert(Rational{ 4,9 } == Rational{ 8,18 }, "");
	Assert(Rational{ 5,9 } == Rational{ 5,9 }, "");
	Assert(Rational{ 2'147'483'647, 2'147'483'647 } == Rational{ 1,1 }, "");
	Assert(Rational{ 6,3 } == Rational{ 2,1 }, "");
	Assert(Rational{ -6,-3 } == Rational{ 2,1 }, "");
	Assert(Rational{ -0,-3 } == Rational{ 0,1 }, "");
}
void First() {
	Assert(Rational{ } == Rational{ 0,1 }, "");
}
void Third() {
	Assert(Rational{ -2,4 } == Rational{ -1,2 }, "");
	Assert(Rational{ 1,-2 } == Rational{ -1,2 }, "");
	Assert(Rational{ -2'147'483'647,1 } == Rational{ -2'147'483'647, 1 }, "");
	Assert(Rational{ -2'147'483'647, -2'147'483'647 } == Rational{ 1,1 }, "");
}

void Forth() {
	Assert(Rational{ -2,-4 } == Rational{ 1,2 }, "");
}

void Fifth() {
	Assert(Rational{ 0,9 } == Rational{ 0,1 }, "");
	Assert(Rational{ 0,-9 } == Rational{ 0,1 }, "");
	Assert(Rational{ 0,-1 } == Rational{ 0,1 }, "");
}

int main() {
	TestRunner runner;
	runner.RunTest(First, "Test first case");
	runner.RunTest(TestDivision, "The second case");
	runner.RunTest(Third, "The third case");
	runner.RunTest(Forth, "The forth case");
	runner.RunTest(Fifth, "The fifth case");
	// добавьте сюда свои тесты
	return 0;
}



