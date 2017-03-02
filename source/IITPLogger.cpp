#include "Poco/Net/ServerSocket.h"
#include "IITPLogger.h"
#include "IITPServer.h"
#include "IITPServerParams.h"
#include "IITPRequestProcess.h"

using Poco::Net::ServerSocket;
using Innovative::IITPServer;
using Innovative::IITPServerParams;
using Innovative::RequestHandlerFactory;

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
        // Command and data sockets
        typedef unsigned short ushort;

        unsigned short cport = (ushort) config().getInt("IITPLoggerServer.cport", 9980);
        unsigned short dport = (ushort) config().getInt("IITPLoggerServer.dport", 9981);
        std::string home     = config().getString("IITPLoggerServer.home", Poco::Path::home());

        logger().information("Listening port...");

        // set-up a server command&data sockets
        ServerSocket svsc(cport);
        ServerSocket svsd(dport);

        IITPServer srv(new RequestHandlerFactory(svsd, home), svsc, new IITPServerParams);

        srv.start();

        getchar();

        srv.stop();

        logger().information("Goodbye...");
    }
    return Application::EXIT_OK;
}
