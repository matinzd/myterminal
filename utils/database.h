#include <string>

#ifndef DATABASE_H
#define DATABASE_H

using namespace std;

class Database
{
public:
    Database();
    static void init();
    static void getFilesAndDirectoryLists(int directory_id, int mode);
    static void createFile(string fileName, int directory_id);
    static string getPath(int directory_id);
    void writeToFile(string data);
};

#define dbPath "data.db"

#endif // DATABASE_H
