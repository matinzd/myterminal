#include <stdio.h>
#include <string>
#ifndef COMMANDS_H
#define COMMANDS_H

using namespace std;

class Commands {
public:
    static void runCommand(string command, int *directory_id);
    static void clear();
    static void ls(string command, int directory_id);
    static void cd(string command, int *directory_id);
    static void touch(string command, int directory_id);
    static void exitFromTerminal();
    static void rm(int fileId);
    static void rmdir(int dirId);
};

static const string CLEAR = "clear";

#endif // COMMANDS_H
