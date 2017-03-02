#ifndef IITP_LOGGER_H
#define IITP_LOGGER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include "Poco/AutoPtr.h"
#include "Poco/ErrorHandler.h"
#include "Poco/Activity.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "IITPRequestHandlerFactory.h"
#include "IITPRequestHandler.h"
#include "IITPServerSession.h"
#include "IITPRequestProcess.h"




using Poco::AutoPtr;
using Poco::Activity;
using Poco::ErrorHandler;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;


using Innovative::IITPRequestHandlerFactory;
using Innovative::IITPRequestHandler;
using Innovative::IITPServerSession;


class IITPLoggerServerApp: public Poco::Util::ServerApplication
{
public:
    IITPLoggerServerApp();

    ~IITPLoggerServerApp();

protected:
    void initialize(Application& self);

    void uninitialize();

    void defineOptions(OptionSet& options);

    void handleOption(const std::string& name, const std::string& value);

    void displayHelp();

    int main(const std::vector<std::string>& args);

private:
    bool _helpRequested;
};

#endif // IITP_LOGGER_H
