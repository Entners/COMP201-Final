#include "model.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// Constructor initializes the object
Model::Model() {
    int     error = 0;
    error = sqlite3_open("test.db", &conn);
    
    if (error)
    {
        puts("Can not open database");
    }
    entry=WORDS_LIKE_TEXT;
    operation=SEARCH;
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
    
    // Add prefix thingy for like query
    if (entry == WORDS_LIKE_TEXT) {
        text = "%" + text;
    }
    
    error = sqlite3_prepare_v2(conn, query.c_str(), 1000, &res, &tail);
    sqlite3_bind_text(res, 1, text.c_str(), -1, SQLITE_TRANSIENT);
    
    cout << "query: " << query << endl;
    cout << "text: " << text << endl;
    
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

// The text the user entered
void Model::setText(std::string text) {
    this->text = text;
}

// Do a query
void Model::runQuery() {
    doQuery(templates[operation][entry]);
}

// Set the operation
void Model::setOperation(Operation op) {
    this->operation = op;
}

// Set the entry
void Model::setEntry(Entry entry) {
    this->entry = entry;
}

// Get the text
string Model::getText() {
    return text;
}

bool Model::gameOver() {
    return false;
}

