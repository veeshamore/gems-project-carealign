#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include<mysql.h>
#include<mysqld_error.h>
#include "IDtoName.hpp"

using namespace std;

string IDtoName::patientIDtoName(MYSQL* conn, int p_id) {
	string retrieveQuery = "select p_fname, p_lname from Patient where patient_id = " + to_string(p_id);
	if(mysql_query(conn,retrieveQuery.c_str())) {
		cout<<"Error: "<<mysql_error(conn)<<endl;
		return "NULL";
	}
	
	else 
	{
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		
		MYSQL_ROW row;
		row = mysql_fetch_row(res);
		
		string fname(row[0]);
		string lname(row[1]);
		return fname+" "+lname;
	}
}

string IDtoName::doctorIDtoName(MYSQL* conn, int d_id) {
	string retrieveQuery = "select d_fname, d_lname from Doctor where doctor_id = " + to_string(d_id);
	if(mysql_query(conn,retrieveQuery.c_str())) {
		cout<<"Error: "<<mysql_error(conn)<<endl;
		return "NULL";
	}
	
	else 
	{
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		
		MYSQL_ROW row;
		row = mysql_fetch_row(res);
		
		string fname(row[0]);
		string lname(row[1]);
		return fname+" "+lname;
	}
}

string IDtoName::hospitalIDtoName(MYSQL* conn, int h_id) {
	string retrieveQuery = "select hosp_name from Hospital where hosp_id = " + to_string(h_id);
	if(mysql_query(conn,retrieveQuery.c_str())) {
		cout<<"Error: "<<mysql_error(conn)<<endl;
		return "NULL";
	}
	
	else 
	{
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		
		MYSQL_ROW row;
		row = mysql_fetch_row(res);
		
		string hname(row[0]);
		return hname;
	}
}

string IDtoName::wardIDtoName(MYSQL* conn, int w_id) {
	string retrieveQuery = "select ward_type from Ward where ward_id = " + to_string(w_id);
	if(mysql_query(conn,retrieveQuery.c_str())) {
		cout<<"Error: "<<mysql_error(conn)<<endl;
		return "NULL";
	}
	
	else 
	{
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		
		MYSQL_ROW row;
		row = mysql_fetch_row(res);
		
		string wname(row[0]);
		return wname;
	}
}
