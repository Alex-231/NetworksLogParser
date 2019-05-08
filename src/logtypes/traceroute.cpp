#include <regex>
#include <sstream>
#include <iostream>

#include "traceroute.h"

namespace logparser {
	namespace logtypes {

		traceroute::traceroute(vector<string> route1, vector<string> route2, vector<string> route3) {
			this->route1 = route1;
			this->route2 = route2;
			this->route3 = route3;
		}

		ostream& operator<<(ostream& out, const traceroute& value)
		{
			for (string point : value.route1) {
				out << point << ',';
			}
			out << endl;

			if (value.route2 != value.route1) {
				for (string point : value.route2) {
					out << point << ',';
				}
				out << endl;
			}

			if (value.route3 != value.route2) {
				for (string point : value.route3) {
					out << point << ',';
				}
				out << endl;
			}

			return out;
		}

		istream& operator>>(istream& in, traceroute& value)
		{
			int point = 0;
			while (!in.eof()) {
				string currentLine;
				getline(in, currentLine);

				regex tracerouteRegex("(((\\S+) \\((\\S+)\\)){0,1}  [0-9.]{1,} ms|\\*)");
				smatch tracerouteMatch;

				int pos = 0;
				for (int i = 0; i < 3; i++) {
					string substring = currentLine.substr(pos);
					if (regex_search(substring, tracerouteMatch, tracerouteRegex))
					{
						if (tracerouteMatch[0] == "*") {
							// If there's no point here, move to next line.
							continue;
						}

						regex pointRegex("((\\S+) \\((\\S+)\\)){1}");
						smatch pointMatch;

						string match = tracerouteMatch[0];
						if (regex_search(match, pointMatch, pointRegex))
						{
							if (i == 0) {
								value.route1.push_back(pointMatch[0]);
								value.route2.push_back("^");
								value.route3.push_back("^");
							}
							else if (i == 1) {
								value.route2[point] = pointMatch[0];
							}
							else if (i == 2) {
								value.route3[point] = pointMatch[0];
							}
						}
						else if (i == 0) {
							// If for some reason the first point can't be parsed, move to the next line.
							continue;
						}

						pos += tracerouteMatch[0].length();
					}
					else if (i < 2) {
						return in;
					}
				}
				point++;
			}

			return in;
		}

	}
}