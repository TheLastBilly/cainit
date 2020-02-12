#include "parser.hpp"

Parser::Parser()
{}

Parser::Parser( std::string path ):
    path(path)
{}

Parser::Parser( const Parser & parser )
{
    path = parser.path;
    buffer = parser.buffer;
}

Parser::~Parser()
{}

CainitError Parser::ParseFile()
{
    if(path.empty())
        return CainitError::NO_PATH_ERROR;

    return ParseFile( path );   
}

static inline bool fil( std::string line, const char * find, size_t & pos)
{
    return (pos = line.find("class")) != std::string::npos;
}

CainitError Parser::ParseFile( std::string path )
{
    if(path.empty())
        return CainitError::NO_PATH_ERROR;
    CainitError error = CainitError::A_OK;
    ClearBuffer();

    std::ifstream file(path.c_str(), std::fstream::in);
    std::string line;
    
    size_t pos = 0, end = 0, tar = 0;
    bool has_class = false;
    while( std::getline(file, line) )
    {
        if(!fil(line, ";", end) || !fil(line, " ", tar) || end < tar)
            continue;
        
        if(fil(line,"class", pos))
        {
            line = line.substr(pos + 6, end - (pos + 6));
            AddClass( ClassUnit( line ) );
            has_class = true;
        }
        else
        {
            if(!has_class)
            {
                error = CainitError::FILE_FORMAT_ERROR;
                break;
            }
            AddElement( VariableElement( 
                line.substr(0, tar),
                line.substr(tar+1, end - (tar+1))
            ));
        }
    }
    return error;
}

void Parser::AddClass( ClassUnit unit )
{
    buffer.push_back(unit);
}

void Parser::AddElement( VariableElement element )
{
    GetLastClass().elements.push_back(element);
}

ClassUnit &Parser::GetLastClass()
{
    if(buffer.empty())
    {
        AddClass( ClassUnit("") );
    }
    return buffer.back();
}