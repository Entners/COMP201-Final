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

vector<string> Model::doQuery(string query) {
    vector<string> result;
    int     error = 0;
    int     rec_count = 0;
    const char      *errMSG;
    const char      *tail;
    
    error = sqlite3_prepare_v2(conn, query.c_str(), 1000, &res, &tail);
    
    if (error != SQLITE_OK) {
        return result;
    }
    
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        string row = (char*)sqlite3_column_text(res, 0);
        result.push_back(row);
        rec_count++;
    }
    return result;
}

// Given a word, what rhymes with it?
// TODO
vector<string> Model::getCategoriesForWord(string word) {
    string query = "select category from rhymes where word = \"" + word + "\" order by word";
    return doQuery(query);
}

vector<string> Model::getWordsInCategory(string category) {
    
}

bool Model::gameOver() {
    return false;
}

