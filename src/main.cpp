#include <iostream>
#include <stdlib.h>
#include "headers/bashloop.h"
#include "utils/database.h"
#include <sqlite3.h>

using namespace std;

int main(int argc, char *argv[])
{

    Database::init();
    Bashloop::run();

    return 0;
}
