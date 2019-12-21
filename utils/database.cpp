#include "database.h"
#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

Database::Database()
{

}

static int filesCallback(void *listMode, int argc, char **argv, char **azColName){
   int i;


   if( *(int *)listMode == 0 ) {
        printf("%s", "-rwxrwxrwx\t");
   }

   for(i = 0; i<argc; i++){
        printf("%s\t", argv[i]);
//      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }

   if( *(int *)listMode == 0 ) {
       printf("\n");
   }

   return 0;
}


static int dirsCallback(void *listMode, int argc, char **argv, char **azColName){
   int i;



   if( *(int *)listMode == 0 ) {
        printf("%s", "drwxrwxrwx\t");
   }

   for(i = 0; i<argc; i++){
        printf("%s\t", argv[i]);
//      printf("drwxrwxrwx\t%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }

   if( *(int *)listMode == 0 ) {
       printf("\n");
   }

   return 0;
}


void Database::init() {

//    printf("%s", "Initializing db");

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    int resDir;
    int resFile;

    rc = sqlite3_open(dbPath, &db);

    if( rc ) {
//        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    } else {
//        fprintf(stderr, "Opened database successfully\n");
    }

    char* dirSqlStatement = "create table if not exists Directories (" \
            "id integer primary key autoincrement," \
            "name text not null unique,"\
            "parent_id integer,"\
            "permissions int not null default 755,"\
            "dateCreated date not null default current_timestamp,"\
            "dateModified date not null default current_timestamp,"\
            "foreign key(parent_id)"\
            "references Directories(id) on delete cascade"\
            ");";

    char* fileSqlStatement = "create table if not exists Files ("\
            "id integer primary key autoincrement,"\
            "name text not null unique,"\
            "directory_id integer,"\
            "permissions int not null default 644,"\
            "dateCreated date not null default current_timestamp,"\
            "dateModified date not null default current_timestamp,"\
            "foreign key(directory_id)"\
            "references Directories(id) on delete cascade"\
            ");";


    resDir = sqlite3_exec(db, dirSqlStatement, 0, 0, &zErrMsg);
    resFile = sqlite3_exec(db, fileSqlStatement, 0, 0, &zErrMsg);

    if( rc != SQLITE_OK ) {
//        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
//        fprintf(stdout, "Table created successfully\n");
    }

    if( resFile != SQLITE_OK ) {
//        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
//        fprintf(stdout, "Table created successfully\n");
    }



    sqlite3_close(db);
}

void Database::getFilesAndDirectoryLists(int directory_id, int mode) {
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        int resDir;
        int resFile;
        const char* dirData = "Callback function called";
        const int* listMode = &mode;

        rc = sqlite3_open(dbPath, &db);

//        if( rc ) {
//            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//        } else {
//            fprintf(stderr, "Opened database successfully\n");
//        }

        string dirs;
        string files;

        if( directory_id == 0 ) {
            if( mode == 0 ) {
                dirs = "select dateModified, name from Directories where parent_id is null";
                files = "select dateModified, name from Files where directory_id is null";
            }

            if( mode == 1 ) {
                dirs = "select name from Directories where parent_id is null";
                files = "select name from Files where directory_id is null";
            }
        } else {
            if( mode == 0 ) {
                dirs = "select dateModified, name from Directories where parent_id = " + std::to_string(directory_id);
                files = "select dateModified, name from Files where directory_id = " + std::to_string(directory_id);
            }

            if( mode == 1 ) {
                dirs = "select name from Directories where parent_id = " + std::to_string(directory_id);;
                files = "select name from Files where directory_id =" + std::to_string(directory_id);
            }
        }




        resDir = sqlite3_exec(db, dirs.c_str(), dirsCallback, (void*)listMode, &zErrMsg);
        resDir = sqlite3_exec(db, files.c_str(), filesCallback, (void*)listMode, &zErrMsg);


        if( mode == 1 ) {
            printf("\n");
        }
        sqlite3_close(db);
}

void Database::createFile(string fileName, int directory_id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char* dirData = "Callback function called";

    rc = sqlite3_open(dbPath, &db);

    string sql;

    if( directory_id == 0 ) {
        sql = "insert into Files (name) values (\"" + fileName + "\");";
    } else {
        sql = "insert into Files (name, directory_id) values (\"" + fileName + "," + std::to_string(directory_id) + "\");";
    }

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

    if( rc != SQLITE_OK ) {
        printf("%s\n", "File exists!");
    }

    sqlite3_close(db);
}

static int pathCallback(void *data, int argc, char **argv, char **azColName){
   string da = *(string *)data;
   cout << da.c_str();
   return 0;
}


string Database::getPath(int directory_id)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char* dirData = "Callback function called";

    rc = sqlite3_open(dbPath, &db);

    string* data;

    string sql = "WITH RECURSIVE path(level, name, parent_id) AS ("\
                "SELECT 0, name, parent_id "\
                    "FROM Directories "\
                    "WHERE id = 12 "\
                    "UNION ALL "\
                    "SELECT path.level + 1, "\
                           "Directories.name, "\
                           "Directories.parent_id "\
                    "FROM Directories "\
                    "JOIN path ON Directories.id = path.parent_id "\
                "),"\
                "path_from_root AS ("\
                    "SELECT name "\
                    "FROM path "\
                    "ORDER BY level DESC "\
                ")"\
                "SELECT group_concat(name, '/') "\
                "FROM path_from_root;";

    rc = sqlite3_exec(db, sql.c_str(), pathCallback, (void*)data, &zErrMsg);

//    sqlite3_ex
    if( rc != SQLITE_OK ) {
        printf("SQL error: %s\n", zErrMsg);
    }

//    cout << "data is : " << data;
    return "test";

}