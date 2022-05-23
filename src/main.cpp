// Database Reference: https://www.sqlite.org/cintro.html#convenience_wrappers_around_core_routines
// 1.) Add Books (Database Maybe?)
// 2.) Display Books (Print Books Title and Author)
// 3.) Change Books 
// 4.) Implementing Changes 
// 5.) Check Books (Search Algorithm? )
// 6.) Buy Books 
/********************************************************************************************************************
* File: main.cpp 
* Author: Chandler Kramer 
* Project: Book Management System 
********************************************************************************************************************/

/********************************************************************************************************************
* Imports 
********************************************************************************************************************/
#include <iostream> 
#include <string>
#include <stdio.h> 
#include <fstream> 
// This was a pain in the ass 
// This helped: https://developer.fedoraproject.org/tech/database/sqlite/about.html
// But not entirely
#include <sqlite3.h> 
using namespace std; 

/********************************************************************************************************************
* Function: Callback 
* Desc: Not Sure haha 
********************************************************************************************************************/
static int callback(void *data, int argc, char** argv, char** azColName){
    int i; 
    fprintf(stderr, "%s\n", (const char*)data); 
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;  
}


/********************************************************************************************************************
* Class: Book 
* Desc: Creates default class classifier for Books 
********************************************************************************************************************/
class Book{
    public: 
        string title;  
        string author; 
};

/********************************************************************************************************************
* Function: main 
* Desc: 
********************************************************************************************************************/
int main(int argc, char** argv){
    Book poppyWar; 
    Book GoT; 
    poppyWar.author = "R.F Kuang"; 
    poppyWar.title = "The Poppy War"; 
    GoT.author = "George R.R. Martin"; 
    GoT.title = "Game of Thrones"; 

    string database = "bookdb.csv";
    sqlite3 *db; 
    int rc; 
    rc = sqlite3_open("bookdb.db", &db); 
    string query = "SELECT * FROM BOOKS;"; 
    sqlite3_exec(db, query.c_str(), callback, NULL, NULL); 
    string sql = ("INSERT INTO BOOKS VALUES(1, 'The Poppy War', 'R.F Kuang');" 
                "INSERT INTO BOOKS VALUES(2, 'Game of Thrones', 'George R.R. Martin');");
    char *messageError; 
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &messageError); 

    if (rc != SQLITE_OK) {
        cerr<<"Error Insert"<<endl; 
        sqlite3_free(messageError); 
    }
    else{
        fprintf(stderr, "Records Created successfully\n"); 
    }
    cout<<"STATE OF TABLE AFTER INSERT"<<endl; 
    sqlite3_exec(db, query.c_str(), callback, NULL, NULL); 
    
    sqlite3_close(db); 
}

