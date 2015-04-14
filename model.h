#ifndef _MODEL_H
#define _MODEL_H

#include <sqlite3.h>
#include <vector>
#include <string>

enum Direction { UP, DOWN, LEFT, RIGHT };
enum Operation { SEARCH, ADD, EDIT, REMOVE };
enum Entry { NOTHING, CATEGORY_FOR_WORD, WORDS_IN_CATEGORY, WORDS_LIKE_TEXT, SONGS_IN_ALBUM, SONGS_BY_ARTIST };

const std::string templates[4][6] = {
    // SEARCH
    { "", "SELECT category from rhymes where word = ?1 order by category", "SELECT word from rhymes where category = ?1 order by word", "SELECT word from rhymes where word like ?1", "", "" },
    // ADD
    { "", "insert into rhymes (word,category) values (?1,?2);", "", "", "", "" },
    // EDIT
    { "", "update rhymes set word = ?1 where category = ?2 and word = ?1", "", "", "", "" },
    // REMOVE
    { "", "delete from rhymes where category = ?1", "", "", "", "" }
};

// The model manages the state of the game
class Model {
public:
    // Constructor (instantiates object)
    Model();
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    // Is the game over?
    bool gameOver();
    // TODO: Put your stuff here
    Entry entry;
    Operation operation;
    void setText(std::string text);
    std::string getText();
    std::vector<std::string> result;
    void runQuery();
    void setOperation(Operation op);
    void setEntry(Entry entry);
private: // this should be private
    sqlite3 *conn;
    sqlite3_stmt *res;
    void doQuery(std::string query);
    // placeholder 1
    std::string text;
    // placeholder 2
    std::string word;
};

#endif