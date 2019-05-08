#include <regex>

#include "wget.h";

namespace logparser {
	namespace logtypes {

		wget::wget(string throughput) {
			this->throughput = throughput;
		}

		ostream& operator<<(ostream& out, const wget& value)
		{
			return out << value.throughput;
		}

		istream& operator>>(istream& in, wget& value)
		{
			string currentLine;
			getline(in, currentLine);

			regex throughputRegex("[0-9.]{1,} [M/K]B/s");
			smatch throughputMatch;

			if (regex_search(currentLine, throughputMatch, throughputRegex))
			{
				value.throughput = throughputMatch[0];
				return in;
			}

			return in;
		}

	}
}