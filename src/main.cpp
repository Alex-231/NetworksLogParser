// NetworksLogParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "logtypes/wget.h"

using namespace std;
using namespace logparser::logtypes;

int main(int argc, char* argv[])
{

#if DEBUG
    std::cout << "Hello World!\n"; 
#endif // DEBUG

	for (int i = 1; i < argc; ++i) {

#if DEBUG
		cout << "argv[" << i << "] is " << argv[i] << endl;
#endif // DEBUG

		ifstream currentLogFile;
		ofstream currentCsvFile;

		currentLogFile.open(argv[i], ifstream::in);
		currentCsvFile.open((new string(argv[i]))->append(".csv"), ifstream::out);

		string firstLine;
		getline(currentLogFile, firstLine);

		if (firstLine.rfind("PING") == 0) {
			// ping file
		}
		else if (firstLine.rfind("traceroute") == 0) {
			// traceroute file
		}
		else {
			vector<wget> throughputs;
			wget throughput;

			while (currentLogFile >> throughput) {
				throughputs.push_back(throughput);
			}

			for (wget throughput : throughputs) {
				currentCsvFile << throughput << ",";
			}
		}

		currentLogFile.close();
		currentCsvFile.close();
	}

#if DEBUG
	getchar();
#endif // DEBUG

	return 0;
}
