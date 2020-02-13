#include "Cainit.hpp"

using namespace Cainit;

Variable::Variable( std::string type, std::string name ):
type(type), name(name)
{}

Variable::Variable( const Variable &variable )
{
    type = variable.type;
    name = variable.name;
}

Header::Header( std::string name ):
name(name)
{}

Header::Header( const Header &header )
{
    name = header.name;
}

Class::Class( std::string name ):
name(name)
{}

Class::Class( const Class &c )
{
    name = c.name;
    variables = c.variables;
}

std::string FirstUpper( std::string s )
{
    std::string r;
    r += toupper(s[0]);
    r += s.substr(1,std::string::npos);
    return r;
}