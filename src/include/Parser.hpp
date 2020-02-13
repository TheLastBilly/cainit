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

    Cainit::file_v GetFiles();
    void SetFiles( Cainit::file_v files );

private:
    struct parser_buff
    {
        bool 
            has_file = false,
            has_class = false;
        int line_count = 0;
        Cainit::class_v classes;
        Cainit::header_v headers;
        Cainit::File file;
    };

    Cainit::ErrorValue ParseLine( std::string line, parser_buff &buff );

    Cainit::file_v files;

    //Varaibles and methods used by the parsing process
    size_t pos = 0, end = 0, tar = 0;
    static inline bool fil( std::string line, const char * find, size_t & pos);
    std::string error_line;
};