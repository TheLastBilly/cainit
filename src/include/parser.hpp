#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "cainit.hpp"

class Parser
{
public:
    Parser();
    Parser( std::string path );

    Parser( const Parser &parser );

    ~Parser();

    CainitError ParseFile();
    CainitError ParseFile( std::string path );

    void ClearBuffer();

private:
    void AddClass( ClassUnit unit );
    void AddElement( VariableElement element );
    ClassUnit &GetLastClass();
    std::vector<ClassUnit> buffer;
    std::string path;
};