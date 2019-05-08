#include <string>

using namespace std;


namespace logparser {
	namespace logtypes {
		class ping {

		public:
			ping(float rttMin, float rttAvg, float rttMax, float rttMDev, vector<float> rtts);
			/*  Empty wget constructor.
				This is used for reading from input streams.	*/
			ping() : ping(0, 0, 0, 0, vector<float>()) {};

			float rttMin, rttAvg, rttMax, rttMDev;
			vector<float> rtts;

			friend ostream& operator<<(ostream& out, const ping& value);
			friend istream& operator>>(istream& in, ping& value);
		};
	}
}