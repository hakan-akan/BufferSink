#ifndef IITPSERVERCONNECTIONFACTORY_H
#define IITPSERVERCONNECTIONFACTORY_H


#include "Poco/Net/Net.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "IITPServerParams.h"
#include "IITPRequestHandlerFactory.h"


namespace Innovative {

using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;

class IITPServerConnectionFactory : public Poco::Net::TCPServerConnectionFactory
{
public:
    IITPServerConnectionFactory(IITPServerParams::Ptr pParams, IITPRequestHandlerFactory::Ptr pFactory);

    ~IITPServerConnectionFactory();

    TCPServerConnection* createConnection(const StreamSocket& socket);

private:
    IITPServerParams::Ptr          _pParams;
    IITPRequestHandlerFactory::Ptr _pFactory;
};


}

#endif // IITPSERVERCONNECTIONFACTORY_H
