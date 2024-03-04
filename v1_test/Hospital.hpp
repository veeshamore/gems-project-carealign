#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP
#include <string>
#include<mysql.h>
#include<mysqld_error.h>
#include "Specialization.hpp"

using namespace std;

class Hospital : public Specialization {
private:
		
	int Hosp_id;
	string Hosp_name;
	string Hosp_location;

public:
	Hospital();	
	int getHosp_id() {
		return Hosp_id;
	}
	
	void setHosp_id(int hosp_id) {
		Hosp_id = hosp_id;
	}
	
	string getHosp_name() {
		return Hosp_name;
	}
	
	void setHosp_name(string hosp_name) {
		Hosp_name = hosp_name;
	}
	
	string getHosp_location() {
		return Hosp_location;
	}
	
	void setHosp_location(string hosp_location) {
		Hosp_location = hosp_location;
	}
	
	
	vector<vector<string>> displayHospitalList(MYSQL* conn, int spec_id);
	vector<pair<int, string>> displayWardList(MYSQL* conn);
};
#endif
