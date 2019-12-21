#include <iostream>
#include <stdlib.h>
#include "headers/sysinfo.h"
#include <string>
#include "headers/bashloop.h"
#include "headers/commands.h"
#include "utils/database.h"
#include <string>
#include <sstream>
#include <regex>
#include <math.h>

using namespace std;

string getBashPrefix(int directory);

void Bashloop::run() {
    if( OS_Windows ) {
        system("CLS");
    } else if (!OS_Windows) {
        system("clear");
    }

    int directory_id = 0;

    for(;;) {
//        cout << "Dir id " << directory_id << endl;
        printf("%s", getBashPrefix(directory_id).c_str());
        string command;
        getline(cin, command);
        Commands::runCommand(command, &directory_id);
    }
}

string getBashPrefix(int directory) {
    if( directory == 0 ) {
        return "matin@ubuntu:~$ ";
    } else {
        return "matin@ubuntu:~$/" + Database::getPath(directory) + "/" ;
    }
}
