#include <string>
// #include <map>
#include <vector>

using namespace std;

#ifndef MKTOOLS_H
#define MKTOOLS_H

#define ALL "all"

struct Jobs
{
   string target;
   vector<string> prerequisites;
   string command;
};

class MKTools{
	
	private:
		string sampleName;
		vector<string> mkArray;
		vector<string> sampleArray;
		vector< vector<string> > targetsHead;  //Sample:targetName
		vector< vector<Jobs> > targetsBody;  //Sample:
		vector<string> targetsAll;
	
	public:
		MKTools();
		void loadFile();
		void loadFile(const string& fileName);
		void parseFile();
		vector<string> split(const string& str, const string& delim);
		void exportMK(const string& fileName);
};

#endif // MKTOOLS_H
