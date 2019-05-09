#include <string>

using namespace std;


namespace logparser {
	namespace logtypes {
		class traceroute {

		public:
			traceroute(vector<string> route1, vector<string> route2, vector<string> route3);
			/*  Empty traceroute constructor.
				This is used for reading from input streams.	*/
			traceroute() : traceroute(vector<string>(), vector<string>(), vector<string>()) {};

			vector<string> route1, route2, route3;

			friend ostream& operator<<(ostream& out, const traceroute& value);
			friend istream& operator>>(istream& in, traceroute& value);
		};
	}
}