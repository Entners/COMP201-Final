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
    std::vector<std::string> getCategoriesForWord(std::string word);
    std::vector<std::string> getWordsInCategory(std::string category);
    std::vector<std::string> getSongsInAlbum(std::string album);
    std::vector<std::string> getsongsInArtist(std::string artist);
    std::vector<std::string> getArtistsInResearchArtists(std::string artists);
// private: // this should be private
    std::vector<std::string> doQuery(std::string query);
};

#endif