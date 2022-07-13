/**************************************************************************

Copyright: CPY, CUHK
Author: Xingqianli
Date: Jan.04 2020 
Description: Unit
Version: 1.0
File: message.cpp

**************************************************************************/


#include <iostream>
#include "message.h"
#include <ctime>
#include <cstring>

using namespace std;

void message::printMessage(const string& str){
	time_t now = time(0);
	char* dt = ctime(&now);
	dt[strlen(dt)-1]=0;
	cout << "[" << dt << "]  " << str << endl;
}

void message::warnMessage(const string& str){
	time_t now = time(0);
	char* dt = ctime(&now);
	dt[strlen(dt)-1]=0;
	cerr << "[" << dt << "]  " << str << endl;
}




