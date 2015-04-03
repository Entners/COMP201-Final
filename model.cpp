#include "model.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor initializes the object
Model::Model() {
    int     error = 0;
    error = sqlite3_open("ljdata.sl3", &conn);
    
    if (error)
    {
        puts("Can not open database");
    }
    
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
}

// Given a word, what rhymes with it?
// TODO
vector<string> Model::getCategoriesForWord(string word) {
    vector<string> result;
    int     error = 0;
    int     rec_count = 0;
    const char      *errMSG;
    const char      *tail;

    error = sqlite3_prepare_v2(conn, "select word, category from rhymes order by word",1000, &res, &tail);
    
    if (error != SQLITE_OK) {
        puts("We did not get any data!");
    }
    
    puts("==========================");
    
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        printf("%s|", sqlite3_column_text(res, 0));
        printf("%s|", sqlite3_column_text(res, 1));
        rec_count++;
    }
    return result;
}

vector<string> Model::getWordsInCategory(string category) {
    
}

bool Model::gameOver() {
    return false;
}

