#include "headers/commands.h"
#include "utils/database.h"
#include <sstream>
#include <regex>
#include <iostream>

using namespace std;

string extract(string command) {
    std::regex r(R"([^\W_]+(?:['_-][^\W_]+)*)");
    smatch m;
    for( sregex_iterator i = sregex_iterator(command.begin(), command.end(), r); i != sregex_iterator(); i++ ) {
        m = *i;
        if( !(m.str().find("touch") != std::string::npos) ) {
            break;
        }
    }
    return m.str();
}

void Commands::touch(string command, int directory_id)
{
   Database::createFile(extract(command), directory_id);
}
