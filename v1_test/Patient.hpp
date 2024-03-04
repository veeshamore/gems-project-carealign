#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include<mysql.h>
#include<mysqld_error.h>
#include"User_Details.hpp"
using namespace std;

class Patient : public User_Details {
private:
    int Patient_id;

public:
	Patient();
	
//	string getUsername() {
//		return Username;
//	}
//	
//	void setUsername(string username) {
//		Username = username;
//	}
	
	int getPatient_id() {
		return Patient_id;
	}
	
	void setPatient_id(int patient_id) {
		Patient_id = patient_id;
	}
	
//	string getFirst_name() {
//		return First_name;
//	}
//	
//	void setFirst_name(string first_name) {
//		First_name = first_name;
//	}
//	
//	string getLast_name() {
//		return Last_name;
//	}
//	
//	void setLast_name(string last_name) {
//		Last_name = last_name;
//	}
//	
//	string getGender() {
//		return Gender;
//	}
//	
//	void setGender(string gender) {
//		Gender = gender;
//	}
//	
//	int getAge() {
//		return Age;
//	}
//	
//	void setAge(int age) {
//		Age = age;
//	}
//	
//	long long getPh_no() {
//		return Ph_no;
//	}
//	
//	void setPh_no(long long ph_no) {
//		Ph_no = ph_no;
//	}
//	
//	string getBlood_group() {
//		return Blood_group;
//	}
//	
//	void setBlood_group(string blood_group) {
//		Blood_group = blood_group;
//	}

	
//    bool login(const string& username, const string& password, const int& role);
//    bool isUsernameAvailable(MYSQL* conn, const std::string& username);
//    bool addInUser_Details(MYSQL* conn, const std::string& username, const std::string& password);
    bool addInPatient(MYSQL* conn, Patient* patient);
    int retrievePatient_Id(MYSQL* conn, const std::string& username);
    Patient retrievePatientDetail(MYSQL* conn, int patient_id);
//    bool update Patient (MYSQL* conn, Patient patient);
    

//    bool signup(MYSQL* conn, const string& username, const string& password,
//        const string& first_name, const string& last_name, const int& age, const string& gender, 
//		const long long& ph_no, const string&blood_group);
};

#endif // PATIENT_HPP
