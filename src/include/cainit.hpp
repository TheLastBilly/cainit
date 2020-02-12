#pragma once 

#include <iostream>
#include <vector>

enum class CainitError
{
    NO_FILE_ERROR,
    NO_PATH_ERROR,
    FILE_FORMAT_ERROR,
    A_OK
};

class HeaderElement
{
public:
    HeaderElement();
    HeaderElement(std::string header);
    ~HeaderElement();
    std::string header;
};

class VariableElement
{
public: 
    VariableElement();
    VariableElement( std::string type, std::string name );
    ~VariableElement();
    std::string type,name;
};

class ClassUnit
{
private:
    typedef std::vector<VariableElement> VariableVec;
    typedef std::vector<HeaderElement> HeaderVec;
public:
    ClassUnit();
    ClassUnit( std::string name );
    ClassUnit( std::string name, VariableVec variables, HeaderVec headers );
    std::string name;
    VariableVec variables;
    std::vector<HeaderElement> headers;
};