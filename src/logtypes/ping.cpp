#include <regex>
#include <sstream>

#include "ping.h";

namespace logparser {
	namespace logtypes {

		ping::ping(float rttMin, float rttAvg, float rttMax, float rttMDev) {
			this->rttMin = rttMin;
			this->rttAvg = rttAvg;
			this->rttMax = rttMax;
			this->rttMDev = rttMDev;
		}

		ostream& operator<<(ostream& out, const ping& value)
		{
			return out << value.rttMin << ',' << value.rttAvg << ',' << value.rttMax << ',' << value.rttMDev;
		}

		istream& operator>>(istream& in, ping& value)
		{
			while (!in.eof()) {
				string currentLine;
				getline(in, currentLine);

				regex pingRegex("[0-9.]{1,}/[0-9.]{1,}/[0-9.]{1,}/[0-9.]{1,}");
				smatch pingMatch;

				if (regex_search(currentLine, pingMatch, pingRegex))
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
			}

			return in;
		}

	}
}