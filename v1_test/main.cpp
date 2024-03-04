#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <mysql.h>
#include <mysqld_error.h>
#include "User_Details.hpp"
#include "Patient.hpp"
#include "Specialization.hpp"
#include "Doctor.hpp"
#include "Appointment.hpp"
#include "Hospitalization.hpp"

using namespace std;

const char* HOST = "10.44.227.27";
const char* USER = "group8";
const char* PASSWD = "group8";
const char* DB = "carealign";

void login(MYSQL* conn, User_Details* user);
void signup(MYSQL* conn, User_Details* user, Patient* patient);
Doctor specializationWithoutLogin(MYSQL* conn, Specialization* spec);
void patientMenu(MYSQL* conn, Patient* p);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void patientMenu(MYSQL* conn, Patient* p) {
	int choice;
	cout << "--------------------------------------------------------" << endl << endl;
	cout << "\t\tHi " << p->getFirst_name() << " " << p->getLast_name() << "!" << endl;
	cout << "Please select an option from the following: " << endl;
	cout << "1. View Profile" << endl;
	cout << "2. Edit Profile" << endl;
	cout << "3. Search Doctors/Hospitals by Specialization" << endl;
	cout << "4. View Appointment History" << endl;
	cout << "5. Manage Appointment" << endl;
	cout << "6. Hospitalize" << endl;
	cout << "7. View Bed Booking History" << endl;
	
	cout << "Select an option (as Integer): ";
	cin >> choice;
	
	switch (choice) {
		case 1:			// Display Patient details
		{
			cout << "ID : " << p->getPatient_id() << endl;
			cout << "First Name : " << p->getFirst_name() << endl;
			cout << "Last Name : " << p->getLast_name() << endl;
			cout << "Age : " << p->getAge() << endl;
			cout << "Phone no. : " << p->getPh_no() << endl;
			cout << "Gender : " << p->getGender() << endl;
			cout << "Blood Group : " << p->getBlood_group() << endl;
			break;
		}
		
		case 2:			//Update Patient details
		{
			
			break;
		}
		
		case 3:			//Specialization with login
		{
			string dt, tim;
			Specialization spec;
			Appointment ap;
			Doctor doctor = specializationWithoutLogin(conn, &spec);
			
			cout << "Please enter a date for your appoinement (yyyy-mm-dd): ";
			cin >> dt;
			vector<string> bookedSlots = ap.findAvailableSlots(conn, dt, doctor.getDoctorId());
			cout << "Below are the available slots for Dr." << doctor.getFirst_name() << " " << doctor.getLast_name() << " on " << dt << endl;
			for(const auto &s : bookedSlots) {
		    	cout << s << endl;
			}
			
			cout << "Choose a time from above list for your appointment (hh:mm:ss) : ";
			cin >> tim;
			
			if(ap.bookAppointment(conn, p->getPatient_id(), doctor.getDoctorId(), doctor.getHosp_id(), dt, tim)) {
				cout << "Appointment Booked!" << endl;
				
			}
			break;
			
		}
		
		case 4:				//Appointment History
		{
			Appointment ap;
			vector<vector<string>> appointmentList = ap.viewAppointmentHistory(conn, p->getPatient_id());
			cout << "Appointment ID\tPatient Name\tDoctor Name\tHospital Name\tBooking Date\tBooking Time\tBed Suggestion" << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			
			for(const auto& vect : appointmentList) {
				for (string s : vect) {
	        		cout << s << "\t";
	    		}
	    		cout<<endl;
			}
			break;
		}
	
		case 6:				//Book a bed for particular day.
		{
			int ap_id, ward_id;
			Hospitalization hz;
			Appointment ap;
			cout << "Enter an Appointment ID: ";
			cin >> ap_id;
			ap = ap.retrieveAppointmentDetails(conn, ap_id);
			if(hz.checkBedSuggest(conn, ap.getAppointment_id())) {
				vector<pair<int, string>> ward_list = hz.displayWardList(conn);
				for(const auto& pr : ward_list) {
					cout << pr.first << ". " << pr.second << endl;
				}
				cout << "Enter ward of your choice (as integer): ";
				cin >> ward_id;
				string dt;
				cout << "Enter a date (yyyy-mm-dd): ";
				cin >> dt;
				
				int bed_id = hz.availableBeds(conn, &ap, ward_id, dt);
				if(bed_id) {
					char c;
					cout << "Bed(s) are Available in selected ward." << endl;
					cout << "Do you want to Book a Bed? (Y/N): ";
					cin >> c;
					
					if(c == 'Y' || c == 'y') {
						hz.book_a_bed(conn, bed_id, &ap, dt);
					}
					
				}
				
				else {
					cout << "Bed(s) are NOT Available in selected ward." << endl;
				}
			}
			break;
		}
		
		case 7:
		{
			
			break;
		}
	}
}

