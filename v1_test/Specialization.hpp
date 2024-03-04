#ifndef SPECIALIZATION_HPP
#define SPECIALIZATION_HPP

#include <bits/stdc++.h>
#include<mysql.h>
#include<mysqld_error.h>
using namespace std;

class Specialization {
protected:
    int Spec_id;
    string Spec_name;

public:
	Specialization();
	
	int getSpec_id() {
		return Spec_id;
	}
	
	void setSpec_id(int spec_id) {
		Spec_id = spec_id;
	}
	
	string getSpec_name() {
		return Spec_name;
	}
	
	void setSpec_name(string spec_name) {
		Spec_name = spec_name;
	}
	
	vector<pair<int, string>> displaySpecList(MYSQL* conn);

    
};

#endif // SPECIALIZATION_HPP
