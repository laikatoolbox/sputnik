#include <string>
#include <map>

namespace Sputnik {
    class Namespace {
    private:
        std::map<std::string, std::string> values;
        std::multimap<std::string, std::string> objects;
    public:
        void printData() const {
        }
    };
}