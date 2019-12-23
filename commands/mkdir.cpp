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
    string options = command.substr(command.find_last_of("mkdir") + 1, command.length());
    boost::trim(options);
    Database::makeDirectory(options, directory_id);
}
