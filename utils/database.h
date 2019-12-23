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
    static void removeFile(string fileName, int directory_id);
    static string getPath(int directory_id);
    static void goToParentDirectory(int *directory_id);
    static void changeDirectory(string dirName, int *directory_id);
    static void makeDirectory(string dirName,int directory_id);
    static void removeDirectory(string dirName,int directory_id);
};

#define dbPath "data.db"

#endif // DATABASE_H
