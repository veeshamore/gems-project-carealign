#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "Patient.hpp"

using namespace std;

Patient::Patient() {
	Patient_id = 0;
}

//bool Patient::isUsernameAvailable(MYSQL* conn, const string& username) {
//	string checkUsername = "SELECT * FROM user_details WHERE username = '" + username + "'";
//	if(mysql_query(conn,checkUsername.c_str())) {
//		cout<<"Error: "<<mysql_error(conn)<<endl;
//		return true;
//	}
//	
//	else {
//		MYSQL_RES* res ;
//		res = mysql_store_result(conn);
//		
//		if(res) {
//			MYSQL_ROW row;
//			row = mysql_fetch_row(res);
//			
//			if(row == 0){
//				mysql_free_result(res);
//				return true;
//			}
//			mysql_free_result(res);
//			return false;
//		}
//	
//	}
//}
//
//bool Patient::addInUser_Details(MYSQL* conn, const string& username, const string& password) {
//	string insertQuery = "INSERT INTO user_details (username, password, role_id) VALUES ('"+ username +"', '"+ password +"',4)"; 
//	if(mysql_query(conn, insertQuery.c_str())){
//		cout << mysql_error(conn) << endl;
//		return false;
//	}
//	else{
//		cout << "Data inserted.." << endl;
//		return true;
//	}
//}

bool Patient::addInPatient(MYSQL* conn, Patient* p) 
{
//	stringstream s_age;
//	s_age << p.getAge();
//	string sAge = s_age.str();
//	
//	string sPh_no = to_string(p.getPh_no());
	
	string insertQuery = "INSERT INTO Patient (username,p_fname,p_lname,age,gender,ph_no,blood_group) VALUES ('"+p->getUsername()+"','"+p->getFirst_name()+"','"+p->getLast_name()+"','"+to_string(p->getAge())+"','"+p->getGender()+"','"+to_string(p->getPh_no())+"','"+p->getBlood_group()+"')"; 
	if(mysql_query(conn, insertQuery.c_str())){
		cout << mysql_error(conn) << endl;
		return false;
	}
	else{
		cout << "Data inserted in Patient table..." << endl;
		return true;
	}
}

int Patient::retrievePatient_Id(MYSQL* conn, const std::string& username) {
	string retrieveQuery = "SELECT patient_id FROM Patient where username ='" + username +"'";
	if(mysql_query(conn,retrieveQuery.c_str())) {
		cout<<"Error: "<<mysql_error(conn)<<endl;
		return 0;
	}
	
	else {
		MYSQL_RES* res ;
	 	res = mysql_store_result(conn);
	 	if(res){
		 	int num = mysql_num_fields(res);
//		 	cout <<"num = " << num << endl;
		 	MYSQL_ROW row;
		 	row=mysql_fetch_row(res);
		 	
		 	string myString(row[0]);
		 	int n = stoi(myString);
//		 	cout << "n = " << n << endl;
		 	mysql_free_result(res);
		 	return n;
		}
	}
}

Patient Patient::retrievePatientDetail(MYSQL* conn, int patient_id) {
	string retrieveQuery = "select * from Patient where patient_id = " + to_string(patient_id);
	if(mysql_query(conn,retrieveQuery.c_str())) {
			Patient patient;
			cout<<"Error: "<<mysql_error(conn)<<endl;
			return patient;
	}
	
	else 
	{
		Patient patient;
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		
		MYSQL_ROW row;
		row = mysql_fetch_row(res);
		
		patient.setPatient_id(patient_id);
		string uname(row[1]);
		patient.setUsername(uname);
		string fname(row[2]);
		patient.setFirst_name(fname);
		string lname(row[3]);
		patient.setLast_name(lname);
		string gender(row[4]);
		patient.setGender(gender);
		string ph(row[5]);
		patient.setPh_no(stoll(ph, nullptr, 10));
		string bgroup(row[6]);
		patient.setBlood_group(bgroup);
		string age(row[7]);
		patient.setAge(stoi(age));
		
		return patient;
	}
}
