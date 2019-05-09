#include <regex>

#include "wget.h";

namespace logparser {
	namespace logtypes {

		wget::wget(float kbps) {
			this->kbps = kbps;
		}

		ostream& operator<<(ostream& out, const wget& value)
		{
			return out << value.kbps;
		}

		istream& operator>>(istream& in, wget& value)
		{
			while (!in.eof()) {
				string currentLine;
				getline(in, currentLine);

				regex throughputRegex("[0-9.]{1,} [M/K]B/s");
				smatch throughputMatch;

				if (regex_search(currentLine, throughputMatch, throughputRegex))
				{
					string matchString = throughputMatch[0];

					// Normalise the throughput value.
					int multiplier = 1;
					switch (matchString[matchString.length() - 4]) {
					case 'G':
						multiplier = 1000000;
						break;
					case 'M':
						multiplier = 1000;
						break;
					case 'K':
					default:
						break;
					}

					value.kbps = stof(matchString) * multiplier;
					return in;
				}
			}

			return in;
		}

	}
}