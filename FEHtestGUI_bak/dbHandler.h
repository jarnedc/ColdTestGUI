#include <iostream>
#include <stdlib.h>
#include <string>
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class dbHandler{
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	public:
	dbHandler();
	~dbHandler();
	bool isConnected();
	bool reconnect();
	bool checkHybrid(string hybridID);	
	bool insertNewTestResult(string hybridID, string calibrationStatus, string pass_test, string nCBCs, string timestamp);
	bool modifyOldTestResult(string hybridID, string calibrationStatus);//not implemented
	string getLast(); //not implemented
	void printBase();
	/*INSERT INTO my_table (stamp, docFile) VALUES (NOW(), LOAD_FILE('/tmp/my_file.odt'));*/

};

