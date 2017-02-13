#include "Poco/Net/ServerSocket.h"
#include "IITPLogger.h"
#include "IITPServer.h"
#include "IITPServerParams.h"

using Poco::Net::ServerSocket;
using Innovative::IITPServer;
using Innovative::IITPServerParams;


IITPLoggerServerApp::IITPLoggerServerApp(): _helpRequested(false)
{
}

IITPLoggerServerApp::~IITPLoggerServerApp()
{
}

void IITPLoggerServerApp::initialize(Poco::Util::Application &self)
{
    loadConfiguration(); // load default configuration files, if present
    ServerApplication::initialize(self);
}

void IITPLoggerServerApp::uninitialize()
{
    ServerApplication::uninitialize();
}

void IITPLoggerServerApp::defineOptions(Poco::Util::OptionSet &options)
{
    ServerApplication::defineOptions(options);

    options.addOption(
                Option("help", "h", "display help information on command line arguments")
                .required(false)
                .repeatable(false));
}

void IITPLoggerServerApp::handleOption(const std::string &name, const std::string &value)
{
    ServerApplication::handleOption(name, value);

    if (name == "help")
        _helpRequested = true;
}

void IITPLoggerServerApp::displayHelp()
{
    HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("A logger server.");
    helpFormatter.format(std::cout);
}

int IITPLoggerServerApp::main(const std::vector<std::string> &/*args*/)
{
    if (_helpRequested)
    {
        displayHelp();
    }
    else
    {
        unsigned short port = (unsigned short) config().getInt("IITPLoggerServer.port", 9980);

        logger().information("Listening port...");

        // set-up a server socket
        ServerSocket svs(port);

        IITPServer srv(new FormRequestHandlerFactory, svs, new IITPServerParams);

        srv.start();

        getchar();

        srv.stop();

        logger().information("Goodbye...");
    }
    return Application::EXIT_OK;
}
