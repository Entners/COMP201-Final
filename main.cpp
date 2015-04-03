#include <stdio.h>
#include <sqlite3.h>
int main(void)
{
    sqlite3 *conn;
    sqlite3_stmt    *res;
    int     error = 0;
    int     rec_count = 0;
    const char      *errMSG;
    const char      *tail;
    error = sqlite3_open("ljdata.sl3", &conn);
    
        if (error)
        {
        puts("Can not open database");
        }
    
    //error = sqlite3_exec(conn, "update people set phonenumber=\'5055559999\' where id=3", 0, 0, 0);
    error = sqlite3_prepare_v2(conn, "select word, category from rhymes order by word",1000, &res, &tail);
    
            if (error != SQLITE_OK) {
                puts("We did not get any data!");
            }
    
            puts("==========================");
    
                while (sqlite3_step(res) == SQLITE_ROW)
                {
                        printf("%s|", sqlite3_column_text(res, 0));
                        printf("%s|", sqlite3_column_text(res, 1));
                        printf("%s|", sqlite3_column_text(res, 2));
                        printf("%s|", sqlite3_column_text(res, 3));
                        printf("%s|", sqlite3_column_text(res, 4));
                          rec_count++;
                }
}