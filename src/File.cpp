#include "Cainit.hpp"

using namespace Cainit;

File::File( std::string name ):
name(name)
{}

File::File( std::string name, header_v headers, class_v classes ):
name(name), headers(headers), classes(classes)
{}

File::File( const File &f )
{
    name = f.name;
    headers = f.headers;
    classes = f.classes;
}

bool File::IsEmpty()
{
    return (headers.empty() && classes.empty());
}

void File::Clear()
{
    classes.clear();
    headers.empty();
}

ErrorValue File::BuildFiles()
{
    if(IsEmpty())
        return ErrorValue::FILE_EMPTY_ERROR;
    ErrorValue error = ErrorValue::A_OK;
    error = BuildHeader();
    if(error != ErrorValue::A_OK)
        return error;
    error = BuildSource();
    if(error != ErrorValue::A_OK)
        return error;
    return error;
}

ErrorValue File::BuildSource()
{
    
}

ErrorValue File::BuildHeader()
{
    std::stringstream ss, getset, vars, con;
    ss << "#pragma once\n\n";

    for( Header h : headers )
    {
        ss << "#include " << h.name << "\n";
    }

    ss << "\n\n";
    std::string varUpper;

    for( Class c : classes )
    {
        //Variables methods and declarations
        for( Variable var : c.variables )
        {
            varUpper = FirstUpper(var.name);
            getset 
                << "\t// " << var.name << " gets and sets\n"
                << "\t" << var.type << " Get" << varUpper << "() const;\n"
                << "\t" << "void Set" << varUpper << "( " << var.type << " " << var.name[0] << " );\n";
            vars 
                << "\t" << var.type << var.name << ";\n";
        }

        ss 
        //Class declaration
            << "class " << c.name << "\n"
            << "{\npublic:\n"
        //Class constructor        
            << "\t" << c.name << "();";

        //Copy constructor        
        ss
            << "\t" << c.name << "( const " << c.name << " &" << c.name[0] << ");\n"
        //Class destructor        
            << "\t~" << c.name << "();\n";
        
        //Add get and set functions
        ss << "\n" << getset.str();

        //Add variable declarations
        ss 
            << "private:\n" 
            << vars.str()
            << "};";
    }

    declarations.name = name + std::string(".hpp");
    declarations.contents = ss.str();

    return ErrorValue::A_OK;
}