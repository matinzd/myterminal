#include "headers/commands.h"
#include "utils/database.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/tokenizer.hpp>
#include <regex>
#include <iostream>

void Commands::rm(string command, int directory_id)
{
    string cmd = "rm";
    size_t index = command.find(cmd);
    string options = command.substr(index + cmd.length(), command.length());
    boost::trim(options);
    regex r("^(..\/)*?(\/$|(\/?[a-zA-Z_0-9-]+)+)?$");
    smatch m;
    boost::char_separator<char> sep("/");
    boost::tokenizer<boost::char_separator<char>> tokens(options, sep);
    for (const string& t : tokens)
    {
        Database::removeFile(t, *&directory_id);
    }
}

void Commands::rmdir(string command, int directory_id)
{
    string cmd = "rmdir";
    size_t index = command.find(cmd);
    string options = command.substr(index + cmd.length(), command.length());
    boost::trim(options);
    regex r("^(..\/)*?(\/$|(\/?[a-zA-Z_0-9-]+)+)?$");
    smatch m;

    boost::char_separator<char> sep("/");
    if( regex_search(options, m, r) ) {
        boost::tokenizer<boost::char_separator<char>> tokens(options, sep);
        for (const string& t : tokens)
        {
            Database::removeDirectory(t, *&directory_id);
        }
    }
}
