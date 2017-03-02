
#include "IITPServerSession.h"


namespace Innovative {


IITPServerSession::IITPServerSession(const StreamSocket& socket, IITPServerParams::Ptr pParams):
	HTTPSession(socket, pParams->getKeepAlive()),
	_firstRequest(true),
	_keepAliveTimeout(pParams->getKeepAliveTimeout()),
	_maxKeepAliveRequests(pParams->getMaxKeepAliveRequests())
{
	setTimeout(pParams->getTimeout());
	this->socket().setReceiveTimeout(pParams->getTimeout());
}


IITPServerSession::~IITPServerSession()
{
}


bool IITPServerSession::hasMoreRequests()
{
	if (!socket().impl()->initialized()) return false;

	if (_firstRequest)
	{
		_firstRequest = false;
		--_maxKeepAliveRequests;
        return socket().poll(getTimeout(), Poco::Net::Socket::SELECT_READ);
	}
	else if (_maxKeepAliveRequests != 0 && getKeepAlive())
	{
		if (_maxKeepAliveRequests > 0) 
			--_maxKeepAliveRequests;
        return buffered() > 0 || socket().poll(_keepAliveTimeout, Poco::Net::Socket::SELECT_READ);
	}
	else return false;
}


SocketAddress IITPServerSession::clientAddress()
{
	return socket().peerAddress();
}


SocketAddress IITPServerSession::serverAddress()
{
	return socket().address();
}


}
