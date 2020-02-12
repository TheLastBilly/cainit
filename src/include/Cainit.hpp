#pragma once

#include <iostream>
#include <vector>

namespace Cainit
{
    enum class ErrorValue
    {
        NO_FILE_ERROR,
        NO_PATH_ERROR,
        FILE_FORMAT_ERROR,
        FILE_PATH_ERROR,
        A_OK
    };
    class Variable
    {
    public:
        Variable( std::string type, std::string value );        
        Variable( const Variable & variable );
        std::string type, value;
    };
    typedef std::vector<Variable> variable_v;

    class Header
    {
    public:
        Header( std::string name );
        Header( const Header &header );
        std::string name;
    };
    typedef std::vector<Header> header_v;

    class Class
    {
    public:        
        Class( std::string name );
        Class( const Class &c );
        std::string name;
        variable_v variables;
    };
    typedef std::vector<Class> class_v;

    class File
    {
    public:
        File( std::string name );
        File( std::string name, header_v headers, class_v classes );
        File( const File &f );
        ~File();
        bool IsEmpty();
        void Clear();
        ErrorValue WriteToDirectory( std::string dir );
        std::string name;
        header_v headers;
        class_v classes;
    };
    typedef std::vector<File> file_v;

}