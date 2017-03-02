#include "IITPRequestProcess.h"
#include "IITPFactory.h"

#include "Poco/AutoPtr.h"
#include "Poco/ErrorHandler.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/File.h"
#include "Poco/StringTokenizer.h"

namespace Innovative {

using Poco::AutoPtr;
using Poco::ErrorHandler;
using Poco::Util::Application;
using Poco::Path;
using Poco::File;
using Poco::StringTokenizer;

DataChannelConsumer::DataChannelConsumer(ServerSocket &socket, const Poco::Path &path):
    _activity(this, &DataChannelConsumer::runActivity),
    _socket(socket), _path(path)
{
}

bool DataChannelConsumer::start()
{
    _path.setFileName("copy.bin");

    _ostr.open(_path.toString());
    if(!_ostr.is_open()) {
        return false;
    }
    _activity.start();
    return true;
}

bool DataChannelConsumer::stop()
{
    bool stopped = true;
    _activity.stop();
    try {
        _activity.wait(100);
    } catch (Poco::TimeoutException &) {
        stopped = false;
    }

    _ostr.close();

    return stopped;
}

std::string DataChannelConsumer::currentDir()
{
    return _path.toString();
}

void DataChannelConsumer::currentDir(const std::string &dir)
{
    _path = Poco::Path(dir);
}

bool DataChannelConsumer::isRunning()
{
    return _activity.isRunning();
}

void DataChannelConsumer::runActivity()
{
    Application& app = Application::instance();

    app.logger().information("Activity started.");

    Poco::Timespan timeout(250000);
    if (_socket.poll(timeout, Poco::Net::Socket::SELECT_READ))
    {
        try
        {
            StreamSocket ss = _socket.acceptConnection();
            // enabe nodelay per default: OSX really needs that
            ss.setNoDelay(true);

            int total = 0;

            while (!_activity.isStopped())
            {
                char data[256 * 1024];
                memset(data, 0, sizeof(data));
                int n = ss.receiveBytes(data, sizeof(data));
                if (n == 0) break;
                data[n] = 0;

                total += n;
                _ostr.write(data, n);
            }
            app.logger().information(Poco::format("Received %d ints", total));

        }
        catch (Poco::Exception& exc)
        {
            app.logger().information("Exception");
            ErrorHandler::handle(exc);
        }
        catch (std::exception& exc)
        {
            app.logger().information("exception");
            ErrorHandler::handle(exc);
        }
        catch (...)
        {
            app.logger().information("Error...");
            ErrorHandler::handle();
        }
    }


    app.logger().information("Activity done.");
}

RequestHandler::RequestHandler(DataChannelConsumer &dchan,  const Poco::Path &path)
    : _dchan(dchan), _path(path)
{
}

bool RequestHandler::start()
{
    return _dchan.start();
}

bool RequestHandler::stop()
{
    bool stat = _dchan.stop();

    return stat;
}

std::string RequestHandler::currentDir()
{
    return _dchan.currentDir();
}

void RequestHandler::currentDir(const std::string &dir)
{
    _dchan.currentDir(dir);
}

void RequestHandler::handleRequest(IITPServerSession &sess)
{
    Application& app = Application::instance();

    Poco::Timespan timeout(250000);
    if (sess.socket().poll(timeout, Poco::Net::Socket::SELECT_READ))
    {
        int sz = 0;
        try
        {
            std::string data(256 * 1024, ' ');
            sz = sess.socket().receiveBytes(&data[0], data.size());

            if (sz == 0) {
                sess.socket().sendBytes("200 OK\r\n", 8);
                return;
            }

            //app.logger().information("Received a command  : " + std::string(data));

            StringTokenizer tokens(data, " \r", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);

            if ((tokens.count() % 2) == 0) return throw std::runtime_error("nonsense");

            AutoPtr<Innovative::Command> pCmd(Innovative::CommandFactory::defaultFactory().createCommand(tokens[0]));
            for (size_t i = 1; i < tokens.count(); i += 2) {
                pCmd->setProperty(tokens[i], tokens[i+1]);
            }

            bool ok = pCmd->execute(this);
            pCmd->status(sess, ok);

        } catch (Poco::Exception &exc) {
            app.logger().information(exc.displayText());
        }

    }

}

RequestHandlerFactory::RequestHandlerFactory(Poco::Net::ServerSocket &socket, const Poco::Path &path)
    : _dchan(socket, path), _path(path)
{
}



IITPRequestHandler *RequestHandlerFactory::createRequestHandler()
{
    return new RequestHandler(_dchan, _path);
}

}
