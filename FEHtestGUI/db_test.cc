#include <iostream>
#include "dbHandler.h"
#include <time.h>

int main(){
	dbHandler test;

	time_t t = time(0);

	//test.printBase();
	if(test.isConnected())	
	{
		string b = "fs";
		test.checkHybrid("complicatedserialnum",&b);
		std::cout << "This is hybrid status: " << b << std::endl;
	}
	else
		cout << "nothing" << endl;
	//test.insertNewTestResult("complicatedserialnum","102","2","1",std::to_string(t));
	//test.modifyOldTestResult("complicatedserialnum","4212","1",std::to_string(t));
	/*test.checkHybrid("1111");

	  test.isConnected();
	  sleep(20);
	  test.reconnect();
	  sleep(10);
	  test.isConnected();*/
	return 0;
}

