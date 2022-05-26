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

void addBook(sqlite3 *db, string title, string author, int rc);
void printDatabase(sqlite3 *db);
void advancedQuery(sqlite3 *db, string column, int option);
/********************************************************************************************************************
* Function: Callback 
* Desc: Prints the results of database search to the screen 
********************************************************************************************************************/
static int callback(void *data, int argc, char** argv, char** azColName){
    int i; 
    // fprintf(stderr, "%s\n", (const char*)data); 
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
    Book drgnRep; 
    poppyWar.author = "R.F Kuang"; 
    poppyWar.title = "The Poppy War"; 
    GoT.author = "George R.R. Martin"; 
    GoT.title = "Game of Thrones"; 
    drgnRep.author = poppyWar.author; 
    drgnRep.title = "The Dragon Republic";
    sqlite3 *db; 
    int rc; 

    string sql = "DROP TABLE IF EXISTS BOOKS;" 
                "CREATE TABLE BOOKS(Id INT, Title TEXT, Author TEXT);";
    
    rc = sqlite3_open("bookdb.db", &db); 
    rc = sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    addBook(db, "The War on Normal People", "Andrew Yang", rc); 
    addBook(db,"The Audacity of Hope", "Barack Obama", rc);
    addBook(db,poppyWar.title, poppyWar.author, rc);
    addBook(db, GoT.title, GoT.author, rc); 
    addBook(db, drgnRep.title, drgnRep.author, rc); 
    addBook(db, "Forward", "Andrew Yang", rc); 
    printDatabase(db); 
    advancedQuery(db, "Andrew Yang", 1); 
    sqlite3_close(db); 

    return 0; 
}

void addBook(sqlite3 *db, string title, string author, int rc){
    Book newBook; 
    newBook.title = title; 
    newBook.author = author; 

    sqlite3_stmt *stmt; 

    if (rc != SQLITE_OK){
        // const char *sqlite3_errmsg(sqlite3*)
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)); 
        // int sqlite3_close(sqlite3 *) 
        sqlite3_close(db); 
    }

    string sql = "INSERT INTO BOOKS VALUES(last_insert_rowid(), ?, ?); ";

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0); 

    if (rc == SQLITE_OK){
        sqlite3_bind_text(stmt,1, newBook.title.c_str(), -1, NULL);
        sqlite3_bind_text(stmt,2, newBook.author.c_str(), -1, NULL);
        
    } else{
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db)); 
    }
    sqlite3_step(stmt); 
    sqlite3_finalize(stmt);
}

void printDatabase(sqlite3 *db){

    string data = "CALLBACK FUNCTION"; 
    string sql = "SELECT * FROM BOOKS;"; 

    int rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data.c_str(), NULL); 

    if(rc!=SQLITE_OK){
        cerr<<"Error SELECT"<<endl; 
    }
    else{
        cout<<"Operation OK!"<<endl; 
    }
}

void advancedQuery(sqlite3 *db, string column, int option) {
    string sql; 
    string trilogy; 
    string call; 
    if(option == 1){
        call = "Author Search";
        sql = "SELECT * FROM BOOKS WHERE AUTHOR = "; 
        trilogy = sql + '\"'+ column + '\"'+";";
    };
    if(option == 2){
        call = "Book Search";
        sql = "SELECT * FROM BOOKS WHERE TITLE = "; 
        trilogy = sql + '\"'+ column + '\"'+";";
    };

    cout<<trilogy<<endl; 
    
    //sqlite3_stmt *stmt; 

    int rc = sqlite3_exec(db, trilogy.c_str(), callback, (void*)call.c_str(), NULL); 

    if(rc!=SQLITE_OK){
        cerr<<"Error SELECT"<<endl; 
    }
    else{
        cout<<"Query Successful!"<<endl; 
    }
}