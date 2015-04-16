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
    operation=CLEAR;
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
    sqlite3_bind_text(res, 1, word.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(res, 2, category.c_str(), -1, SQLITE_TRANSIENT);
    
    if (error != SQLITE_OK) {
        return;
    }
    
    
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        Row row;
        row.word = (char*)sqlite3_column_text(res, 0);
        row.category = (char*)sqlite3_column_text(res, 1);
        result.push_back(row);
        rec_count++;
    }
}

// Do a query
void Model::runQuery() {
    doQuery(templates[operation]);
}

// Set the operation
void Model::setOperation(Operation op) {
    this->operation = op;
    word = "";
    category = "";
    result.clear();
}

void Model::setText(string text) {
    static bool first = true;
    if (operation == ADD) {
        if (first) {
            word = text;
        } else {
            category = text;
        }
        first = !first;
    } else {
        word = text;
    }
}

