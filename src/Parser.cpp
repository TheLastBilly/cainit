#include "Parser.hpp"

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
        error = ParseLine( line, buffer );
        if(error == Cainit::ErrorValue::FILE_FORMAT_ERROR)
        {
            std::stringstream ss;
            ss << "Error in line " << buffer.line_count << ":\t" << line;
            error_line = ss.str();
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
    static const 
        Cainit::ErrorValue on_error = Cainit::ErrorValue::FILE_FORMAT_ERROR;
    static const
        Cainit::ErrorValue on_success = Cainit::ErrorValue::A_OK;
    buff.line_count =+1;
    if(!fil(line, ";", end) || !fil(line, " ", tar) || end < tar)
        return Cainit::ErrorValue::FILE_FORMAT_ERROR;
    else if(fil(line,"file", pos))
    {
        buff.has_file = true;
        buff.file.classes = buff.classes;
        buff.file.headers = buff.headers;
        if(!buff.file.IsEmpty())
        {
            files.push_back(buff.file);
            buff.classes.clear();
            buff.file.Clear();
        }
        buff.file.name = line.substr(pos + 5, end - (pos + 5));
        buff.has_class = false;
    }
    else if(fil(line,"class", pos))
    {
        if(!buff.has_file)
            return on_error;
        line = line.substr(pos + 6, end - (pos + 6));
        buff.classes.push_back( Cainit::Class(line) );
        buff.has_class = true;
    }
    else if(fil(line, "header", pos))
    {
        if(!buff.has_file)
            return on_error;
        
        line = line.substr(pos + 7, end - (pos + 7));
        buff.headers.push_back( Cainit::Header(line) );
    }
    else if(buff.has_class)
    {
        buff.classes.back().variables.push_back(
            Cainit::Variable( line.substr(0, tar), line.substr(tar+1, end-tar-1) )
        );
    }
    return on_success;
}

inline bool Parser::fil( std::string line, const char * find, size_t & pos)
{
    return (pos = line.find(find)) != std::string::npos;
}