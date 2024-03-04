#include <bits/stdc++.h>
#include <sstream>
#include "Specialization.hpp"

using namespace std;

Specialization::Specialization(){
	Spec_id = 0;
}


vector<pair<int, string>> Specialization::displaySpecList(MYSQL* conn)
{
//    stringstream s_specId;
//	s_specId << p.getSpec_Id();
//	string sSpecID = s_specId.str();
	
	vector<pair<int,string>> displayList;
	
	string retrieveSpec = "select * from Specialization";
	if(mysql_query(conn, retrieveSpec.c_str())){
		cout << mysql_error(conn) << endl;
		displayList.push_back(make_pair(0, "NULL"));
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
		 		for(int i=0; i < num; i++) {
//		 			cout << row[i] << "\t";
				}
				string sId(row[0]);
				string sName(row[1]);
				int n = stoi(sId);
		 		displayList.emplace_back(n, sName);
//				cout<<endl;
			}
		}
		mysql_free_result(res);
		return displayList;
	}
}
