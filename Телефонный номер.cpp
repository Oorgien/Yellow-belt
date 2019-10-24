#include<string>
#include<algorithm>
#include<vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <stdexcept>
using namespace std;

bool CheckPhone(const string& international_number) {
	istringstream phone_stream(international_number);
	bool flag = true;
	
	string country_code;
	char c; 
	phone_stream.get(c);
	flag = flag && (c == '+');
	flag = flag && (getline(phone_stream, country_code, '-'));

	string city_code;
	flag = flag && (getline(phone_stream, city_code, '-'));

	string local_number;
	flag = flag && (phone_stream >> local_number);
	return flag;
}

class PhoneNumber {
public:
	/* Принимает строку в формате +XXX-YYY-ZZZZZZ
	   Часть от '+' до первого '-' - это код страны.
	   Часть между первым и вторым символами '-' - код города
	   Всё, что идёт после второго символа '-' - местный номер.
	   Код страны, код города и местный номер не должны быть пустыми.
	   Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

	   Примеры:
	   * +7-495-111-22-33
	   * +7-495-1112233
	   * +323-22-460002
	   * +1-2-coursera-cpp
	   * 1-2-333 - некорректный номер - не начинается на '+'
	   * +7-1233 - некорректный номер - есть только код страны и города
	*/
	PhoneNumber(const string& international_number) {
		istringstream phone_stream(international_number);
		bool flag = true;

		string country_code;
		char c;
		phone_stream.get(c);
		flag = flag && (c == '+');
		flag = flag && (getline(phone_stream, country_code, '-'));

		string city_code;
		flag = flag && (getline(phone_stream, city_code, '-'));

		string local_number;
		flag = flag && (phone_stream >> local_number);

		if (!flag)
		{
			throw invalid_argument("Wrong phone format: " + international_number);
		}
		country_code_ = country_code;
		city_code_ = city_code;
		local_number_ = local_number;

	}

	string GetCountryCode() const {
		return country_code_;
	}
	string GetCityCode() const {
		return city_code_;
	}
	string GetLocalNumber() const {
		return local_number_;
	}
	string GetInternationalNumber() const {
		return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
	}
private:
	string country_code_;
	string city_code_;
	string local_number_;

};

/*
int main() {
	try {
		string phone;
		cin >> phone;
		PhoneNumber p(phone);
		cout << p.GetCityCode() << endl<< p.GetCountryCode() << endl << p.GetLocalNumber() << endl << p.GetInternationalNumber();
	}
	catch (invalid_argument& i) {
		cout << i.what();
	}
	return 0;
}
*/

