
#include "IITPServerConnectionFactory.h"
#include "IITPServerConnection.h"
#include "IITPRequestHandlerFactory.h"


namespace Innovative {


IITPServerConnectionFactory::IITPServerConnectionFactory(IITPServerParams::Ptr pParams, IITPRequestHandlerFactory::Ptr pFactory):
    _pParams(pParams),
    _pFactory(pFactory)
{
    poco_check_ptr (pFactory);
}


IITPServerConnectionFactory::~IITPServerConnectionFactory()
{
}


TCPServerConnection* IITPServerConnectionFactory::createConnection(const StreamSocket& socket)
{
    return new IITPServerConnection(socket, _pParams, _pFactory);
}


}
