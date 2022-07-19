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
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
	message m;
	MKTools mkTools;
	int ch;
	unsigned int fileType = 0,fileTypeNum = 0; 
	string fileName;
	string outputName = "makefile";
	while ((ch = getopt(argc, argv, "f:po:")) != -1) {
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
			case 'o':
				outputName = (string)optarg;
                break;
            case '?':
				cerr << "unrecognized command: " << "'" << (char)optopt << "'" << endl;
                exit(1);
        }
    }
	if(fileTypeNum > 1){
		cerr << "Error: Only and need one file source can be specified" << endl;
		exit(1);
	}else if(fileTypeNum < 1){
		cerr << "\nProgram: " << *argv << " (Tools for create a makefile in the xqmk format for bioinformatics pipeline analysis)" << endl;
		cerr << "Version: 1.0" << endl;
		cerr << "Contact: Xingqianli@cuhk.edu.hk" << endl;
		cerr << "\nUsage: \n\t" << *argv  << " < -f file> or < -p within | (pipeline)> < -o output_file>" << endl;
		cerr << "\nOptions:" << "\n\t" << "-f: STR\t" << "Path of xqmk file"  <<  endl;
		cerr << "\t-p\tcreate makefile from pipeline(|)"<< endl;
		cerr << "\t-o: STR\tPath of output make file"<< endl;
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
	mkTools.exportMK(outputName);
	return EXIT_SUCCESS;
}
