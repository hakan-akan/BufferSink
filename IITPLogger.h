#ifndef IITP_LOGGER_H
#define IITP_LOGGER_H


//
// HTTPFormServer.cpp
//
// $Id: //poco/Main/Net/samples/HTTPFormServer/src/HTTPFormServer.cpp#5 $
//
// This sample demonstrates the HTTPServer and HTMLForm classes.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//
#if 0

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"

using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Net::MessageHeader;
using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::CountingInputStream;
using Poco::NullOutputStream;
using Poco::StreamCopier;

#endif


#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include <iostream>
//
#include "IITPRequestHandlerFactory.h"
#include "IITPRequestHandler.h"


using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;


using Innovative::IITPRequestHandlerFactory;
using Innovative::IITPRequestHandler;




class FormRequestHandler: public IITPRequestHandler
{
public:
    FormRequestHandler()
    {
    }

    void handleRequest()
    {
        Application& app = Application::instance();
        app.logger().information("Received a request... ");

   }
};


class FormRequestHandlerFactory: public IITPRequestHandlerFactory
{
public:
    FormRequestHandlerFactory()
    {
    }

    IITPRequestHandler* createRequestHandler()
    {
        return new FormRequestHandler;
    }
};



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
