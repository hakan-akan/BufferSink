
#include "IITPServerParams.h"


namespace Innovative {

IITPServerParams::IITPServerParams():
	_timeout(60000000),
	_keepAlive(true),
	_maxKeepAliveRequests(0),
	_keepAliveTimeout(15000000)
{
}


IITPServerParams::~IITPServerParams()
{
}

	
void IITPServerParams::setServerName(const std::string& serverName)
{
	_serverName = serverName;
}
	

void IITPServerParams::setSoftwareVersion(const std::string& softwareVersion)
{
	_softwareVersion = softwareVersion;
}


void IITPServerParams::setTimeout(const Poco::Timespan& timeout)
{
	_timeout = timeout;
}

	
void IITPServerParams::setKeepAlive(bool keepAlive)
{
	_keepAlive = keepAlive;
}

	
void IITPServerParams::setKeepAliveTimeout(const Poco::Timespan& timeout)
{
	_keepAliveTimeout = timeout;
}

	
void IITPServerParams::setMaxKeepAliveRequests(int maxKeepAliveRequests)
{
	poco_assert (maxKeepAliveRequests >= 0);
	_maxKeepAliveRequests = maxKeepAliveRequests;
}
	

}
