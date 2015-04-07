#ifndef _MODEL_H
#define _MODEL_H

#include <sqlite3.h>
#include <vector>
#include <string>

enum Direction { UP, DOWN, LEFT, RIGHT };

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
    sqlite3 *conn;
    sqlite3_stmt *res;
    void getCategoriesForWord(std::string word);
    void getWordsInCategory(std::string category);
    void getSongsInAlbum(std::string album);
    void getsongsInArtist(std::string artist);
    void getArtistsInResearchArtists(std::string artists);
// private: // this should be private
    void doQuery(std::string query);
    std::vector<std::string> result;
};

#endif