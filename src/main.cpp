/********************************************************************************************************************
* File: main.cpp 
* Author: Chandler Kramer 
* Project: Book Management System 
********************************************************************************************************************/
// Database Reference: https://www.sqlite.org/cintro.html#convenience_wrappers_around_core_routines
// 1.) Add Books (Database Maybe?)
// 2.) Display Books (Print Books Title and Author)
// 3.) Change Books 
// 4.) Implementing Changes 
// 5.) Check Books (Search Algorithm? )
// 6.) Buy Books 

/********************************************************************************************************************
* Imports 
********************************************************************************************************************/
#include "dataFuncs.h"

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

