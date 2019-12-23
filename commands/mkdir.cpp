#include "utils/database.h"
#include "headers/commands.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/tokenizer.hpp>

void Commands::mkdir(string command, int directory_id)
{
    string cmd = "mkdir";
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
            Database::makeDirectory(t, *&directory_id);
        }
    }
}
