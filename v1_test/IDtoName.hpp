#ifndef IDTONAME_HPP
#define IDTONAME_HPP
#include <string>
#include<mysql.h>
#include<mysqld_error.h>

using namespace std;

class IDtoName {
public:
	string patientIDtoName(MYSQL* conn, int p_id);
	string doctorIDtoName(MYSQL* conn, int d_id);
	string hospitalIDtoName(MYSQL* conn, int h_id);
	string wardIDtoName(MYSQL* conn, int w_id);
};
#endif
