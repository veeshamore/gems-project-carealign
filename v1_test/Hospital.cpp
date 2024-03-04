#include <bits/stdc++.h>
#include "Hospital.hpp"

using namespace std;

Hospital::Hospital(){
	Hosp_id = 0;
}

vector<vector<string>> Hospital::displayHospitalList(MYSQL* conn, int spec_id)
{
	string retrieveHosp = "select h.hosp_id, h.hosp_name, h.hosp_location from Hospital h, Junction_Hosp_Spec j where j.hosp_id = h.hosp_id and j.spec_id = " + to_string(spec_id);
	vector<vector<string>> displayList;
		
	if (mysql_query(conn, retrieveHosp.c_str())) {
		vector<string> childVector;
		cout << mysql_error(conn) << endl;
		childVector.push_back("NULL");
		displayList.push_back(childVector);
		return displayList;
	}
	else
	{
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		if (res) {
			int num = mysql_num_fields(res);
			MYSQL_ROW row;
			while (row = mysql_fetch_row(res)) {
				vector<string> childVector;
				string s_id(row[0]);
				string sName(row[1]);
				string sLoc(row[2]);
				childVector.insert(childVector.end(), {s_id, sName, sLoc});
				displayList.push_back(childVector);
			}
		}
		mysql_free_result(res);
		return displayList;
	}
}

vector<pair<int, string>> Hospital::displayWardList(MYSQL* conn)
{
	string retrieveWard = "select * from Ward";
	vector<pair<int, string>> displayList;
		
	if (mysql_query(conn, retrieveWard.c_str())) {
		cout << mysql_error(conn) << endl;
		displayList.push_back(make_pair(0, "NULL"));
		return displayList;
	}
	else
	{
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		if (res) {
			int num = mysql_num_fields(res);
			MYSQL_ROW row;
			while (row = mysql_fetch_row(res)) {
				string wId(row[0]);
				string wName(row[1]);
				int n = stoi(wId);
		 		displayList.emplace_back(n, wName);
			}
		}
		mysql_free_result(res);
		return displayList;
	}
}
