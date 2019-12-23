#include "headers/commands.h"
#include "utils/database.h"
#include <sstream>
#include <regex>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/tokenizer.hpp>
#include <regex>

using namespace std;


void Commands::touch(string command, int directory_id)
{
    string cmd = "touch";
    size_t index = command.find(cmd);
    string options = command.substr(index + cmd.length(), command.length());
    boost::trim(options);
    regex r("^(..\/)*?(\/$|(\/?[a-zA-Z_0-9-]+)+)?$");
    smatch m;

    boost::char_separator<char> sep("/");
    boost::tokenizer<boost::char_separator<char>> tokens(options, sep);
    for (const string& t : tokens)
    {
        Database::createFile(t, *&directory_id);
        break;
    }
}
