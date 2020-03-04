// cainit - Parser.cpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include "include/Parser.hpp"

Parser::Parser()
{}

Parser::Parser( const Parser &parser )
{
    files = parser.files;
}

Parser::~Parser()
{}

Cainit::ErrorValue 
Parser::ParseFile( std::string path )
{
    if(path.empty())
        return Cainit::ErrorValue::NO_PATH_ERROR;

    std::ifstream file(path.c_str(), std::fstream::in);
    if(!file.is_open())
        return Cainit::ErrorValue::FILE_PATH_ERROR;

    Cainit::ErrorValue error = Cainit::ErrorValue::A_OK;
    
    std::string line;
    ParserBuffer buffer;
    while( std::getline(file, line) )
    {
        buffer.line_count++;
        if(line[0] == '#' || line.empty())
            continue;
        error = ParseLine( line, buffer );
        if(error == Cainit::ErrorValue::FILE_FORMAT_ERROR)
        {
            std::stringstream ss;
            ss << "Error in line " << buffer.line_count << ": " << line << "\n";
            error_line = ss.str();
            return error;
        }
    }
    buffer.file.classes = buffer.classes;
    buffer.file.headers = buffer.headers;
    files.push_back(buffer.file);
    return error;
}

Cainit::ErrorValue 
Parser::ParseLine( std::string line, ParserBuffer &buff )
{
    if(line.size() < 3)
        return Cainit::ErrorValue::A_OK;
    bool has_set_get = true;
    static const 
        Cainit::ErrorValue on_error = Cainit::ErrorValue::FILE_FORMAT_ERROR;
    static const
        Cainit::ErrorValue on_success = Cainit::ErrorValue::A_OK;
    if(!fil(line, ";", end) || !fil_l(line, " ", tar) || end < tar)
        return Cainit::ErrorValue::FILE_FORMAT_ERROR;
    else if(fil(line,"file", pos) && pos < end )
    {
        buff.has_file = true;
        buff.file.classes = buff.classes;
        buff.file.headers = buff.headers;
        if(!buff.file.IsEmpty())
        {
            files.push_back(buff.file);
            buff.classes.clear();
            buff.headers.clear();
            buff.file.Clear();
        }
        buff.file.name = line.substr(pos + 5, end - (pos + 5));
        buff.has_class = false;
    }
    else if(fil(line,"class", pos) && pos < end)
    {
        if(!buff.has_file)
            return on_error;
        line = line.substr(pos + 6, end - (pos + 6));
        buff.classes.push_back( Cainit::Class(line) );
        buff.has_class = true;
    }
    else if(fil(line, "header", pos) && pos < end)
    {
        if(!buff.has_file)
            return on_error;
        
        line = line.substr(pos + 7, end - (pos + 7));
        buff.headers.push_back( Cainit::Header(line) );
    }
    else if(fil(line, "derived", pos) && pos < end)
    {
        if(!buff.has_class)
            return on_error;

        line = line.substr( pos + 8, end - (pos + 8) );        
        buff.classes.back().derived = line;
    }
    else if(fil(line, "function", pos) && pos < end)
    {
        if(!buff.has_class)
            return on_error;

        line = line.substr( pos + 9, end - (pos + 9) );

        //Get the type
        if((pos = line.find(" ")) == std::string::npos)
            return on_error;
        type_b = line.substr( 0, pos );
        
        //Get the name
        pos++;
        if((end = line.find(" ", pos)) == std::string::npos)
            return on_error;
        name_b = line.substr( pos, end - pos );
        std::cout << name_b << "\n";
        
        //Get the parameters
        if((line.size() - end -1) < 1)
            return on_error;
        param_b = line.substr( end+1, std::string::npos );

        buff.classes.back().functions.push_back( Cainit::Function( type_b, name_b, param_b ) );
    }
    else
    {
        if(!buff.has_class)
            return on_error;
        if(fil(line, "no_set_get:", pos) && tar > pos)
        {
            pos += 11;
            has_set_get = false;
        }
        else
        {
            pos = 0;            
        }
        buff.classes.back().variables.push_back(
            Cainit::Variable( line.substr(pos, tar - pos), line.substr(tar+1, end-tar-1), has_set_get )
        );
    }
    return on_success;
}

inline bool Parser::fil( std::string line, const char * find, size_t & pos)
{
    return (pos = line.find(find)) != std::string::npos;
}
inline bool Parser::fil_l( std::string line, const char * find, size_t & pos)
{
    return (pos = line.find_last_of(find, std::string::npos)) != std::string::npos;
}