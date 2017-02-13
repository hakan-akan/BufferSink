#ifndef IITPSERVER_H
#define IITPSERVER_H

#include "Poco/Net/Net.h"
#include "Poco/Net/TCPServer.h"

#include "IITPRequestHandlerFactory.h"
#include "IITPServerParams.h"

namespace Innovative {

class IITPServer : public Poco::Net::TCPServer
{
public:
    IITPServer(IITPRequestHandlerFactory::Ptr pFactory, const Poco::Net::ServerSocket& socket, IITPServerParams::Ptr pParams);
    IITPServer(IITPRequestHandlerFactory::Ptr pFactory, Poco::ThreadPool& threadPool, const Poco::Net::ServerSocket& socket, IITPServerParams::Ptr pParams);

    ~IITPServer();

};

}

#endif // IITPSERVER_H