void doctorMenu(MYSQL* conn, Doctor* d) 
{
	int choice;
	cout << "--------------------------------------------------------" << endl << endl;
	cout << "\t\tHi " << d->getFirst_name() << " " << d->getLast_name() << "!" << endl;
	cout << "Please select an option from the following: " << endl;
	cout << "1. View Profile" << endl;
	cout << "2. Edit Profile" << endl;
	cout << "3. Recommend Hospitalization to Patient" << endl;
//	cout << "4. View Appointment History" << endl;
//	cout << "5. Manage Appointment" << endl;
//	cout << "6. View Bed Booking History" <<endl;
	
	cout << "Select an option (as Integer): ";
	cin >> choice;
	
	switch (choice) {
		case 1:			// Display Doctor details
		{
			cout << "ID : " << d->getDoctorId() << endl;
			cout << "First Name : " << d->getFirst_name() << endl;
			cout << "Last Name : " << d->getLast_name() << endl;
			cout << "Age : " << d->getAge() << endl;
			cout << "Phone no. : " << d->getPh_no() << endl;
			cout << "Gender : " << d->getGender() << endl;
			cout << "Blood Group : " << d->getBlood_group() << endl;
			break;
		}
		
		
		case 3:
		{
			int id, bed_suggest;
			Appointment ap;
			cout << "Enter the Appointment ID: ";
			cin >> id;
			cout << "Is bed recommended? (0 for NO, 1 for YES): ";
			cin >> bed_suggest;
			ap.bed_suggestion(conn, id, bed_suggest);
			break;
		}
	}
}

void login(MYSQL* conn, User_Details* user) 
{
	string username, password;
	int role;
	cout << "------------ Welcome to Login page ------------" << endl << endl;
	cout << "Following are the integer codes for different roles:" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Administrator" << endl;
    cout << "3. Doctor" << endl;
    cout << "4. Patient" << endl;
    cout << "Enter role (as integer): ";
    cin >> role;
    user->setRole(role);

    cout << "Enter username: ";
    cin >> username;
    user->setUsername(username);

    cout << "Enter password: ";
    cin >> password;
    user->setPassword(password);
    
    switch(role) 
	{
//    	case 1:
//    	{
//    		if (role == 1 && user.login(conn, user)) {
//	            cout << "Login successfull!" << endl;
//	            cout << user->getUsername() <<"'s Admin Dashboard" << endl;
////	            adminMenu();
//	        }
//	        else {
//	            cout << "Login failed. Please check your credentials and try again." << endl;
//	        }
//	        break;
//		}
//		
//		case 2:
//		{
//			if (role == 2 && user->login(conn, user)) {
//	            cout << "Login successfull!" << endl;
//	            cout << user->getUsername() <<"'s Administrator Dashboard" << endl;
////	            adminstratorMenu();
//	        }
//	        else {
//	            cout << "Login failed. Please check your credentials and try again." << endl;
//	        }
//	        break;
//		}
//		
		case 3:
		{
			if (role == 3 && user->login(conn, user)) {
	            cout << "Login successfull!" << endl;
	            cout << user->getUsername() <<"'s Doctor Dashboard" << endl;
	            Doctor d = d.retrieveDoctorDetail(conn, d.retrieveDoctor_Id(conn, user->getUsername()));
	            doctorMenu(conn, &d);
	        }
	        else {
	            cout << "Login failed. Please check your credentials and try again." << endl;
	        }
	        break;
		}
		
		case 4:
		{
			if (role == 4 && user->login(conn, user)) {
	            cout << "Login successfull!" << endl;
	            cout << user->getUsername() <<"'s Patient Dashboard" << endl;
	            Patient p = p.retrievePatientDetail(conn, p.retrievePatient_Id(conn, user->getUsername()));
	            
	            patientMenu(conn, &p);
	        }
	        else {
	            cout << "Login failed. Please check your credentials and try again." << endl;
	        }
	        break;
		}	
	}

}

void signup(MYSQL* conn, User_Details* user, Patient* patient)
{
	string username, password;
	cout << endl << "------------ Welcome to SignUp page ------------" << endl;
	cout << "Please SignUp as Patient." << endl;
	cout << "------------------------------" << endl;
	cout << "Create an username: ";
    cin >> username;
    while(!(user->isUsernameAvailable(conn, username)))
    {
    	cout <<endl << "This username is already taken. Please try some unique username." << endl;
    	cout << "Create an username: ";
    	cin >> username;
	}
	
	cout << "Create your Password: ";
	cin >> password;
	
	user->setUsername(username);
	user->setPassword(password);
	user->setRole(4);
	
	if(user->addInUser_Details(conn, user)) 
	{
	    patient->setUsername(username);
		string first_name, last_name, gender, blood_group;
		int age;
		long long ph_no;
		
    	cout << "Enter your First name: ";
    	cin >> first_name;
    	patient->setFirst_name(first_name);
    	
    	cout << "Enter your Last name: ";
    	cin >> last_name;
    	patient->setLast_name(last_name);
    	
    	cout << "Enter your Gender: ";
    	cin >> gender;
    	patient->setGender(gender);
    	
    	cout << "Enter your Age: ";
    	cin >> age;
    	patient->setAge(age);
    	
    	cout << "Enter your Phone number: ";
    	cin >> ph_no;
    	patient->setPh_no(ph_no);
    	
    	cout << "Enter your Blood Group: ";
    	cin >> blood_group;
    	patient->setBlood_group(blood_group);
    	
    	if(patient->addInPatient(conn, patient)) {
    		cout << "Account created successfully!" << endl;
    		cout << "You can now successfully Login to your account with your credentials." << endl;
    		login(conn, user);
//	        		cout << endl << patient.retrievePatient_Id(conn, patient.getUsername());
		}
		else {
			cout << "Error in adding into Patient table" << endl;
		}
		
	}
	else {
		cout << "Error in adding into User_Details table" << endl;
	}
}

