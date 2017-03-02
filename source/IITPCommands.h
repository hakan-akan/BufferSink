#ifndef IITPCOMMANDS_H
#define IITPCOMMANDS_H




#include "Poco/Foundation.h"
#include "Poco/Configurable.h"
#include "Poco/Mutex.h"
#include "Poco/RefCountedObject.h"


namespace Innovative {

using Poco::Configurable;
using Poco::RefCountedObject;
using Poco::FastMutex;

class IITPServerSession;

struct IAppCommand {

    virtual bool start() = 0;
    virtual bool stop()  = 0;
    virtual std::string currentDir() = 0;
    virtual void currentDir(const std::string &dir) = 0;
};


class Command: public Configurable, public RefCountedObject
{
public:
    Command();

    virtual bool execute(IAppCommand *cmd);
    virtual void status(IITPServerSession &sess, bool ok);

    void setProperty(const std::string& name, const std::string& value);
    std::string getProperty(const std::string& name) const;

protected:
    virtual ~Command();

private:
    Command(const Command&);
    Command& operator = (const Command&);
};


class MakeDirCommand : public Command {
public:
    MakeDirCommand();

    bool execute(IAppCommand *cmd);

    void status(IITPServerSession &sess, bool ok);

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

    static const std::string DIR_NAME;

private:
    std::string  _name;
    FastMutex    _mutex;
};

class StartStoreCommand : public Command {
public:
    StartStoreCommand();

    bool execute(IAppCommand *cmd);

    void status(IITPServerSession &sess, bool ok);

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

    static const std::string FILE_NAME;

private:
    std::string  _name;
    FastMutex    _mutex;
};

class EndStoreCommand : public Command {
public:
    EndStoreCommand();

    bool execute(IAppCommand *cmd);

    void status(IITPServerSession &sess, bool ok);

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

private:

};

class CustomCommand : public Command {
public:
    CustomCommand();

    bool execute(IAppCommand *cmd);

    void status(IITPServerSession &sess, bool ok);

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

private:
};

class RenameCommand : public Command {
public:
    RenameCommand();

    bool execute(IAppCommand *cmd);

    void status(IITPServerSession &sess, bool ok);

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

    static const std::string FROM_NAME;
    static const std::string TO_NAME;

private:
    std::string _from;
    std::string _to;
    FastMutex   _mutex;
};

class DeleteCommand : public Command {
public:
    DeleteCommand();

    bool execute(IAppCommand *cmd);

    void status(IITPServerSession &sess, bool ok);

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

private:
};

class ChangeDirCommand : public Command {
public:
    ChangeDirCommand();

    bool execute(IAppCommand *cmd);

    void status(IITPServerSession &sess, bool ok);

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

    static const std::string DIR_NAME;

private:
    std::string _dir;
    FastMutex   _mutex;
};

class CurrentDirCommand : public Command {
public:
    CurrentDirCommand();

    bool execute(IAppCommand *cmd);

    void status(IITPServerSession &sess, bool ok);

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

private:
    std::string _cdir;
};

class QuitCommand : public Command {
public:
    QuitCommand();

    bool execute(IAppCommand *cmd);

    void status(IITPServerSession &sess, bool ok);

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

private:

};


} // namespace Poco

#endif // IITPCOMMANDS_H
