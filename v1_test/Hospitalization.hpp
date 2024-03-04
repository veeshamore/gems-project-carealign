#ifndef HOSPITALIZATION_HPP
#define HOSPITALIZATION_HPP

#include <iostream>
#include <string>
#include <ctime>
#include <mysql.h>
#include <mysqld_error.h>
#include "Appointment.hpp"

using namespace std;

class Hospitalization : public Appointment {
	private:
		int Hospitalization_id;
		int Ward_id;
		string booking_from_date;
		string booking_to_date;
		
	public:
		Hospitalization();
		
		int getHospitalization_id() {
			return Hospitalization_id;
		}
		
		void setHospitalization_id(int hospitalization_id) {
			Hospitalization_id = hospitalization_id;
		}
		
		int getWard_id() {
			return Ward_id;
		}
		
		void setWard_id(int ward_id) {
			Ward_id = ward_id;
		}
		
		string getBooking_to_date(){
			return booking_to_date;
		}
		
		void setBooking_to_date(string to_date){
			booking_to_date = to_date;
		}
		
		string getBooking_from_date(){
			return booking_from_date;
		}
		
		void setBooking_from_date(string from_date){
			booking_from_date = from_date;
		}
		
		bool book_a_bed(MYSQL* conn, int bed_id, Appointment* hz, string dt);
		bool changeBedStatus(MYSQL* conn, int bed_id);
		bool checkBedSuggest(MYSQL* conn, int ap_id);
		int availableBeds(MYSQL* conn, Appointment* hz, int ward_id, string dt);
		string addThreeDays(const string& inputDate);
};
#endif
