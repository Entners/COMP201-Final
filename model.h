#ifndef _MODEL_H
#define _MODEL_H

#include <sqlite3.h>
#include <vector>
#include <string>

enum Direction { UP, DOWN, LEFT, RIGHT };
// What are we doing at the moment?
enum Operation { CLEAR, SEARCH_BY_WORD, SEARCH_BY_CATEGORY, ADD, REMOVE };

// SQL query templates
const std::string templates[5] = {
    // CLEAR does nothing
    "",
    // SEARCH_BY_WORD
    "SELECT word, category from rhymes where word = ?1 order by category",
    // SEARCH_BY_CATEGORY
    "SELECT word, category from rhymes where category = ?2 order by word",
    // ADD
    "insert into rhymes (word,category) values (?1,?2);",
    // REMOVE
    "delete from rhymes where word = ?1"
};

struct Row {
    std::string word;
    std::string category;
};

// The model manages the state of the game
class Model {
public:
    // Constructor (instantiates object)
    Model();
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    // What we're doing at the moment
    Operation operation;
    
    // The current word
    std::string word;
    // The current category
    std::string category;
    
    std::vector<Row> result;
    void runQuery();
    void setOperation(Operation op);
    void setText(std::string text);
private: // this should be private
    sqlite3 *conn;
    sqlite3_stmt *res;
    void doQuery(std::string query);
};

#endif