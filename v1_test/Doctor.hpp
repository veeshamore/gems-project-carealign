#ifndef DOCTOR_HPP
#define DOCTOR_HPP
#include <string>
#include<mysql.h>
#include<mysqld_error.h>
#include "User_Details.hpp"
#include "Specialization.hpp"
#include "Hospital.hpp"

using namespace std;

class Doctor : public User_Details, public Hospital {
private:
	int doctor_id;
	string degree_name;
	int yoe;
	string consult_from_time;
    string consult_to_time;
    string ward_visit_from_time;
    string ward_visit_to_time;
    string emergency_from_time;
    string emergency_to_time;
public:
    // Constructor
    Doctor();
    // Getters
    int getDoctorId() const {
        return doctor_id;
    }
    
    std::string getDegreeName() const {
        return degree_name;
    }
    int getYearsOfExperience() const {
        return yoe;
    }
    string getConsultFromTime() const {
        return consult_from_time;
    }
    string getConsultToTime() const {
        return consult_to_time;
    }
    string getWardVisitFromTime() const {
        return ward_visit_from_time;
    }
    string getWardVisitToTime() const {
        return ward_visit_to_time;
    }
    string getEmergencyFromTime() const {
        return emergency_from_time;
    }
    string getEmergencyToTime() const {
        return emergency_to_time;
    }
    // Setters
    void setDoctorId(int newDoctorId) {
        doctor_id = newDoctorId;
    }
    
    void setDegreeName(const std::string& newDegreeName) {
        degree_name = newDegreeName;
    }
    void setYearsOfExperience(int newYoe) {
        yoe = newYoe;
    }
    void setConsultFromTime(string newConsultFromTime) {
        consult_from_time = newConsultFromTime;
    }
    void setConsultToTime(string newConsultToTime) {
        consult_to_time = newConsultToTime;
    }
    void setWardVisitFromTime(string newWardVisitFromTime) {
        ward_visit_from_time = newWardVisitFromTime;
    }
    void setWardVisitToTime(string newWardVisitToTime) {
        ward_visit_to_time = newWardVisitToTime;
    }
    void setEmergencyFromTime(string newEmergencyFromTime) {
        emergency_from_time = newEmergencyFromTime;
    }
    void setEmergencyToTime(string newEmergencyToTime) {
        emergency_to_time = newEmergencyToTime;
    }
    
    
    vector<vector<string>> searchDoctorBySpec(MYSQL* conn, int spec_id);
    vector<vector<string>> searchDoctorByHospital(MYSQL* conn, int spec_id, int hosp_id);
    vector<vector<string>> searchDoctorByName(MYSQL* conn, int spec_id, string name);
    vector<string> displayDoctorDetails(MYSQL* conn, int doctor_id);
    int retrieveDoctor_Id(MYSQL* conn, const std::string& username);
    Doctor retrieveDoctorDetail(MYSQL* conn, int doctor_id);
};
#endif // DOCTOR_HPP
	
