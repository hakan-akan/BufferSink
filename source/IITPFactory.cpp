#include "IITPFactory.h"
#include "Poco/SingletonHolder.h"

namespace Innovative {


CommandFactory::CommandFactory()
{
    registerBuiltins();
}


CommandFactory::~CommandFactory()
{
}


void CommandFactory::registerCommandClass(const std::string& className, CommandInstantiator* pFactory)
{
    _commandFactory.registerClass(className, pFactory);
}


Command* CommandFactory::createCommand(const std::string& className) const
{
    return _commandFactory.createInstance(className);
}

namespace
{
    static Poco::SingletonHolder<CommandFactory> sh;
}


CommandFactory& CommandFactory::defaultFactory()
{
    return *sh.get();
}


void CommandFactory::registerBuiltins()
{
    using Poco::Instantiator;
    _commandFactory.registerClass("STOR" , new Instantiator<StartStoreCommand, Command>);
    _commandFactory.registerClass("ETOR" , new Instantiator<EndStoreCommand  , Command>);
    _commandFactory.registerClass("QUIT" , new Instantiator<QuitCommand      , Command>);
    _commandFactory.registerClass("CUST" , new Instantiator<CustomCommand    , Command>);
    _commandFactory.registerClass("MKDIR", new Instantiator<MakeDirCommand   , Command>);
    _commandFactory.registerClass("RNTO" , new Instantiator<RenameCommand    , Command>);
    _commandFactory.registerClass("DELE" , new Instantiator<DeleteCommand    , Command>);
    _commandFactory.registerClass("CWD"  , new Instantiator<ChangeDirCommand , Command>);
    _commandFactory.registerClass("PWD"  , new Instantiator<CurrentDirCommand, Command>);

    void setFile(const std::string& name);

    void rmdir(const std::string& path);

}

}
