// cainit - Parser.cpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once 

#include <iostream>
#include <vector>

#include "Cainit.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

class Parser
{   
public:
    Parser();
    Parser( const Parser &parser );
    ~Parser();

    Cainit::ErrorValue ParseFile( std::string path );

    Cainit::file_v files;

    std::string error_line;

private:
    struct ParserBuffer
    {
        bool 
            has_file = false,
            has_class = false;
        int line_count = 0;
        Cainit::class_v classes;
        Cainit::header_v headers;
        Cainit::File file;
    };

    Cainit::ErrorValue ParseLine( std::string line, ParserBuffer &buff );

    //Varaibles and methods used by the parsing process
    size_t pos = 0, end = 0, tar = 0;
    static inline bool fil( std::string line, const char * find, size_t & pos);
};