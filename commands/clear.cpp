#include "headers/commands.h"
#include "headers/sysinfo.h"
#include <stdlib.h>
#include <stdio.h>

void Commands::clear()
{
    if( OS_Windows ) {
        system("CLS");
    } else if (!OS_Windows) {
        system("clear");
    }

}

void Commands::exitFromTerminal()
{
    exit(EXIT_SUCCESS);
}
