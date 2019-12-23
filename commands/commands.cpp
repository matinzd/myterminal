#include "headers/commands.h"
#include <iostream>
#include <stdlib.h>
#include "headers/sysinfo.h"
#include <string.h>
#include "headers/bashloop.h"
#include <string>
#include <sstream>
#include <regex>
#include <utils/database.h>

string extractCommandName(string command) {
    std::regex r(R"([^\W_]+(?:['_-][^\W_]+)*)");
    smatch m;
    for( sregex_iterator i = sregex_iterator(command.begin(), command.end(), r); i != sregex_iterator(); i++ ) {
        m = *i;
        break;
    }
    return m.str();
}

void Commands::runCommand(string command, int *directory_id) {
    if( extractCommandName(command) == "clear" ) {
        Commands::clear();
//        Database().writeToFile("New data");
        return;
    }

    if(extractCommandName(command) == "exit" ) {
        Commands::exitFromTerminal();
        return;
    }

    if( extractCommandName(command) == "ls" ) {
        Commands::ls(command, *directory_id);
        return;
    }

    if( extractCommandName(command) == "cd" ) {
        Commands::cd(command, &*directory_id);
        return;
    }

    if( extractCommandName(command) == "touch" ) {
        Commands::touch(command, *directory_id);
        return;
    }

    if( extractCommandName(command) == "mkdir" ) {
        Commands::mkdir(command, *directory_id);
        return;
    }

    if( extractCommandName(command) == "rmdir" ) {
        Commands::rmdir(command, *directory_id);
        return;
    }

    if( extractCommandName(command) == "rm" ) {
        Commands::rm(command, *directory_id);
        return;
    }

    cout << "Command " << extractCommandName(command) << " not found :(" << endl;
}
