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
#include <cstdlib>

using namespace std;


MKTools::MKTools()
{
	this->sampleName = "default";
}


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
	m.printMessage("File has been uploaded");
}


void MKTools::parseFile()
{
	message m;
	vector<string> lineArray;
	string targetName;
	Jobs job;
	vector<string> targetsHeadSample;
	vector<Jobs> targetsBodySample;
	for(long unsigned int i=0;i<mkArray.size();i++){
		if(mkArray[i].size()==0) continue;
		if (mkArray[i].rfind("@", 0) == 0){
			if(targetsHeadSample.size()>0){ 
				this->targetsHead.push_back(targetsHeadSample); 
				this->targetsBody.push_back(targetsBodySample);
				targetsHeadSample.clear();
				targetsBodySample.clear();
				vector<string> (targetsHeadSample).swap(targetsHeadSample);
				vector<Jobs> (targetsBodySample).swap(targetsBodySample);
			}
			lineArray = this->split(mkArray[i],"@");
			sampleName = lineArray.at(0);
			sampleArray.push_back(sampleName);
		}else{
			lineArray = this->split(mkArray[i],"\t");
			if(lineArray.size()<3){m.warnMessage("Warning: insufficient content of target line, skip this line: "+mkArray[i]);continue;}
			if(sampleArray.size()==0) sampleArray.push_back(this->sampleName);
			if(lineArray.at(0).size()<4) targetName= "Job_" + lineArray.at(0);
			else targetName = lineArray.at(0);	
			if((this->split(lineArray.at(1),",")).at(0) == ALL){
				if(this->targetsAll.size()>0) m.warnMessage("Error: specify that the last target is more than one, only set one target to be last executed"), exit(1);
				else{targetsAll.push_back(lineArray.at(2)); continue;}
			}
			targetsHeadSample.push_back(targetName);
			job.target = targetName;
			job.prerequisites = this->split(lineArray.at(1),",");
			job.command = lineArray.at(2);
			targetsBodySample.push_back(job);
		}
	}
	this->targetsHead.push_back(targetsHeadSample);
	this->targetsBody.push_back(targetsBodySample);	
	if(this->targetsHead.at(0).size()==0) m.warnMessage("Error: didn't find any valid targets, parsing failed"), exit(1);
	else m.printMessage("Parsing is completed");
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

void MKTools::exportMK(const string& fileName)
{
	message m;
	ofstream outFile(fileName.c_str(),ios::out);
	vector<string> targetsHeadSample;
	vector<Jobs> targetsBodySample;
	if(!outFile){
		m.warnMessage("Writing to the file failed! The currently entered file name is "+fileName);
		exit(1);
	}
	system("mkdir -p log");
	
	//Head
	outFile << "all: ";
	if(sampleArray.size()>1){
		for(long unsigned int i=0;i<sampleArray.size();i++){
			outFile << " log/" << sampleArray.at(i) << ".done ";
		}
		outFile << endl;
	}else{
		targetsHeadSample = this->targetsHead.at(0);
		for(long unsigned int i=0;i<targetsHeadSample.size();i++){
			outFile << " log/" << targetsHeadSample.at(i) << ".done";
		}
		outFile << endl;
	}
	if(this->targetsAll.size()>0) outFile << "\t" << targetsAll.at(0) << endl;
	outFile << endl;
	
	//Body
	if(sampleArray.size()>1){
		for(long unsigned int i=0;i<sampleArray.size();i++){
			outFile << "log/" << sampleArray.at(i) << ".done:";
			targetsHeadSample = this->targetsHead.at(i);
			targetsBodySample = this->targetsBody.at(i);
			for(long unsigned int j=0;j<targetsHeadSample.size();j++){
				outFile << " log/" << sampleArray.at(i) << '.' << targetsHeadSample.at(j) << ".done";
			}
			outFile << endl;
			outFile << "\ttouch log/" << sampleArray.at(i) << ".done" << endl << endl;
			for(long unsigned int j=0;j<targetsHeadSample.size();j++){
				outFile << "log/" << sampleArray.at(i) << '.' << targetsHeadSample.at(j) << ".done:";
				if(targetsBodySample.at(j).prerequisites.at(0)=="0") outFile << endl;
				else{
					for(auto &pIndex : targetsBodySample.at(j).prerequisites){
						outFile << " log/" << sampleArray.at(i) << '.' << targetsHeadSample.at(stoi(pIndex)-1) << ".done";
					}
					outFile << endl;
				}
				outFile << "\t" << targetsBodySample.at(j).command << " && touch log/" << sampleArray.at(i) << '.' << targetsHeadSample.at(j) << ".done" << endl;
				outFile << endl;
			}
			outFile << endl;
		}
	}else{
		targetsHeadSample = this->targetsHead.at(0);
		targetsBodySample = this->targetsBody.at(0);
		for(long unsigned int j=0;j<targetsHeadSample.size();j++){
				outFile << "log/" << targetsHeadSample.at(j) << ".done:";
				if(targetsBodySample.at(j).prerequisites.at(0)=="0") outFile << endl;
				else{
					for(auto &pIndex : targetsBodySample.at(j).prerequisites){
						outFile << " log/" << targetsHeadSample.at(stoi(pIndex)-1) << ".done";
					}
					outFile << endl;
				}
				outFile << "\t" << targetsBodySample.at(j).command << " && touch log/" << targetsHeadSample.at(j) << ".done" << endl;
				outFile << endl;
			}
			outFile << endl;
	}
	m.warnMessage("File successfully written! The makefile has been saved: "+fileName);
	outFile.close();
}
