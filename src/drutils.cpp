#include <sstream>

bool existline(std::stringstream const & ss)
{
    return ss.rdbuf()->in_avail();
}
