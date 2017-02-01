#include "dbHandler.h"


dbHandler::dbHandler(){
	// Create a connection 
	try{
		driver = get_driver_instance();
		//con = driver->connect("tcp://127.0.0.1:5504", "tester", "hybr1dTest3r");
		con = driver->connect("tcp://dbod-tkhybrid.cern.ch:5503", "tester", "hybr1dTest3r");
		if(isConnected()){
			std::cout << "[dbHandler] Database connected succesfully" << std::endl;
			// Connect to the MySQL test database 
			con->setSchema("tkhybrid");
		}
	}
	catch(sql::SQLException &e){
		std::cout << "[dbHandler] Database not connected. Did you set up the tunnel properly?" << endl;		
		con=nullptr;
	}
	//else FIXME try to connect several times
}

dbHandler::~dbHandler(){
	if(res!=nullptr) delete res;
	if(stmt!=nullptr) delete stmt;
	if(con!=nullptr) delete con;
	;
}

bool dbHandler::reconnect(){
	// Create a connection 
	con->reconnect();
	if(isConnected()){
		std::cout << "[dbHandler] Database connected succesfully" << std::endl;
		// Connect to the MySQL test database 
		con->setSchema("tkhybrid");
	}
	//else
}

bool dbHandler::isConnected(){
	try{
		if (con == nullptr || con->isClosed()){
			std::cout << "[dbHandler] Database not connected." << std::endl;
			return false;
		}
		else{
			return true;
		}
	}
	catch(sql::SQLException &e){
		std::cout << "[dbHandler] Database not connected." << std::endl;
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line "
			<< __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return false;
	}
}
void dbHandler::checkInput(std::string *input){
	input->erase(remove_if(input->begin(), input->end(), [](char c) { return !isalnum(c); } ), input->end());	
}
// checking if the hybryd has already been tested
bool dbHandler::checkHybrid(string hybridID){
	checkInput(&hybridID);
	stmt = con->createStatement();
	try{
		res = stmt->executeQuery((string)"SELECT * FROM "+table+" WHERE hybrid_serial_number='"+hybridID+"';");
		if (res->rowsCount()==0){
			std::cout << "[dbHandler::checkHybrid] Hybrid not tested. HybridID: "<< hybridID << std::endl;
			return true;
		}
		else{
			std::cout << "[dbHandler::checkHybrid] Hybrid tested. HybridID: " << hybridID << std::endl;
			return false;
		}
	}
	catch(sql::SQLException &e){
		std::cout << "[dbHandler::checkHybrid] Problem with the database." << std::endl;
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line "
			<< __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;throw("dbHandler failed");
	}
}
// inserting new result into the DB
bool dbHandler::insertNewTestResult(string hybridID, string calibrationStatus, string pass_test, string nCBCs, string timestamp){
	// Input sanitization
	checkInput(&hybridID);
	checkInput(&calibrationStatus);
	checkInput(&pass_test);
	checkInput(&nCBCs);
	checkInput(&timestamp);
	// Executing query
	stmt = con->createStatement();
	if (!checkHybrid(hybridID)){
		// If hybrid was already tested, it will remove the active flag from the previous test result, old entry stills stays in the DB 
		removeOldTestResult(hybridID);
	}
	std::string query = "INSERT INTO "+table+" (date,time,hybrid_type,hybrid_serial_number,passed_test,exit_code) VALUES (FROM_UNIXTIME("+timestamp+", '%Y-%m-%d'),From_UNIXTIME("+timestamp+", '%H:%i:%s'),'"+nCBCs+"', '"+hybridID+"', '"+pass_test+"','"+calibrationStatus+"');";
	std::cout << "[dbHandler::insertNewTestResult]" << query << std::endl;
	try {
		res = stmt->executeQuery(query);//FIXME blob
	} catch (sql::SQLException &e) {
		if (e.getErrorCode()!=0){
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line "
				<< __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
			throw("dbHandler failed");
		}
		//std::cout << "INSERT crash, checking status of the last input..." << std::endl;
		std::cout << "[dbHandler::insertNewTestResult] Checking status of the last input..." << std::endl;
		if(checkHybrid(hybridID)) {
			std::cout << "[dbHandler::checkHybrid] Problem with inserting into the DB." << std::endl;
			return false;
		}
		else { 
			std::cout << "[dbHandler::checkHybrid] Insert successfull." << std::endl;
			return true;
		}
	}
	return true;
}
bool dbHandler::removeOldTestResult(string hybridID){
	// Input sanitization
	checkInput(&hybridID);
	// Executing query
	stmt = con->createStatement();
	std::string query = "UPDATE "+table+" SET is_last=false WHERE hybrid_serial_number='"+hybridID+"';";
	std::cout << "[dbHandler::modifyOldTestResult]" << query << std::endl;
	try {
		res = stmt->executeQuery(query);//FIXME blob
	} catch (sql::SQLException &e) {
		if (e.getErrorCode()!=0){
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line "
				<< __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
			throw("dbHandler failed");
		}
		//std::cout << "INSERT crash, checking status of the last input..." << std::endl;
		std::cout << "[dbHandler::modifyNewTestResult] Checking status of the last input..." << std::endl;
		if(checkHybrid(hybridID)) {
			std::cout << "[dbHandler::checkHybrid] Problem with inserting into the DB." << std::endl;
			return false;
		}
		else { 
			std::cout << "[dbHandler::checkHybrid] Modification successfull." << std::endl;
			return true;
		}
	}
	return true;
}

bool dbHandler::modifyOldTestResult(string hybridID, string calibrationStatus, string pass_test, string timestamp){
	// Input sanitization
	checkInput(&hybridID);
	checkInput(&calibrationStatus);
	checkInput(&pass_test);
	//checkInput(&nCBCs);
	checkInput(&timestamp);
	// Executing query
	stmt = con->createStatement();
	std::string query = "UPDATE "+table+" SET date=FROM_UNIXTIME("+timestamp+", '%Y-%m-%d'), time=FROM_UNIXTIME("+timestamp+", '%H:%i:%s'), passed_test='"+pass_test+"',exit_code='"+calibrationStatus+"' WHERE hybrid_serial_number='"+hybridID+"';";
	std::cout << "[dbHandler::modifyOldTestResult]" << query << std::endl;
	try {
		res = stmt->executeQuery(query);//FIXME blob
	} catch (sql::SQLException &e) {
		if (e.getErrorCode()!=0){
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line "
				<< __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
			throw("dbHandler failed");
		}
		//std::cout << "INSERT crash, checking status of the last input..." << std::endl;
		std::cout << "[dbHandler::modifyNewTestResult] Checking status of the last input..." << std::endl;
		if(checkHybrid(hybridID)) {
			std::cout << "[dbHandler::checkHybrid] Problem with inserting into the DB." << std::endl;
			return false;
		}
		else { 
			std::cout << "[dbHandler::checkHybrid] Insert successfull." << std::endl;
			return true;
		}
	}
	return true;
}

string dbHandler::getLast(){
	stmt = con->createStatement();
	return 0;
};

void dbHandler::printBase(){
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * FROM FEH_hybrid_test");
	while (res->next()) {
		std::cout << "\t... MySQL replies: ";
		// Access column data by numeric offset, 1 is the first column 
		std::cout << res->getString(1) << " " << res->getString(2) << std::endl;
		//std::cout << res << std::endl;
	}
}

