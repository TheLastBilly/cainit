// cainit - File.cpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "include/Cainit.hpp"

using namespace Cainit;

File::File()
{}

File::File( std::string name ):
name(name)
{}

File::File( std::string name, header_v headers, class_v classes ):
name(name), headers(headers), classes(classes)
{}

File::~File()
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
    if(declarations.IsEmpty())
        BuildHeader();

    std::stringstream ss, o_ss;
    ss 
        << "#include " << '"' << declarations.name << '"' << "\n\n";
        
    for( Class c : classes )
    {
        ss 
            << c.name << "::" << c.name << "()\n{}\n\n"
            << c.name << "::~" << c.name << "()\n{}\n\n"
            << c.name << "::" << c.name << "( const " << c.name << " &" << c.name[0] << " )\n{\n";
        for( Variable var : c.variables )
        {
            ss << "\t" << var.name << " = " << c.name[0] << "." << var.name << ";\n";
        }
        ss << "}\n\n";
        for( Variable var : c.variables )
        {
            if(!var.has_set_get)
                continue;
            ss
                << var.GetFuncDefinition( c.name ) << "\n"
                << var.SetFuncDefinition( c.name ) << "\n\n";
        }
    }

    definitions.name = name + ".cpp";
    definitions.contents = ss.str();
    return ErrorValue::A_OK;
}

ErrorValue File::BuildHeader()
{
    std::stringstream ss, getset, vars, con;
    ss << "#pragma once\n\n";

    for( Header h : headers )
    {
        ss << "#include " << h.name << "\n";
    }

    ss << "\n";

    for( Class c : classes )
    {
        //Variables methods and declarations
        for( Variable var : c.variables )
        {
            vars 
                << "\t" << var.type << " " << var.name << ";\n";
            if(!var.has_set_get)
                continue;
            getset
                << "\t" << var.GetFuncDeclaration() << "\n"
                << "\t" << var.SetFuncDeclaration() << "\n";
        }

        ss 
        //Class declaration
            << "class " << c.name;
        if(c.derived.size() > 0)
            ss << ": public " << c.derived;
        ss
            << "\n{\npublic:\n"
        //Class constructor        
            << "\t" << c.name << "();\n"
        //Copy constructor        
            << "\t" << c.name << "( const " << c.name << " &" << c.name[0] << ");\n"
        //Class destructor        
            << "\t~" << c.name << "();\n";
        
        //Add get and set functions
        ss << "\n" << getset.str();

        //Add variable declarations
        ss 
            << "\nprivate:\n" 
            << vars.str()
            << "};";
    }

    declarations.name = name + std::string(".hpp");
    declarations.contents = ss.str();

    return ErrorValue::A_OK;
}