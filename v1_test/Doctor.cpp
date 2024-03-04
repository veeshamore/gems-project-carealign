#include <bits/stdc++.h>
#include <string>
#include <sstream>
#include "Doctor.hpp"
 
Doctor::Doctor(){
	doctor_id = 0;
}

vector<vector<string>> Doctor::searchDoctorByHospital(MYSQL* conn, int spec_id, int hosp_id)
{
	vector<vector<string>> displayList;
	
//	stringstream s_id;
//	s_id << spec_id;
//	string sID = s_id.str();
//	
//	stringstream h_id;
//	h_id << hosp_id;
//	string hID = h_id.str();
	
	string retrieveDoc = "select d.doctor_id, d.d_fname, d.d_lname, d.yoe, d.degree_name, h.hosp_name from Doctor d, Hospital h, Specialization s where (h.hosp_id = d.hosp_id) and (d.spec_id = s.spec_id) and (s.spec_id = '" + to_string(spec_id) + "') and (h.hosp_id ='"+ to_string(hosp_id) +"')";
	if(mysql_query(conn, retrieveDoc.c_str())){
		vector<string> childVector;
		cout << mysql_error(conn) << endl;
		childVector.push_back("NULL");
		displayList.push_back(childVector);
		return displayList;
	}
	else
	{
		MYSQL_RES* res ;
	 	res = mysql_store_result(conn);
	 	if(res){
		 	int num = mysql_num_fields(res);
		 	MYSQL_ROW row;
		 	while(row = mysql_fetch_row(res)) {
//		 		for(int i=0; i < num; i++) {
//		 			cout << row[i] << "\t";
				
				vector<string> childVector;
				string s_id(row[0]);
				string sFName(row[1]);
				string sLName(row[2]);
				string sYoe(row[3]);
				string sDegree(row[4]);
				string sHospName(row[5]);
				sFName = sFName + " " + sLName;
				
				childVector.insert(childVector.end(), {s_id, sFName, sYoe, sDegree , sHospName});
//				cout<< childVector[0] << " " << childVector[1];
				displayList.push_back(childVector);
//				cout<<endl;
			
			}
		}
		mysql_free_result(res);
		return displayList;
	}
}
 
vector<vector<string>> Doctor::searchDoctorBySpec(MYSQL* conn, int spec_id)
{
	vector<vector<string>> displayDoctorList;
//	stringstream s_id;
//	s_id << spec_id;
//	string sID = s_id.str();
	
	string retrieveDoc = "select  d.doctor_id, d.d_fname, d.d_lname, d.yoe, d.degree_name, h.hosp_name from Doctor d, Hospital h, Specialization s where (h.hosp_id = d.hosp_id) and (d.spec_id = s.spec_id) and (s.spec_id = '" + to_string(spec_id) + "')";
	if(mysql_query(conn, retrieveDoc.c_str())){
		vector<string> childVector;
		cout << mysql_error(conn) << endl;
		childVector.push_back("NULL");
		displayDoctorList.push_back(childVector);
		return displayDoctorList;
	}
	
	else
	{
		MYSQL_RES* res ;
	 	res = mysql_store_result(conn);
	 	if(res){
		 	int num = mysql_num_fields(res);
		 	MYSQL_ROW row;
		 	while(row = mysql_fetch_row(res)) {
//		 		for(int i=0; i < num; i++) {
//		 			cout << row[i] << "\t";
				
				vector<string> childVector;
				Doctor doctor;
				string s_id(row[0]);
				string sFName(row[1]);
				string sLName(row[2]);
				string sYoe(row[3]);
				string sDegree(row[4]);
				string sHospName(row[5]);
				sFName = sFName + " " + sLName;
				
				childVector.insert(childVector.end(), {s_id, sFName, sYoe, sDegree , sHospName});
//				cout<< childVector[0] << " " << childVector[1];
				displayDoctorList.push_back(childVector);
//				cout<<endl;
			
			}
		}
		mysql_free_result(res);
		return displayDoctorList;
	}
}

vector<vector<string>> Doctor::searchDoctorByName(MYSQL * conn, int spec_id, string name)
{
			vector<vector<string>> displayList = searchDoctorBySpec(conn, spec_id);
			vector<vector<string>> filteredList;
			for (const auto& doctor : displayList) {
				if (doctor.size() >= 2 && doctor[1] == name) {
					filteredList.push_back(doctor);
				}
			}
			return filteredList;
}

int Doctor::retrieveDoctor_Id(MYSQL* conn, const std::string& username)
{
	string retrieveQuery = "SELECT doctor_id FROM Doctor where username ='" + username +"'";
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

Doctor Doctor::retrieveDoctorDetail(MYSQL* conn, int doctor_id) 
{
	string retrieveQuery = "select * from Doctor where doctor_id = " + to_string(doctor_id);
	if(mysql_query(conn,retrieveQuery.c_str())) {
			Doctor doctor;
			cout<<"Error: "<<mysql_error(conn)<<endl;
			return doctor;
	}
	
	else 
	{
		Doctor doctor;
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		
		MYSQL_ROW row;
		row = mysql_fetch_row(res);
		
		doctor.setDoctorId(doctor_id);
		string uname(row[1]);
		doctor.setUsername(uname);
		string fname(row[2]);
		doctor.setFirst_name(fname);
		string lname(row[3]);
		doctor.setLast_name(lname);
		string gender(row[4]);
		doctor.setGender(gender);
		string ph(row[5]);
		doctor.setPh_no(stoll(row[5], nullptr, 10));
		string spec_id(row[6]);
		doctor.setSpec_id(stoi(spec_id));
		string degree(row[7]);
		doctor.setDegreeName(degree);
		string yoe(row[8]);
		doctor.setYearsOfExperience(stoi(yoe));
		
		
		string sConsult_from(row[9]);
		doctor.setConsultFromTime(sConsult_from);
		string sConsult_to(row[10]);
		doctor.setConsultToTime(sConsult_to);
		string sHosp_id(row[15]);
		doctor.setHosp_id(stoi(sHosp_id));
		string sAge(row[16]);
		doctor.setAge(stoi(sAge));
		string sBgroup(row[17]);
		doctor.setBlood_group(sBgroup);
		
				
		return doctor;
	}
}
