#include "IITPServerConnection.h"

#include "Poco/Net/NetException.h"
#include "Poco/Timestamp.h"
#include <memory>

#include "IITPRequestHandler.h"
#include "IITPServerConnection.h"



namespace Innovative {


IITPServerConnection::IITPServerConnection(const StreamSocket& socket, IITPServerParams::Ptr pParams, IITPRequestHandlerFactory::Ptr pFactory):
    Poco::Net::TCPServerConnection(socket),
    _pParams(pParams),
    _pFactory(pFactory)
{
    poco_check_ptr (pFactory);
}


IITPServerConnection::~IITPServerConnection()
{
}


void IITPServerConnection::run()
{
    std::string server = _pParams->getSoftwareVersion();
    IITPServerSession session(socket(), _pParams);
    while (session.hasMoreRequests())
    {
        try
        {
//            HTTPServerResponseImpl response(session);
//            HTTPServerRequestImpl request(response, session, _pParams);

//            Poco::Timestamp now;
//            response.setDate(now);
//            response.setVersion(request.getVersion());
//            response.setKeepAlive(_pParams->getKeepAlive() && request.getKeepAlive() && session.canKeepAlive());
//            if (!server.empty())
//                response.set("Server", server);
            try
            {
                std::auto_ptr<IITPRequestHandler> pHandler(_pFactory->createRequestHandler());
                if (pHandler.get())
                {
//                    if (request.expectContinue())
//                        response.sendContinue();

                    pHandler->handleRequest(session);
                    //session.setKeepAlive(_pParams->getKeepAlive() && response.getKeepAlive() && session.canKeepAlive());
                }
                else sendErrorResponse(session, IITP_NOT_IMPLEMENTED);
            }
            catch (Poco::Exception&)
            {
              //  if (!response.sent())
                 //   sendErrorResponse(session, IITP_INTERNAL_SERVER_ERROR);
                throw;
            }
        }
        catch (Poco::Net::NoMessageException&)
        {
            break;
        }
        catch (Poco::Net::MessageException&)
        {
            //sendErrorResponse(session, HTTPResponse::HTTP_BAD_REQUEST);
        }
    }
}


void IITPServerConnection::sendErrorResponse(IITPServerSession& session, IITPStatus status)
{
//    HTTPServerResponseImpl response(session);
//    response.setVersion(HTTPMessage::HTTP_1_1);
//    response.setStatusAndReason(status);
//    response.setKeepAlive(false);
//    response.send();
//    session.setKeepAlive(false);
}


}
