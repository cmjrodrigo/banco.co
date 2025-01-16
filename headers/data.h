#include "user.h"
#ifndef DATA_H
#define DATA_H
#define FUNCTION(f) #f
#define PRINCIPAL "../databases/principal.txt"
#define TEMPORAL "../databases/temporal.txt"

//Returns the maximum id currently on the database
int datacurrentid();

//Appends a user at the end of the database
void dataaddusr(USER usr);

//Returns a user's id  at a given name (0 if not found)
int datasearchname(char *name);

//Gets a user's data from the database
USER datagetusr(int id);

void dataupdate (int id_to_update, USER usr);
#endif
