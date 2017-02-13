#include "IITPServer.h"
#include "IITPServerConnectionFactory.h"

namespace Innovative {



IITPServer::IITPServer(IITPRequestHandlerFactory::Ptr pFactory, const  Poco::Net::ServerSocket& socket, IITPServerParams::Ptr pParams):
    TCPServer(new IITPServerConnectionFactory(pParams, pFactory), socket, pParams)
{
}


IITPServer::IITPServer(IITPRequestHandlerFactory::Ptr pFactory, Poco::ThreadPool& threadPool, const Poco::Net::ServerSocket& socket, IITPServerParams::Ptr pParams):
    TCPServer(new IITPServerConnectionFactory(pParams, pFactory), threadPool, socket, pParams)
{
}


IITPServer::~IITPServer()
{
}


}
