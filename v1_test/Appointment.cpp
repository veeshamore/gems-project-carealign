#include <bits/stdc++.h>
#include <string>
#include <sstream>
#include <set>
#include "Appointment.hpp"

Appointment::Appointment() {
	Appointment_id = 0;
}

pair<string, string> Appointment::consultTime(MYSQL* conn, int doctor_id) {
	string retrieveDocTime = "select consult_from_time, consult_to_time from Doctor where doctor_id = " + to_string(doctor_id);
	if(mysql_query(conn, retrieveDocTime.c_str())) {
		pair<string, string> consultTimePair;
		cout << mysql_error(conn) << endl;
		
		consultTimePair.first = "0";
		consultTimePair.second = "0";
		return consultTimePair;
	}
	
	else
	{
		pair<string, string> consultTimePair;
		consultTimePair.first = "0";
		consultTimePair.second = "0";
		
		MYSQL_RES* res ;
	 	res = mysql_store_result(conn);
	 	if(res) {
		 	int num = mysql_num_fields(res);
		 	MYSQL_ROW row;
		 	row = mysql_fetch_row(res);
		 	
		 	string from_time(row[0]);
		 	string to_time(row[1]);
		 	consultTimePair.first = from_time;
			consultTimePair.second = to_time;
		}
		 	
		 	
//		 	while(row = mysql_fetch_row(res)) {
////		 		for(int i=0; i < num; i++) {
////		 			cout << row[i] << "\t";
//				
//				pair<tm, tm> childVector;
//				string s_id(row[0]);
//				string sFName(row[1]);
//				string sLName(row[2]);
//				string sYoe(row[3]);
//				string sDegree(row[4]);
//				string sHospName(row[5]);
//				sFName = sFName + " " + sLName;
//				
//				childVector.insert(childVector.end(), {s_id, sFName, sYoe, sDegree , sHospName});
////				cout<< childVector[0] << " " << childVector[1];
//				displayList.push_back(childVector);
////				cout<<endl;
//			
//			}
//		}
		mysql_free_result(res);
		return consultTimePair;
	}
}

vector<string> Appointment::findAvailableSlots(MYSQL* conn, string date, int doctor_id) {
	pair<string, string> consultTime = Appointment::consultTime(conn, doctor_id);
	vector<string> bookedSlotTime = Appointment::bookedSlots(conn, date, doctor_id);
	
	// Parse startTime and endTime
    int startHours, startMinutes, startSeconds;
    char delimiter;
    std::istringstream ss_start(consultTime.first);
    ss_start >> startHours >> delimiter >> startMinutes >> delimiter >> startSeconds;

    int endHours, endMinutes, endSeconds;
    std::istringstream ss_end(consultTime.second);
    ss_end >> endHours >> delimiter >> endMinutes >> delimiter >> endSeconds;

    // Convert start and end times into total minutes
    int totalStartMinutes = startHours * 60 + startMinutes;
    int totalEndMinutes = endHours * 60 + endMinutes;

    // Calculate the number of slots
    const int slotDuration = 15;
    int numSlots = (totalEndMinutes - totalStartMinutes) / slotDuration;

    // Create a set of booked slots
    std::set<std::string> bookedSlots;
    for (const auto& slot : bookedSlotTime) {
        bookedSlots.insert(slot);
    }

    // Store the available slots
    std::vector<std::string> availableSlots;

    // Check each slot between startTime and endTime
    for (int i = 0; i < numSlots; ++i) {
        int slotStart = totalStartMinutes + i * slotDuration;
        int slotEnd = slotStart + slotDuration;
        
        // Convert slotStart into HH:MM format
        int slotStartHours = slotStart / 60;
        int slotStartMinutes = slotStart % 60;

        std::string slotStartTime = (slotStartHours < 10 ? "0" : "") + std::to_string(slotStartHours) + ":" +
                                    (slotStartMinutes < 10 ? "0" : "") + std::to_string(slotStartMinutes) + ":00";

        // Check if the slot is available
        if (!bookedSlots.count(slotStartTime)) {
            availableSlots.push_back(slotStartTime);
        }
    }

    return availableSlots;
}

