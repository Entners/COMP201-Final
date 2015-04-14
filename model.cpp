#include "model.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor initializes the object
Model::Model() {
    int     error = 0;
    error = sqlite3_open("test.db", &conn);
    
    if (error)
    {
        puts("Can not open database");
    }
    doQuery("select distinct word from rhymes where word like 'p%alysis' order by word;");
}
// Destructor deletes dynamically allocated memory
Model::~Model() {
    
}

void Model::doQuery(string query) {
    int     error = 0;
    int     rec_count = 0;
    const char      *errMSG;
    const char      *tail;
    
    result.clear();
    
    error = sqlite3_prepare_v2(conn, query.c_str(), 1000, &res, &tail);
    
    if (error != SQLITE_OK) {
        return;
    }
    
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        string row = (char*)sqlite3_column_text(res, 0);
        result.push_back(row);
        rec_count++;
    }
}

// Given a word, what rhymes with it?
// TODO
void Model::getCategoriesForWord(string word) {
    string query = "select category from rhymes where word = \"" + word + "\" order by word";
    doQuery(query);
}

void Model::getWordsInCategory(string category) {
    
}

void Model::setText(std::string text) {
    this->text = text;
}

bool Model::gameOver() {
    return false;
}

