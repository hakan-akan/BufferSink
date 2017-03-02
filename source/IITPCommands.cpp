#include "IITPCommands.h"
#include "IITPServerSession.h"

#include "Poco/Format.h"
#include "Poco/Path.h"
#include "Poco/File.h"

namespace Innovative {


Command::Command()
{
}


Command::~Command()
{
}

bool Command::execute(IAppCommand *)
{
    return false;
}

void Command::status(IITPServerSession &, bool )
{

}

void Command::setProperty(const std::string& name, const std::string& /*value*/)
{
    throw Poco::PropertyNotSupportedException(name);
}


std::string Command::getProperty(const std::string& name) const
{
    throw Poco::PropertyNotSupportedException(name);
}

const std::string MakeDirCommand::DIR_NAME = "name";

MakeDirCommand::MakeDirCommand()
{

}

bool MakeDirCommand::execute(IAppCommand */*cmd*/)
{
    return true;
}

void MakeDirCommand::status(IITPServerSession &sess, bool ok)
{
    if (ok)
        sess.socket().sendBytes("200 OK\r\n", 8);
    else
        sess.socket().sendBytes("200 OK\r\n", 8);
}

void MakeDirCommand::setProperty(const std::string &name, const std::string &value)
{
    FastMutex::ScopedLock lock(_mutex);

    if (name == DIR_NAME) {
        _name = value;
    } else
        Command::setProperty(name, value);
}

std::string MakeDirCommand::getProperty(const std::string &name) const
{
    if (name == DIR_NAME)
        return _name;
    else
        return Command::getProperty(name);
}

StartStoreCommand::StartStoreCommand()
{

}

bool StartStoreCommand::execute(IAppCommand *cmd)
{
    return cmd->start();
}

void StartStoreCommand::status(IITPServerSession &sess, bool ok)
{
    if (ok)
        sess.socket().sendBytes("200 OK\r\n", 8);
    else
        sess.socket().sendBytes("200 OK\r\n", 8);
}

void StartStoreCommand::setProperty(const std::string &name, const std::string &value)
{
    Command::setProperty(name, value);
}

std::string StartStoreCommand::getProperty(const std::string &name) const
{
    return Command::getProperty(name);
}

EndStoreCommand::EndStoreCommand()
{

}

bool EndStoreCommand::execute(IAppCommand *cmd)
{
    return cmd->stop();
}

void EndStoreCommand::status(IITPServerSession &sess, bool ok)
{
    if (ok)
        sess.socket().sendBytes("200 OK\r\n", 8);
    else
        sess.socket().sendBytes("200 OK\r\n", 8);
}

void EndStoreCommand::setProperty(const std::string &name, const std::string &value)
{
    Command::setProperty(name, value);
}

std::string EndStoreCommand::getProperty(const std::string &name) const
{
    return Command::getProperty(name);
}

CustomCommand::CustomCommand()
{

}

bool CustomCommand::execute(IAppCommand */*cmd*/)
{
    return true;
}

void CustomCommand::status(IITPServerSession &sess, bool ok)
{
    if (ok)
        sess.socket().sendBytes("200 OK\r\n", 8);
    else
        sess.socket().sendBytes("200 OK\r\n", 8);
}


void CustomCommand::setProperty(const std::string &name, const std::string &value)
{
    Command::setProperty(name, value);
}

std::string CustomCommand::getProperty(const std::string &name) const
{
    return Command::getProperty(name);
}

QuitCommand::QuitCommand()
{

}

bool QuitCommand::execute(IAppCommand *cmd)
{
    return true;
}

void QuitCommand::status(IITPServerSession &sess, bool ok)
{
    if (ok)
        sess.socket().close();

}

void QuitCommand::setProperty(const std::string &name, const std::string &value)
{
    Command::setProperty(name, value);
}

std::string QuitCommand::getProperty(const std::string &name) const
{
    return Command::getProperty(name);
}

const std::string RenameCommand::FROM_NAME = "from";
const std::string RenameCommand::TO_NAME   = "to";

RenameCommand::RenameCommand()
{

}

bool RenameCommand::execute(IAppCommand *cmd)
{
    if (!Poco::File(_from).exists() && !Poco::File(_to).exists())
    {
        return true;
    }
    else
        return false;
}

void RenameCommand::status(IITPServerSession &sess, bool ok)
{
    if (ok)
        sess.socket().sendBytes("200 OK\r\n", 8);
    else
        sess.socket().sendBytes("100 NO\r\n", 8);
}

void RenameCommand::setProperty(const std::string &name, const std::string &value)
{
    FastMutex::ScopedLock lock(_mutex);

    if (name == FROM_NAME) {
        _from = value;
    } else if (name == TO_NAME) {
        _to   = value;
    } else
        Command::setProperty(name, value);
}

std::string RenameCommand::getProperty(const std::string &name) const
{
    return Command::getProperty(name);
}

DeleteCommand::DeleteCommand()
{

}

bool DeleteCommand::execute(IAppCommand *cmd)
{

}

void DeleteCommand::status(IITPServerSession &sess, bool ok)
{
    if (ok)
        sess.socket().sendBytes("200 OK\r\n", 8);
    else
        sess.socket().sendBytes("100 NO\r\n", 8);
}

void DeleteCommand::setProperty(const std::string &name, const std::string &value)
{
    Command::setProperty(name, value);
}

std::string DeleteCommand::getProperty(const std::string &name) const
{
    return Command::getProperty(name);
}

const std::string ChangeDirCommand::DIR_NAME = "dir";

ChangeDirCommand::ChangeDirCommand()
{

}

bool ChangeDirCommand::execute(IAppCommand *cmd)
{
    // Check for valid dir string
    if (Poco::Path(_dir).isDirectory())
        cmd->currentDir(_dir);

    return _dir == cmd->currentDir();
}

void ChangeDirCommand::status(IITPServerSession &sess, bool ok)
{
    if (ok)
        sess.socket().sendBytes("200 OK\r\n", 8);
    else
        sess.socket().sendBytes("100 NO\r\n", 8);
}

void ChangeDirCommand::setProperty(const std::string &name, const std::string &value)
{
    FastMutex::ScopedLock lock(_mutex);

    if (name == DIR_NAME) {
        _dir = value;
    } else
        Command::setProperty(name, value);
}

std::string ChangeDirCommand::getProperty(const std::string &name) const
{
    return Command::getProperty(name);
}

CurrentDirCommand::CurrentDirCommand()
{

}

bool CurrentDirCommand::execute(IAppCommand *cmd)
{
    _cdir = cmd->currentDir();
    return !_cdir.empty() ? true : false;
}


void CurrentDirCommand::status(IITPServerSession &sess, bool ok)
{
    if (ok) {
        std::string data;
        Poco::format(data, "%d \"%s\"\r\n", 200, _cdir);
        sess.socket().sendBytes(data.c_str(), (int)data.size());
     } else
        sess.socket().sendBytes("100 NO\r\n", 8);
}

void CurrentDirCommand::setProperty(const std::string &name, const std::string &value)
{
    Command::setProperty(name, value);
}

std::string CurrentDirCommand::getProperty(const std::string &name) const
{
    return Command::getProperty(name);
}

}
