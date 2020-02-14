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

std::string Variable::FirstUpper( )
{
    std::string r;
    r += toupper(name[0]);
    r += name.substr(1,std::string::npos);
    return r;
}

inline std::string Variable::GetFuncDeclaration()
{
    return (get_func_dec = type + " Get" + FirstUpper() + "() const;");
}

std::string Variable::GetFuncDefinition( std::string class_name )
{
    if(get_func_dec.empty())
        GetFuncDeclaration();
    size_t func_t = (type + " ").size();    
    std::stringstream ss;
    ss 
        << type << " " << class_name << "::" << get_func_dec.substr(func_t, func_t- get_func_dec.size() -2) << "\n"
        << "{\n"
        << "\treturn " << name << ";\n"
        << "}";
    return (get_func_def = ss.str());
}

inline std::string Variable::SetFuncDeclaration()
{
    return (set_func_dec = "void Set" + FirstUpper() + "( " + type + name[0] +" );");
}

std::string Variable::SetFuncDefinition( std::string class_name )
{
    if(set_func_dec.empty())
        SetFuncDeclaration();
    std::stringstream ss;
    ss
        << "void " << class_name << "::" << set_func_dec.substr(5, 4 - set_func_dec.size()) << "\n"
        << "{\n"
        << "\t" << name << " = " <<  name[0] << ";\n"
        << "}";
    return (set_func_def = ss.str());
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