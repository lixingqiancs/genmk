/**************************************************************************

Copyright: CPY, CUHK
Author: Xingqianli
Date: Jul.10 2022 
Description: Create Pipeline
Version: 1.0
File: create_pipeline.cpp

**************************************************************************/

#include "message.h"
#include "MKTools.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <map>

using namespace std;

int main(int argc, char** argv)
{
	message m;
	MKTools mkTools;
	int ch;
	unsigned int fileType = 0,fileTypeNum = 0; 
	string fileName;

	cout << "--------------------------" << endl;
	
	if(argc<2){
		m.warnMessage("usage: xq_mk < -f file> or < -p within | (pipeline)>");
		exit(1);
	}
	
	while ((ch = getopt(argc, argv, "f:p")) != -1) {
        switch (ch) {
            case 'f':
				fileType = 1;
				++(fileTypeNum);
				fileName = (string)optarg;
                break;
            case 'p':
				fileType = 2;
				++(fileTypeNum);
                break;
            case '?':
				string unknowOpthion="Unknown option: ";
				unknowOpthion.push_back((char)optopt);
                m.printMessage(unknowOpthion);
                exit(1);
        }
		
    }
	
	if(fileTypeNum > 1){
		m.warnMessage("Exit: Only one file source can be specified");
		exit(1);
	}
	
	if(fileType == 1){
		m.printMessage("File is " + fileName);
		mkTools.loadFile(fileName);
	}
	else{
		m.printMessage("File from pipeline");
		mkTools.loadFile();
	}
	
	mkTools.parseFile();
	
	return EXIT_SUCCESS;
}