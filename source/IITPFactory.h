#ifndef IITPPROTOCOLFACTORY_H
#define IITPPROTOCOLFACTORY_H


#include "Poco/Foundation.h"
#include "Poco/DynamicFactory.h"
#include "IITPCommands.h"

namespace Innovative {

using Poco::AbstractInstantiator;
using Poco::DynamicFactory;

class CommandFactory
{
public:
    typedef AbstractInstantiator<Command>   CommandInstantiator;

    CommandFactory();

    ~CommandFactory();

    void registerCommandClass(const std::string& className, CommandInstantiator* pFactory);

    Command* createCommand(const std::string& className) const;

    static CommandFactory& defaultFactory();

private:
    void registerBuiltins();

    DynamicFactory<Command>   _commandFactory;
};


}


#endif // IITPPROTOCOLFACTORY_H
