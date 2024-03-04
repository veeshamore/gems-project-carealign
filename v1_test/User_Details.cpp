#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "User_Details.hpp"

using namespace std;

bool User_Details::isUsernameAvailable(MYSQL* conn, const string& username) {
	string checkUsername = "SELECT * FROM User_Details WHERE username = '" + username + "'";
	if(mysql_query(conn,checkUsername.c_str())) {
		cout<<"Error: "<<mysql_error(conn)<<endl;
		return false;
	}
	
	else {
		MYSQL_RES* res ;
		res = mysql_store_result(conn);
		
		MYSQL_ROW row;
		row = mysql_fetch_row(res);
		
		if(row == 0){
			mysql_free_result(res);
			return true;
		}
		mysql_free_result(res);
		return false;
	}
}

bool User_Details::addInUser_Details(MYSQL* conn, User_Details* user) {
//	stringstream s_role;
//	s_role << user.getRole();
//	string sRole = s_role.str();
	
	string insertQuery = "INSERT INTO User_Details (role_id, username, password) VALUES ('"+ to_string(user->getRole())+"', '"+ user->getUsername() +"', "+ user->getPassword() +")"; 
	if(mysql_query(conn, insertQuery.c_str())){
		cout << mysql_error(conn) << endl;
		return false;
	}
	else{
		cout << "Data inserted in user_details.." << endl;
		return true;
	}
}

bool User_Details::login(MYSQL* conn, User_Details* user) {

	if(!(user->isUsernameAvailable(conn, user->getUsername()))){
		string show = "SELECT * FROM User_Details WHERE username = '" + user->getUsername() + "'";
		if(mysql_query(conn,show.c_str())) {
			cout<<"Error: "<<mysql_error(conn)<<endl;
			return 0;
		}
		
		else {
			MYSQL_RES* res ;
			res = mysql_store_result(conn);
			
			MYSQL_ROW row;
			row = mysql_fetch_row(res);
			
			if(row == 0){
				mysql_free_result(res);
				return 0;
			}
			else if(row[1] == user->getUsername() && row[2] == user->getPassword() && row[0] == to_string(user->getRole())) {
//				cout<<row[0]<<endl;
				mysql_free_result(res);
				return true;
			}
			mysql_free_result(res);
			return 0;
		}
	}
	else
		return 0;
}
	
//	else{
//		MYSQL_RES* res ;
//		res = mysql_store_result(conn);
//		
//		if(res){
//			MYSQL_ROW row;
//			row = mysql_fetch_row(res);
//			
//			if(row == 0){
//				return 20;
//			}
//			
//			if(row[0] == user.getUsername() && row[1] == user.getPassword()){
//				string pat_id = "SELECT patient_id from patient WHERE username ='"+ user.getUsername() +"'";
//				if(mysql_query(conn,show.c_str())) {
//					cout<<" after password Error: "<<mysql_error(conn)<<endl;
//					return 30;
//				}
//				else {
//					res = mysql_store_result(conn);
//					row = mysql_fetch_row(res);
//					mysql_free_result(res);
//					cout<<row[0]<<endl;
//					int id = atoi(row[0]);
//					cout<<id;
//					return id;
//				}
////				return true;
//			}
//			mysql_free_result(res);
//			return 40;
//		}
//		return 50;
//	}
//}

//	string get = "SELECT * FROM user_details where username='" + username +"'";
//	if(mysql_query(conn, get.c_str())){
//		cout << mysql_error(conn) << endl;
//		return false;
//	}
//	else{
//		MYSQL_RES* result = mysql_store_result(conn);
//		if(result){
//			int num = mysql_num_fields(result);
//			MYSQL_ROW row;
//			cout<<endl<<endl;
//			while(row = mysql_fetch_row(result)){
//				for(int i=0; i<num; i++){
//					cout <<"  "<<row[i];
//				}
//				cout << endl;
//			}
//			
//			mysql_free_result(result);
//			return true;
//		}
//		return false;
//    }
//}

//string User_Details::login(const std::string& username, const std::string& password, const int& role) {
//
//    try {
//        ostringstream queryStream;
//        queryStream << "SELECT * FROM user_details WHERE username = '" << username
//            << "' AND password = '" << password << "' AND role_id = " << role;
//
//        std::string query = queryStream.str();
//
//        sql::ResultSet* res = dbConnection.executeQuery(query);
//
//        // Process the result set as needed
//        if (res->next()) {
//            // Authentication successful
//            delete res;
//            dbConnection.closeConnection();
//            return true;
//        }
//        else {
//            // Authentication failed
//            delete res;
//            dbConnection.closeConnection();
//            return false;
//        }
//
//    }
//    catch (sql::SQLException& e) {
//        cerr << "SQL Exception: " << e.what() << endl;
//        dbConnection.closeConnection();
//        return false; // Authentication failure
//    }
//}

/*
bool User_Details::login(const std::string& username, const std::string& password, const int& role) {
    MySQLConnector connector;

    if (connector.connect("127.0.0.1:3306", "root", "root", "cpp_test")) {
        try {
            std::ostringstream queryStream;
            queryStream << "SELECT * FROM user_details WHERE username = '" << username
                << "' AND password = '" << password << "' AND role_id = " << role;

            std::string query = queryStream.str();

            sql::PreparedStatement* stmt = connector.getConnection()->prepareStatement(query);
            sql::ResultSet* res = stmt->executeQuery();

            // Process the result set as needed
            if (res->next()) {
                // Authentication successful
                delete res;
                delete stmt;
                connector.disconnect();
                return true;
            }
            else {
                // Authentication failed
                delete res;
                delete stmt;
                connector.disconnect();
                return false;
            }

        }
        catch (sql::SQLException& e) {
            std::cerr << "SQL Exception: " << e.what() << std::endl;
            connector.disconnect();
            return false; // Authentication failure
        }
    }
    else {
        // Unable to connect to the database
        return false;
    }
}
*/

//bool User_Details::signup(const string& username, const string& password, const string& p_fname, const string& p_lname, const char& gender, const long& ph_no, const string& blood_group, const string& location)
//{
//    int role_id = 4;
//    try {
//        ostringstream queryStream;
//        queryStream << "SELECT * FROM user_details WHERE username = '" << username << "' AND role_id = 4" << ;
//
//        std::string query = queryStream.str();
//
//        sql::ResultSet* res = dbConnection.executeQuery(query);
//
//        // Process the result set as needed
//        if (res->next()) {
//            // Authentication successful
//            delete res;
//            dbConnection.closeConnection();
//            return true;
//        }
//        else {
//            // Authentication failed
//            delete res;
//            dbConnection.closeConnection();
//            return false;
//        }
//
//    }
//    catch (sql::SQLException& e) {
//        cerr << "SQL Exception: " << e.what() << endl;
//        dbConnection.closeConnection();
//        return false; // Authentication failure
//    }
//}
