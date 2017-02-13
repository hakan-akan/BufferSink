

#ifndef IITPServerParams_INCLUDED
#define IITPServerParams_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/TCPServerParams.h"


namespace Innovative {


class IITPServerParams: public Poco::Net::TCPServerParams
{
public:
    typedef Poco::AutoPtr<IITPServerParams> Ptr;
	
    IITPServerParams();

	void setServerName(const std::string& serverName);

	const std::string& getServerName() const;

	void setSoftwareVersion(const std::string& softwareVersion);

	const std::string& getSoftwareVersion() const;

	void setTimeout(const Poco::Timespan& timeout);
		
	const Poco::Timespan& getTimeout() const;
		
	void setKeepAlive(bool keepAlive);
		
	bool getKeepAlive() const;
		
	void setKeepAliveTimeout(const Poco::Timespan& timeout);
		
	const Poco::Timespan& getKeepAliveTimeout() const;
	
	void setMaxKeepAliveRequests(int maxKeepAliveRequests);
		
	int getMaxKeepAliveRequests() const;

protected:
    virtual ~IITPServerParams();

private:
	std::string    _serverName;
	std::string    _softwareVersion;
	Poco::Timespan _timeout;
	bool           _keepAlive;
	int            _maxKeepAliveRequests;
	Poco::Timespan _keepAliveTimeout;
};


//
// inlines
//
inline const std::string& IITPServerParams::getServerName() const
{
	return _serverName;
}


inline const std::string& IITPServerParams::getSoftwareVersion() const
{
	return _softwareVersion;
}


inline const Poco::Timespan& IITPServerParams::getTimeout() const
{
	return _timeout;
}


inline bool IITPServerParams::getKeepAlive() const
{
	return _keepAlive;
}


inline int IITPServerParams::getMaxKeepAliveRequests() const
{
	return _maxKeepAliveRequests;
}


inline const Poco::Timespan& IITPServerParams::getKeepAliveTimeout() const
{
	return _keepAliveTimeout;
}


}


#endif
