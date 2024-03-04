#ifndef APPOINTMENT_HPP
#define APPOINTMENT_HPP

#include <iostream>
#include <string>
#include <ctime>
#include<mysql.h>
#include<mysqld_error.h>
#include "Patient.hpp"
#include "Doctor.hpp"
#include "IDtoName.hpp"

using namespace std;

class Appointment: public Patient, public Doctor, public IDtoName {
	private:
		int Appointment_id;
		string booking_date;
		string appointment_from_time;
		int bed_suggest;
		
	public:
		Appointment();
		
		int getAppointment_id() {
			return Appointment_id;
		}
		
		void setAppointment_id(int appointment_id) {
			Appointment_id = appointment_id;
		}
		
		string getBookingDate() {
			return booking_date;
		}
		
		void setBookingDate(string book_date) {
			booking_date = book_date;
		}
		
		string getAppointmentFromTime() {
			return appointment_from_time;
		}
		
		void setAppointmentFromTime(string from_time) {
			appointment_from_time = from_time;
		}
		
		int getBedSuggest() {
			return bed_suggest;
		}
		
		void setBedSuggest(int bed_sugges) {
			bed_suggest = bed_sugges;
		}
		
		Appointment retrieveAppointmentDetails(MYSQL* conn, int ap_id);
		vector<vector<string>> viewAppointmentHistory(MYSQL* conn, int p_id);
		vector<string> findAvailableSlots(MYSQL* conn, string date, int doctor_id);
		vector<string> bookedSlots(MYSQL* conn, string date, int doctor_id);
		pair<string, string> consultTime(MYSQL* conn, int doctor_id);
		bool bookAppointment(MYSQL* conn, int p_id, int d_id, int h_id, string date, string time);
		void bed_suggestion(MYSQL* conn, int dc_id, int bed_suggest);
};
#endif
