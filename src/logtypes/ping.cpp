#include <regex>
#include <sstream>

#include "ping.h";

namespace logparser {
	namespace logtypes {

		ping::ping(float rttMin, float rttAvg, float rttMax, float rttMDev, vector<float> rtts) {
			this->rttMin = rttMin;
			this->rttAvg = rttAvg;
			this->rttMax = rttMax;
			this->rttMDev = rttMDev;
			this->rtts = rtts;
		}

		ostream& operator<<(ostream& out, const ping& value)
		{
			out << "rtts (ms),";

			for (float rtt : value.rtts) {
				out << rtt << ',';
			}
			out << endl << "rtt min/avg/max/mdev," << value.rttMin << ',' << value.rttAvg << ',' << value.rttMax << ',' << value.rttMDev;

			return out;
		}

		istream& operator>>(istream& in, ping& value)
		{
			value.rtts = vector<float>();

			while (!in.eof()) {
				string currentLine;
				getline(in, currentLine);

				regex pingEndRegex("[0-9.]{1,}/[0-9.]{1,}/[0-9.]{1,}/[0-9.]{1,}");
				regex pingRegex("[0-9.]{1,} ms");
				smatch pingMatch;

				if (regex_search(currentLine, pingMatch, pingEndRegex))
				{
					string matchString = pingMatch[0];
					stringstream matchStream(matchString);
					
					string rttMinString, rttAvgString, rttMaxString, rttMDevString;

					getline(matchStream, rttMinString, '/');
					getline(matchStream, rttAvgString, '/');
					getline(matchStream, rttMaxString, '/');
					getline(matchStream, rttMDevString, ' ');

					value.rttMin = stof(rttMinString);
					value.rttAvg = stof(rttAvgString);
					value.rttMax = stof(rttMaxString);
					value.rttMDev = stof(rttMDevString);
					return in;
				}
				else if (regex_search(currentLine, pingMatch, pingRegex))
				{
					value.rtts.push_back(stof(pingMatch[0]));
				}
			}

			return in;
		}

	}
}