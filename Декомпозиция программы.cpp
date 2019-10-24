#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <cassert>

using namespace std;


enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	// Реализуйте эту функцию
	string cmd;
	is >> cmd;
	if (cmd == "NEW_BUS") {
		q.stops.clear();
		string Bus;
		int stops_count;
		vector<string> Stops;
		q.type = QueryType::NewBus;
		is >> Bus;
		q.bus = Bus;
		is >> stops_count;
		while (stops_count > 0) {
			--stops_count;
			is >> q.stop;
			Stops.push_back(q.stop);
		}
		q.stops = Stops;
	}
	else if (cmd == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (cmd == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (cmd == "ALL_BUSES")
	{
		q.type = QueryType::AllBuses;
	}
	return is;
}

struct BusesForStopResponse {
	// Наполните полями эту структур
	vector<string> Buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	// Реализуйте эту функцию
	if (r.Buses.size() == 0) {
		os << "No stop";
	}
	else {
		for (const auto& item : r.Buses) {
			os << item << " ";
		}
	}
	return os;
}

struct StopsForBusResponse {
	// Наполните полями эту структуру
	vector<string> Stops;
	map<string, vector<string>> Buses;
	string Nobus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	// Реализуйте эту функцию
	int i = 0;
	if (r.Nobus.size() != 0) {
		os << "No bus";
		return os;
	}
	for ( auto& item : r.Stops) {
		os << "Stop " << item << ": ";
		i++;
		for ( auto& i: r.Buses.at(item)){
			os << i << " ";
		}
		if(i!=r.Stops.size()){ cout << endl; }
	}
	
	return os;
}

struct AllBusesResponse {
	// Наполните полями эту структуру
	map<string, vector<string>> Buses;
	
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	// Реализуйте эту функцию
	int i = 0;
	if (r.Buses.empty()) {
		os << "No buses";
	}
	else {
		for (const auto& bus_item : r.Buses) {
			os << "Bus " << bus_item.first << ": ";
			i++;
			for (const string& stop : bus_item.second) {
				os << stop << " ";
			}
			if (i != r.Buses.size()) { cout << endl; }
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		// Реализуйте этот метод
		buses_to_stops[bus] = stops;
		for (const string& stop : stops) {
			stops_to_buses[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		// Реализуйте этот метод
		BusesForStopResponse r;
		if (stops_to_buses.count(stop) == 0) {
			return r;
		}
		for (const string& bus : stops_to_buses.at(stop)) {
			r.Buses.push_back(bus);
		}
		
		return r;
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const{
		// Реализуйте этот метод
		StopsForBusResponse r;
		if (buses_to_stops.count(bus) == 0) {
			r.Nobus = "No bus";
			return r;
		}
		else {
			for (auto& stop : buses_to_stops.at(bus)) {
				r.Stops.push_back(stop);
				if (stops_to_buses.at(stop).size() == 1) {
					r.Buses[stop].push_back("no interchange");
				}
				else {
					for (auto& other_bus : stops_to_buses.at(stop)) {
						if (bus != other_bus) {
							r.Buses[stop].push_back(other_bus);
						}
					}
				}
			}
		}
		return r;
	}

	AllBusesResponse GetAllBuses() const {
		// Реализуйте этот метод
		AllBusesResponse r;
		for (const auto& item : buses_to_stops) {
			r.Buses[item.first] = item.second;
		}
		return r;
	}
private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше
int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}
	return 0;
}