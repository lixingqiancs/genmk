#include <string>
#include <map>
#include <vector>

using namespace std;

#ifndef MKTOOLS_H
#define MKTOOLS_H

struct Jobs
{
   string target;
   vector<string> prerequisites;
   string command;
};

class MKTools{
	
	private:
		// private
		vector<string> mkArray;
		vector<string> sampleArray;
		vector<map<string,vector<string>>> targetsHead;
		vector<map<string,vector<Jobs>>> targetsBody;
	
	public:
		// public 
		void loadFile();
		void loadFile(const string& fileName);
		void parseFile();
		vector<string> split(const string& str, const string& delim);

};

#endif // MKTOOLS_H