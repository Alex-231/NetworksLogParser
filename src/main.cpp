//
// NetworksLogParser - Alex Newark
//
// This log parser was created for a uni assessment.
// It currently supports parsing of ping, traceroute and wget logs.
// Following a somewhat Object-Oriented design, the program is fairly extendable,
// and more log types could be added in future.
//
// Potential Future Improvements:
// - Implementing a base class for logtypes, with a virtual function to detect if a log is of that type
//	 so that detecting a log type and handling output could be done genericly.
// - Better error handling of logs, at the moment suitable logs are expected.
// - More information from logs, eg ping hopcount.
//


#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "logtypes/wget.h"
#include "logtypes/ping.h"
#include "logtypes/traceroute.h"

using namespace std;
using namespace logparser::logtypes;

int main(int argc, char* argv[])
{
    std::cout << "Log Parser" << endl; 

	// If there's no files to parse, tell the user.
	if (argc < 2) {
		cout << "Drag files onto the exe or launch with paths as arguments." << endl;
	}

	// For every file to parse...
	for (int i = 1; i < argc; ++i) {
		cout << endl << "Parsing log " << i << ": " << argv[i] << endl;

		ifstream currentLogFile;
		ofstream currentCsvFile;

		// Create and open a csv file to 
		string csvPath = (new string(argv[i]))->append(".csv");

		currentLogFile.open(argv[i], ifstream::in);
		currentCsvFile.open(csvPath, ifstream::out);

		// Get the first line to determine the log type.
		string firstLine;
		getline(currentLogFile, firstLine);

		if (firstLine.rfind("PING") == 0) {
			cout << "Detected ping log type..." << endl;
			vector<ping> rtts;
			ping rtt;

			while (currentLogFile >> rtt) {
				rtts.push_back(rtt);
				cout << "Parsed RTT: " << rtt.rttAvg << " ms" << endl;
			}

			cout << "Writing csv file... (" << csvPath << ')' << endl;

			for (ping rtt : rtts) {
				currentCsvFile << rtt << endl << endl;
			}

			cout << "Done." << endl;
		}
		else if (firstLine.rfind("traceroute") == 0) {
			cout << "Detected traceroute log type..." << endl;

			vector<traceroute> traceroutes;
			traceroute _traceroute;

			while (currentLogFile >> _traceroute) {
				traceroutes.push_back(_traceroute);
				cout << "Parsed Traceroute: " << endl << _traceroute;
			}

			traceroutes.push_back(_traceroute);
			cout << "Parsed Traceroute." << endl;

			cout << "Writing csv file... (" << csvPath << ')' << endl;

			for (traceroute _traceroute : traceroutes) {
				currentCsvFile << _traceroute;
			}

			cout << "Done." << endl;
		}
		// If the log isn't a traceroute or ping, wget is assumed.
		else {
			cout << "Detected throughput log type..." << endl;
			vector<wget> throughputs;
			wget throughput;

			while (currentLogFile >> throughput) {
				throughputs.push_back(throughput);
				cout << "Parsed Throughput: " << throughput.kbps << " KB/s" << endl;
			}

			float throughputSum = 0;
			for (wget throughput : throughputs) {
				throughputSum += throughput.kbps;
			}
			float throughputAverage = throughputSum / throughputs.size();
			cout << "Average Throughput: " << throughputAverage << " KB/s" << endl;

			cout << "Writing csv file... (" << csvPath << ')' << endl;

			currentCsvFile << "Throughputs (KB/s),";
			for (wget throughput : throughputs) {
				currentCsvFile << throughput << ",";
			}

			currentCsvFile << endl << "Average Throughput (KB/s)," << throughputAverage;

			cout << "Done." << endl;
		}

		currentLogFile.close();
		currentCsvFile.close();
	}

	cout << endl << "Press any key to exit." << endl;

	getchar();

	return 0;
}
