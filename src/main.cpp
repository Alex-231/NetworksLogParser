// NetworksLogParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	for (int i = 1; i < argc; ++i) {
		cout << endl << "Parsing log " << i << ": " << argv[i] << endl;

		ifstream currentLogFile;
		ofstream currentCsvFile;

		string csvPath = (new string(argv[i]))->append(".csv");

		currentLogFile.open(argv[i], ifstream::in);
		currentCsvFile.open(csvPath, ifstream::out);

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

			currentCsvFile << "rtt min, rtt avg, rtt max, rtt mdev" << endl;
			for (ping rtt : rtts) {
				currentCsvFile << rtt << endl;
			}

			cout << "Done." << endl;
		}
		else if (firstLine.rfind("traceroute") == 0) {
			cout << "Detected traceroute log type..." << endl;
			cout << "ERROR: Not Yet Implemented" << endl;
			cout << "Done." << endl;
		}
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