Doctor specializationWithoutLogin(MYSQL* conn, Specialization* spec) 
{
	int spec_id, hosp_id, doc_id, choice;
	Doctor doctor;
	cout << endl << " - List of Available Specializations -" << endl;
	
	vector<pair<int, string>> pairVector = spec->displaySpecList(conn);
	
	for (const auto& pair : pairVector) {
		std::cout << pair.first << ". " << pair.second << std::endl;
	}
	
	cout << endl << endl << "Please select the specialization of your choice (as integer): ";
	cin >> spec_id;
	
	cout << endl << "1. Search By Hospital" << endl;
	cout << "2. Search Doctor by name" << endl;
	cout << "Please select from above options: ";
	cin >> choice;
	
	if(choice == 1)
	{
		cout << endl <<" - List of Hospitals with Location -" << endl;
		vector<vector<string>> hospitalList = doctor.displayHospitalList(conn, spec_id);
		for(const auto& vect : hospitalList) {
			for (string s : vect) {
        		cout << s << "\t";
    		}
    		cout<<endl;
		}
		
		cout << "Select the Hospital (as Integer): ";
		cin >> hosp_id;
		
		cout << endl << " - List of Doctors in selected Specialization and Hospital - " << endl;
		vector<vector<string>> display = doctor.searchDoctorByHospital(conn, spec_id, hosp_id);
		cout << endl << "ID\tName\t\tExperience\tDegree\tHospital_Name" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		for(const auto& vect : display)	{
			for (string s : vect) {
        		cout << s <<"\t";
    		}
    		cout<<endl;
		}
		
		cout << endl << "Please select a Doctor to proceed: " << endl;
		cin >> doc_id;
		return doctor.retrieveDoctorDetail(conn, doc_id);
	}
	else 
	{
		string name;
		cout << "Enter the name of Doctor: ";
		cin.ignore();
		getline(cin, name);
		cout << endl <<" - List of Doctors in selected Specialization -" << endl;
		vector<vector<string>> display = doctor.searchDoctorByName(conn, spec_id, name);
		cout << endl << "ID\tName\t\tExperience\tDegree\tHospital_Name" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------" << endl;
		for(const auto& vect : display)	{
			for (string s : vect) {
        		cout << s <<"\t";
    		}
			cout<<endl;
		}
		
		cout << endl << "Please select a Doctor to proceed: " << endl;
		cin >> doc_id;
		return doctor.retrieveDoctorDetail(conn, doc_id);
	}
}


int main(int argc, char** argv) {
	MYSQL* conn;
	conn = mysql_init(NULL);
	 
	if(!mysql_real_connect(conn, HOST, USER, PASSWD, DB, 3306, NULL,0)){
		cout << mysql_error(conn);
	}
	

	//------------------------------DATABASE CONNECTION SUCCESSFULL--------------------------------------------
	
	int choice;
	
    char ch = 'y';
    
    User_Details user;
    Patient patient;
    Specialization spec;
    Doctor doctor;
    int pat_id;
    
	cout << endl << "\t\tWelcome to CareAlign" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << endl << "Choose from the following:" << endl;
	cout << "1. Login" << endl;
	cout << "2. SignUp" << endl;
	cout << "3. Search by Specialization" << endl;
	
	cout << "Enter your choice: ";
    cin >> choice;
        
//    Appointment ap;
//    
//    vector<string> bookedSlots = ap.findAvailableSlots(conn, "2024-02-12", 16);
//    for(const auto &s : bookedSlots) {
//    	cout << s << endl;
//	}
//	
//	string dt, slot;
//	cout << "Enter date of your choice: ";
//	cin >> dt;
//	cout << "Enter slot of your choice: ";
//	cin >> slot;
//	ap.bookAppointment(conn, 20, 16, 7, dt, slot);
//    
//    pair<string, string> consult = ap.consultTime(conn, 1);
//    cout << consult.first << " " << consult.second << endl;
    
    
    switch(choice) 
	{
		case 1:   		//Login irrespective of your role
		{
			login(conn, &user);
			break;	
	    }
	    
	    
	    case 2:			//SignUp as a Patient Only
    	{
    		signup(conn, &user, &patient);
			break;
		}
		
		
		case 3:			//Specialization without Login
		{
			specializationWithoutLogin(conn, &spec);
			cout << endl << "\t !!! Please login to Book Appointments... !!!" << endl << endl;
    		login(conn, &user);
			break;
		}
	    	
	    default:
	    	cout << "Wrong option! Please type the correct number" << endl;
    }
	
	
	mysql_close(conn);
	return 0;
}
