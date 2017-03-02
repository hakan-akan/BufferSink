#ifndef IITPSERVERCONNECTION_H
#define IITPSERVERCONNECTION_H

#include "Poco/Net/Net.h"
#include "Poco/Net/TCPServerConnection.h"
#include "IITPRequestHandlerFactory.h"
#include "IITPServerParams.h"
#include "IITPServerSession.h"

namespace Innovative {


enum IITPStatus
{
    IITP_CONTINUE                        = 100,
    IITP_SWITCHING_PROTOCOLS             = 101,
    IITP_OK                              = 200,
    IITP_NOT_IMPLEMENTED                 = 201,
    IITP_INTERNAL_SERVER_ERROR           = 202
};


class IITPServerConnection: public Poco::Net::TCPServerConnection
{
public:
    IITPServerConnection(const StreamSocket& socket, IITPServerParams::Ptr pParams, IITPRequestHandlerFactory::Ptr pFactory);

    virtual ~IITPServerConnection();

    void run();

protected:
    void sendErrorResponse(IITPServerSession& session, IITPStatus status);

private:
    IITPServerParams::Ptr          _pParams;
    IITPRequestHandlerFactory::Ptr _pFactory;
};


}


#endif // IITPSERVERCONNECTION_H
