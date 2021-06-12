#pragma once
#include <iostream>
#include <string>
using namespace std;

class Crime {
	public:
		Crime(string, string, string, string, string, string);
		string getTypeCrime();
		string getDescription();
		string getDate();
		string getLat();
		string getLong();
	private:
		string TypeCrime;
		string Long;
		string Lat;
		string Date;
		string Id;
		string Description;
};

string Crime::getTypeCrime() {
	return this->TypeCrime;
}
string Crime::getLat() {
	return this->Lat;
}
string Crime::getLong() {
	return this->Long;
}
string Crime::getDescription() {
	return this->Description;
}
string Crime::getDate() {
	return this->Date;
}

Crime::Crime(string Id, string Type, string Long, string Lat, string Date, string Description) {
	this->Id = Id;
	this->TypeCrime = Type;
	this->Long = Long;
	this->Lat = Lat;
	this->Date = Date;
	this->Description = Description;
}