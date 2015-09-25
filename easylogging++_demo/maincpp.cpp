#include "boost/filesystem.hpp"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

static unsigned int idx = 0;

void rolloutHandler(const char* filename, std::size_t size)
{
	std::stringstream stream;
	stream << filename << "." << ++idx;
	boost::filesystem::rename(filename, stream.str().c_str());
}

int main(int argc, char** argv)
{
	el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);
	el::Configurations conf("log.conf");
	el::Loggers::reconfigureAllLoggers(conf);
	el::Helpers::installPreRollOutCallback(rolloutHandler);

	for (int i = 0; i < 100000; ++i)
	{
		LOG(INFO) << "Test==========================================================";
	}

	el::Helpers::uninstallPreRollOutCallback();
	return 0;
}