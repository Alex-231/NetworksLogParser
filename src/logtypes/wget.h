#include <string>

using namespace std;


namespace logparser {
	namespace logtypes {
		class wget {

		public:
			wget(float kbps);
			/*  Empty wget constructor.
				This is used for reading from input streams.	*/
			wget() : wget(0) {};

			float kbps;

			friend ostream& operator<<(ostream& out, const wget& value);
			friend istream& operator>>(istream& in, wget& value);
		};
	}
}