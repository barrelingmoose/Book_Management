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
* Class: Book 
* Desc: Creates default class classifier for Books 
********************************************************************************************************************/
class Book{
    public: 
        string title;  
        string author; 
};

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

