// cainit - Cainit.hpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <cstdio>

namespace Cainit
{
    enum class ErrorValue
    {
        NO_FILE_ERROR,
        NO_PATH_ERROR,
        FILE_FORMAT_ERROR,
        FILE_PATH_ERROR,
        FILE_EMPTY_ERROR,
        A_OK
    };

    std::string GetErrorDescription( ErrorValue err );

    class Variable
    {
    public:
        Variable( std::string type, std::string name );        
        Variable( const Variable & variable );

        std::string GetFuncDeclaration();
        std::string SetFuncDeclaration();

        std::string GetFuncDefinition( std::string class_name );
        std::string SetFuncDefinition( std::string class_name );

        std::string 
            type, name,
            get_func_dec, get_func_def,
            set_func_dec, set_func_def;

    private:
        std::string FirstUpper();    
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

    class CodeFile
    {
    public:    
        CodeFile();
        CodeFile(std::string name, std::string contents);
        std::string 
            name,
            contents;
        bool IsEmpty();
    };

    class File
    {
    public:
        File();
        File( std::string name );
        File( std::string name, header_v headers, class_v classes );
        File( const File &f );
        ~File();
        bool IsEmpty();
        void Clear();
        ErrorValue BuildFiles();

        std::string name;
        header_v headers;
        class_v classes;

        CodeFile definitions, declarations;
        
        ErrorValue BuildHeader();
        ErrorValue BuildSource();   
    };
    typedef std::vector<File> file_v;

    std::string FirstUpper( std::string s );
    inline std::string GetGetter( Variable var );
}