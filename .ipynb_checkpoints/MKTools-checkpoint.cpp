/**************************************************************************

Copyright: CPY, CUHK
Author: Xingqianli
Date: Jul.13 2022
Description: MKTools, the function of create make file 
Version: 1.0
File: MKTools.cpp

**************************************************************************/

#include "message.h"
#include "MKTools.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cstring>

using namespace std;

void MKTools::loadFile()
{
	message m;
	string row;
	unsigned int e;
	while(!cin.eof()) {
        getline(cin, row);
        e=row.find_last_not_of("\n");
        row = row.substr(0, e+1);
        mkArray.push_back(row);;
    }
	// cout << mkArray.size() << endl;
	m.printMessage("File has been uploaded");
}


void MKTools::loadFile(const string& fileName)
{
	message m;
	string row;
	ifstream mkFile(fileName.c_str(),ios::in);
	if(!mkFile){
		m.warnMessage("xqmk file failed to open! The currently entered file name is " + fileName);
		exit(1);
	}	
	while(getline(mkFile,row)) mkArray.push_back(row);;
	mkFile.close();
	// cout << mkArray.size() << endl;
	m.printMessage("File has been uploaded");
}

void MKTools::parseFile()
{
	vector<string> lineArrray;
	for(long unsigned int i=0;i<mkArray.size();i++){
        cout<<mkArray[i]<<endl;
		if (mkArray[i].rfind(">", 0) == 0){
			cout<<"!!!!"<endl;
		}
			
		lineArrray = this->split(mkArray[i],"\t");
		// cout<<lineArrray.size()<<endl;
	
	}
}

vector<string> MKTools::split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;
	char * strs = new char[str.length() + 1]; 
	strcpy(strs, str.c_str()); 
 
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
 
	char *p = strtok(strs, d);
	while(p) {
		string s = p;
		res.push_back(s); 
		p = strtok(NULL, d);
	}
 
	return res;
}
