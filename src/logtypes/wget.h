#include <string>

using namespace std;


namespace logparser {
	namespace logtypes {
		class wget {

		public:
			wget(string throughput);
			/*  Empty wget constructor.
				This is used for reading from input streams.	*/
			wget() : wget("? KB/s") {};

			string throughput;

			friend ostream& operator<<(ostream& out, const wget& value);
			friend istream& operator>>(istream& in, wget& value);
		};
	}
}