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
	//if(res!=nullptr) delete res;
	//if(stmt!=nullptr) delete stmt;
	//if(con!=nullptr) delete con;
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
	//else FIXME try to connect several times
}

bool dbHandler::isConnected(){
	try{
		if (con == nullptr || con->isClosed()){
			std::cout << "[dbHandler] Database not connected. Did you set up the tunnel properly?" << std::endl;
			return false;
		}
		else{
			return true;
		}
	}
	catch(sql::SQLException &e){
		std::cout << "[dbHandler] Database not connected. Did you set up the tunnel properly?" << std::endl;
	}
}
// checking if the hybryd has already been tested
bool dbHandler::checkHybrid(string hybridID){
	stmt = con->createStatement();
	try{
		res = stmt->executeQuery((string)"SELECT * FROM FEH_test_results WHERE hybrid_serial_number="+hybridID);
		if (res->rowsCount()==0){
			std::cout << "[db_handler::checkHybrid] Hybrid not tested. HybridID: "<< hybridID << std::endl;
			return true;
		}
		else{
			std::cout << "[db_handler::checkHybrid] Hybrid tested. HybridID: " << hybridID << std::endl;
			return false;
		}
	}
	catch(sql::SQLException &e){
		std::cout << "[db_handler::checkHybrid] Problem with the database. Try to reconnect." << std::endl;
		throw("db_handler failed");
	}
}
// inserting new result into the DB
bool dbHandler::insertNewTestResult(string hybridID, string calibrationStatus, string pass_test, string nCBCs, string timestamp){
		std::cout << "INSERT INTO FEH_test_results (date,time,hybrid_type,hybrid_serial_number,passed_test,exit_code,test_result) VALUES (FROM_UNIXTIME("+timestamp+",  '%D.%M.%Y'), FROM_UNIXTIME("+timestamp+", '%h:%i:%s')," << nCBCs << ", " << hybridID << ", 1," << calibrationStatus << ");" << std::endl;
	stmt = con->createStatement();
	try {
		//res = stmt->executeQuery("INSERT INTO FEH_test_results (date,time,hybrid_type,hybrid_serial_number,passed_test,exit_code,test_result) VALUES (DATE("+timestamp+"),TIME("+timestamp+"),"+nCBCs+", "+hybridID+", 1,"+calibrationStatus+", LOAD_FILE('dummy_pdf.pdf'));");//FIXME blob
		res = stmt->executeQuery("INSERT INTO FEH_test_results (date,time,hybrid_type,hybrid_serial_number,passed_test,exit_code) VALUES (FROM_UNIXTIME("+timestamp+", '%Y-%m-%d'),From_UNIXTIME("+timestamp+", '%H:%i:%s'),"+nCBCs+", "+hybridID+", "+pass_test+","+calibrationStatus+");");//FIXME blob
	} catch (sql::SQLException &e) {
		std::cout << "INSERT crash, checking status of the last input..." << std::endl;
		if(checkHybrid(hybridID)) {
			std::cout << "[db_handler::checkHybrid] Problem with inserting into the DB." << std::endl;
			return false;
		}
		else { 
			std::cout << "[db_handler::checkHybrid] Insert successfull." << std::endl;
			return true;
		}
	}
	return true;
}

bool dbHandler::modifyOldTestResult(string hybridID, string calibrationStatus){
	stmt = con->createStatement();
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