vector<string> Appointment::bookedSlots(MYSQL* conn, string date, int doctor_id) {
	string retrieveBookedSlots = "select booking_from_time from Doctor_Consulting where booking_date = '" + date +"' and doctor_id = " + to_string(doctor_id);
	
	if(mysql_query(conn, retrieveBookedSlots.c_str())){
		vector<string> bookedSlots;
		cout << mysql_error(conn) << endl;
		bookedSlots.emplace_back("Err");
		return bookedSlots;
	}
	
	else
	{
		vector<string> bookedSlots;
		MYSQL_RES* res ;
	 	res = mysql_store_result(conn);
	 	if(res) {
		 	MYSQL_ROW row;
		 	while(row = mysql_fetch_row(res)) {
		 		string booked(row[0]);
		 		bookedSlots.emplace_back(booked);
		 	}
		 	return bookedSlots;
		}
		else {
			bookedSlots.emplace_back("Err");
			return bookedSlots;
		}
	}
}

void Appointment::bed_suggestion(MYSQL* conn, int dc_id, int bed_suggest) {
	string updateQuery = "UPDATE Doctor_Consulting SET bed_suggest = " + to_string(bed_suggest) + " where doctor_consult_id = " + to_string(dc_id);
	if(mysql_query(conn, updateQuery.c_str())){
		cout << mysql_error(conn) << endl;
	}
	else
		cout << "Suggestion Added!" << endl;
}

bool Appointment::bookAppointment(MYSQL* conn, int p_id, int d_id, int h_id, string date, string time) {
	string insertQuery = "INSERT INTO Doctor_Consulting (patient_id, doctor_id, hosp_id, booking_date, booking_from_time) VALUES ('"+ to_string(p_id) +"', '"+ to_string(d_id) +"', '"+ to_string(h_id)+"', '"+ date +"', '"+ time +"')"; 
	if(mysql_query(conn, insertQuery.c_str())){
		cout << mysql_error(conn) << endl;
		return false;
	}
	
	else{
		cout << "Appointment Booked for P_ID: " << p_id << " at H_ID: " << h_id << " to D_ID: " << d_id << " on " << date << " " << time << endl;
		return true;
	}
}

Appointment Appointment::retrieveAppointmentDetails(MYSQL* conn, int ap_id) {
	string retrieveQuery = "select * from Doctor_Consulting where doctor_consult_id = " + to_string(ap_id);
	if(mysql_query(conn,retrieveQuery.c_str())) {
			Appointment appointment;
			cout<<"Error: "<<mysql_error(conn)<<endl;
			return appointment;
	}
	
	else 
	{
		Appointment appointment;
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		
		MYSQL_ROW row;
		row = mysql_fetch_row(res);
		
		appointment.setAppointment_id(ap_id);
		string p_id(row[1]);
		appointment.setPatient_id(stoi(p_id));
		string d_id(row[2]);
		appointment.setDoctorId(stoi(d_id));
		
		string book_date(row[3]);
		appointment.setBookingDate(book_date);
		string from_time(row[4]);
		appointment.setAppointmentFromTime(from_time);
		string bed_suggest(row[5]);
		appointment.setBedSuggest(stoi(bed_suggest));
		string h_id(row[7]);
		appointment.setHosp_id(stoi(h_id));
		
		return appointment;		
	}
}

vector<vector<string>> Appointment::viewAppointmentHistory(MYSQL* conn, int p_id) {
	string retrieveQuery = "select * from Doctor_Consulting where patient_id = " + to_string(p_id);
	vector<vector<string>> displayList;
	if(mysql_query(conn,retrieveQuery.c_str())) {
		vector<string> childVector;
		cout << mysql_error(conn) << endl;
		childVector.push_back("NULL");
		displayList.push_back(childVector);
		return displayList;
	}
	
	else 
	{
		IDtoName id_str;
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		if (res) {
			int num = mysql_num_fields(res);
			MYSQL_ROW row;
			while (row = mysql_fetch_row(res)) {
				vector<string> childVector;
				string dc_id(row[0]);
				string p_id(row[1]);
				string d_id(row[2]);
				string booking_date(row[3]);
				string booking_time(row[4]);
				string bed_suggest(row[5]);
				string h_id(row[7]);
				childVector.insert(childVector.end(), {dc_id, id_str.patientIDtoName(conn, stoi(p_id)), id_str.doctorIDtoName(conn, stoi(d_id)), id_str.hospitalIDtoName(conn, stoi(h_id)), booking_date, booking_time, bed_suggest});
				displayList.push_back(childVector);
			}
		}
		mysql_free_result(res);
		return displayList;
	}
		
}


