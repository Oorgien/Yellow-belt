#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <set>
#include <map>
#include<deque>

using namespace std;
enum class OperationType {
	CONCAT,
	MULTIPLY,
	DIVISION,
	MINUS
};
struct operation {
	OperationType Type;
	int x;
	deque<string> res;
};



istream& operator>>(istream& is, operation& op) {
	char oper;
	is >> oper;
	if (oper == '+') {
		op.Type = OperationType::CONCAT;
	}
	else if (oper == '*') {
		op.Type = OperationType::MULTIPLY;
	}
	else if (oper == '-') {
		op.Type = OperationType::MINUS;
	}
	else if (oper == '/') {
		op.Type = OperationType::DIVISION;
	}
	int y;
	is >> y;
	op.x = y;
	return is;
}

void MakeOperation(operation& op) {
	switch (op.Type) {
	case OperationType::CONCAT:
		op.res.push_back(" + "+to_string(op.x));
		break;
	case OperationType::DIVISION:
		op.res.push_back(" / " + to_string(op.x));
		break;
	case OperationType::MULTIPLY:
		op.res.push_back(" * " + to_string(op.x));
		break;
	case OperationType::MINUS:
		op.res.push_back(" - " + to_string(op.x));
		break;
	}
}

deque<string> DequeParse(deque<string>& d) {
	deque<string> res;
	for (auto it = begin(d); it != end(d); it++) {
		if (it == begin(d)) res.push_back(*it);
		else {
			auto act = (*it)[1];
			auto prev = (*(it - 1))[1];
			bool flag = (prev == '+' || prev == '-') && (act == '*' || act == '/');
			if (flag == true) {
				res.push_front("(");
				res.push_back(")" + *it);
			}
			else res.push_back(*it);
		}
	}
	return res;
}

ostream& operator<< (ostream& os,const deque<string>& d) {
	for (auto it = begin(d); it != end(d); it++) {
		os << *it;
	}
	return os;
}

int main() {
	int x;
	cin >> x;
	int n;
	cin >> n;
	operation op;
	op.res.push_front(to_string(x));
	while (n > 0) {
		cin >> op;
		MakeOperation(op);
		n--;
		//deque<string> d = DequeParse(op.res);
		//cout << d;
	}
	deque<string> d = DequeParse(op.res);
	cout << d;
	return 0;
}