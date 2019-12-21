#include "headers/commands.h"
#include "utils/database.h"

void Commands::ls(string command, int directory_id)
{

    if( command.find("-l") != std::string::npos ) {
        Database::getFilesAndDirectoryLists(directory_id, 0);
    } else {
        Database::getFilesAndDirectoryLists(directory_id, 1);
    }

}
