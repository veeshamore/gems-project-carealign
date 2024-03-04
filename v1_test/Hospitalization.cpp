#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <chrono>
#include <iomanip>
#include "Hospitalization.hpp"

Hospitalization::Hospitalization() {
	Hospitalization_id = 0;
}

bool Hospitalization::checkBedSuggest(MYSQL* conn, int ap_id) {
	string checkQuery = "select bed_suggest from Doctor_Consulting where doctor_consult_id = " + to_string(ap_id);
	if(mysql_query(conn, checkQuery.c_str())){
		cout << mysql_error(conn) << endl;
		return false;
	}
	
	else{
		MYSQL_RES* res ;
	 	res = mysql_store_result(conn);
	 	MYSQL_ROW row;
	 	row = mysql_fetch_row(res);
	 	string sBed(row[0]);
	 	if(sBed == "1")
	 		return true;
	 	else
			return false;
	}
}

int Hospitalization::availableBeds(MYSQL* conn, Appointment* hzn, int ward_id, string dt) 
{
	string checkQuery = "SELECT bed_id FROM Bed WHERE hosp_id = "+ to_string(hzn->getHosp_id()) +" AND ward_id = "+ to_string(ward_id) +" AND bed_id NOT IN (SELECT bed_id FROM Hospitalisation WHERE '"+ dt +"' BETWEEN booking_from_date AND booking_to_date) LIMIT 1";
	if(mysql_query(conn, checkQuery.c_str())){
		cout << mysql_error(conn) << endl;
		return 0;
	}
	
	else {
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		
		MYSQL_ROW row;
		row = mysql_fetch_row(res);
		
		if(row == 0) {
			return 0;
		}
		else {
			string id(row[0]);
			return stoi(id);
		}
	}
}

bool Hospitalization::changeBedStatus(MYSQL* conn, int bed_id) {
	string updateQuery = "UPDATE Bed SET bed_status = '1' WHERE (bed_id = '" + to_string(bed_id)+"')";
	if(mysql_query(conn, updateQuery.c_str())){
		cout << mysql_error(conn) << endl;
		return false;
	}
	
	else return true;
}

string Hospitalization::addThreeDays(const string& inputDate) {
    // Parse input date string
    istringstream ss(inputDate);
    int year, month, day;
    char dash;
    ss >> year >> dash >> month >> dash >> day;

    // Create a time point representing the input date
    tm input_tm = {0};
    input_tm.tm_year = year - 1900; // Years since 1900
    input_tm.tm_mon = month - 1;    // Months are 0-based
    input_tm.tm_mday = day;

    time_t input_time = mktime(&input_tm);

    // Add three days to the input time
    input_time += 2 * 24 * 60 * 60; // 3 days in seconds

    // Convert the updated time back to a string
    tm* updated_tm = localtime(&input_time);
    ostringstream oss;
    oss << updated_tm->tm_year + 1900 << "-" << setw(2) << setfill('0') << updated_tm->tm_mon + 1 << "-" << setw(2) << setfill('0') << updated_tm->tm_mday;

    return oss.str();
}

bool Hospitalization::book_a_bed(MYSQL* conn, int bed_id, Appointment* hz, string dt) {
	string bookQuery = "INSERT INTO Hospitalisation (doctor_consult_id, patient_id, bed_id, booking_from_date, booking_to_date) VALUES ('"+to_string(hz->getAppointment_id())+"', '"+to_string(hz->getPatient_id())+"', '"+ to_string(bed_id) +"', '"+ dt +"', '"+ addThreeDays(dt) +"')";
	if(mysql_query(conn, bookQuery.c_str())){
		cout << mysql_error(conn) << endl;
		return false;
	}
	
	else {
		cout << "Bed Booked!" << endl;
	}
	
}


