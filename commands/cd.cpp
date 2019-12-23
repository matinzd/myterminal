#include "headers/commands.h"
#include "utils/database.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/tokenizer.hpp>


using namespace std;

void Commands::cd(string command, int *directory_id)
{
//    std::regex r(R"([^\W_]+(?:['_-][^\W_]+)*)");
//    smatch m;
//    for( sregex_iterator i = sregex_iterator(command.begin(), command.end(), r); i != sregex_iterator(); i++ ) {
//        m = *i;
//        if( !boost::equals(m.str(), "cd") ) {
////            if(boost::equals(m.str(), ".."))
//        }
//    }


        string cmd = "cd";
        size_t index = command.find(cmd);
        string options = command.substr(index + cmd.length(), command.length());
        boost::trim(options);

        if( boost::equals(options, "..") ) {
            Database::goToParentDirectory(&*directory_id);
            return;
        }

        regex r("^(..\/)*?(\/$|(\/?[a-zA-Z_0-9-]+)+)?$");
        smatch m;

        boost::char_separator<char> sep("/");
        if( regex_search(options, m, r) ) {
            boost::tokenizer<boost::char_separator<char>> tokens(options, sep);
            for (const string& t : tokens)
            {
                if( boost::equals(t, "..") ) {
                    Database::goToParentDirectory(&*directory_id);
                } else {
                    Database::changeDirectory(t, &*directory_id);
                }
            }
        }




}
