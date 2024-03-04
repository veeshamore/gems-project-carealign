#ifndef USER_DETAILS_HPP
#define USER_DETAILS_HPP

#include <iostream>
#include<mysql.h>
#include<mysqld_error.h>
using namespace std;

class User_Details {
	
private:
    string Password;
protected:
    string Username;
    int Role;
    string First_name;
    string Last_name;
    int Age;
    string Gender;
    string Blood_group;
    long long Ph_no;

public:
	
	string getUsername() {
		return Username;
	}
	
	void setUsername(string username) {
		Username = username;
	}
	
	string getPassword() {
		return Password;
	}
	
	void setPassword(string password) {
		Password = password;
	}
	
	int getRole() {
		return Role;
	}
	
	void setRole(int role) {
		Role = role;
	}
	
	string getFirst_name() {
		return First_name;
	}
	
	void setFirst_name(string first_name) {
		First_name = first_name;
	}
	
	string getLast_name() {
		return Last_name;
	}
	
	void setLast_name(string last_name) {
		Last_name = last_name;
	}
	
	string getGender() {
		return Gender;
	}
	
	void setGender(string gender) {
		Gender = gender;
	}
	
	int getAge() {
		return Age;
	}
	
	void setAge(int age) {
		Age = age;
	}
	
	long long getPh_no() {
		return Ph_no;
	}
	
	void setPh_no(long long ph_no) {
		Ph_no = ph_no;
	}
	
	string getBlood_group() {
		return Blood_group;
	}
	
	void setBlood_group(string blood_group) {
		Blood_group = blood_group;
	}

	bool isUsernameAvailable(MYSQL* conn, const string& username);
	bool addInUser_Details(MYSQL* conn, User_Details* user);
    bool login(MYSQL* conn, User_Details* user);
    
    //bool signup(const string& username, const string& password, const string& p_fname, const string& p_lname, const char& gender, const long& ph_no, const string& blood_group, const string& location);
};

#endif // USER_DETAILS_HPP
