#ifndef IITPREQUESTPROCESS_H
#define IITPREQUESTPROCESS_H

#include <string>
#include <fstream>
#include <Poco/Activity.h>
#include <Poco/Net/ServerSocket.h>

#include "IITPCommands.h"
#include "IITPRequestHandler.h"
#include "IITPRequestHandlerFactory.h"

using Poco::Net::ServerSocket;
using Poco::Activity;

namespace Innovative {


class DataChannelConsumer
{
public:
    DataChannelConsumer(ServerSocket& socket, const Poco::Path &path);

    bool start();
    bool stop();
    std::string currentDir();
    void currentDir(const std::string& dir);

    bool isRunning();

protected:
    void runActivity();

private:
    Activity<DataChannelConsumer> _activity;
    ServerSocket&                 _socket;
    std::ofstream                 _ostr;
    Poco::Path                    _path;
};



class RequestHandler: IAppCommand, public IITPRequestHandler
{
public:
    RequestHandler(DataChannelConsumer& dchan, const Poco::Path &path);

    bool start();
    bool stop();
    std::string currentDir();
    void currentDir(const std::string &dir);

    void handleRequest(IITPServerSession &sess);

private:
    DataChannelConsumer  &_dchan;
    const Poco::Path     &_path;
};


class RequestHandlerFactory: public IITPRequestHandlerFactory
{
public:
    RequestHandlerFactory(ServerSocket& socket, const Poco::Path &path);

    IITPRequestHandler *createRequestHandler();

private:
    DataChannelConsumer  _dchan;
    const Poco::Path    &_path;
};

}



#endif // IITPREQUESTPROCESS_H
