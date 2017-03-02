#ifndef IITPREQUESTHANDLER_H
#define IITPREQUESTHANDLER_H

#include "IITPServerSession.h"
#include "Poco/Path.h"
namespace Innovative {

class IITPRequestHandler
{
public:
    IITPRequestHandler();

    virtual ~IITPRequestHandler();

    virtual void handleRequest(IITPServerSession &) = 0;

private:
    IITPRequestHandler(const IITPRequestHandler&);
    IITPRequestHandler& operator = (const IITPRequestHandler&);
};



}

#endif // IITPREQUESTHANDLER_H
