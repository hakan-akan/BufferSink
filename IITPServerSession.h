


#ifndef IITPServerSession_INCLUDED
#define IITPServerSession_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/HTTPSession.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/HTTPServerSession.h"
#include "IITPServerParams.h"
#include "Poco/Timespan.h"


namespace Innovative {

using Poco::Net::StreamSocket;
using Poco::Net::SocketAddress;

class IITPServerSession: public Poco::Net::HTTPSession
{
public:
    IITPServerSession(const StreamSocket& socket, IITPServerParams::Ptr pParams);

    virtual ~IITPServerSession();
				
	bool hasMoreRequests();
	
	bool canKeepAlive() const;
	
	SocketAddress clientAddress();
		
	SocketAddress serverAddress();
		
private:
	bool           _firstRequest;
	Poco::Timespan _keepAliveTimeout;
	int            _maxKeepAliveRequests;
};


//
// inlines
//
inline bool IITPServerSession::canKeepAlive() const
{
	return _maxKeepAliveRequests != 0;
}


}


#endif
