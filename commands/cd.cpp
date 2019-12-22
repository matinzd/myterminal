#include "headers/commands.h"
#include "utils/database.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>

void Commands::cd(string command, int *directory_id)
{
    std::regex r(R"([^\W_]+(?:['_-][^\W_]+)*)");
    smatch m;
    for( sregex_iterator i = sregex_iterator(command.begin(), command.end(), r); i != sregex_iterator(); i++ ) {
        m = *i;
        if( !boost::equals(m.str(), "cd") ) {
            if(boost::equals(m.str(), ".."))
        }
    }


}
