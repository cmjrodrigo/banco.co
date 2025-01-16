#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../headers/user.h"
#include "../headers/data.h"

//Returns the maximum id currently on the database
int datacurrentid(){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(datacurrentid()));
#endif
	FILE *f = fopen(PRINCIPAL, "rt");
	int cid = 0;
	char line[200];

	while(fgets(line, sizeof(line), f) != NULL){
		cid++;
	}

	fclose(f);
	return cid;
}

//Appends a user at the end of the database
void dataaddusr(USER usr){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(dataaddusr()));
#endif
	FILE *f = fopen(PRINCIPAL, "at");
	fprintf(f, "%d\t%s\t%d\t%d\t%.2f\t%s\n", usr.id, usr.name, usr.active, usr.supervisor, usr.balance, usr.password);

	fclose(f);
}

//Returns a user's id  at a given name (0 if not found)
int datasearchname(char *name){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(datasearchname()));
#endif
	FILE *f = fopen(PRINCIPAL, "rt");
	int cid = 0, found = 0;
	char line[200], nc[50];

	while(fgets(line, sizeof(line), f) != NULL){
		sscanf(line, "%d\t%[^\t]", &cid, nc);
		if(!strcmp(name, nc)){
			found = 1;
			break;
		}
	}

	fclose(f);
	if (found){
		return cid;
	}
	else{
		return 0;
	}
}

//Gets a user's data from the database
USER datagetusr(int id){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(datagetusr()));
#endif                                                       
	FILE *f = fopen(PRINCIPAL, "rt");
	int cid = 0, found = 0;
	char line[200];

	while(fgets(line, sizeof(line), f) != NULL && cid != id){
		cid++;
		if(cid == id){
			found = 1;
			break;
		}
	}

	fclose(f);
	if(!found){
#ifdef DEBUG
printf("\x1B[33m\t%s: NO USER FOUND, RETURNING EMPTY STRUCT.\x1B[0m\n",FUNCTION(datagetusr()) );
#endif
		USER usr = {0,0,0,0,0,0};
		return usr;
	}
	else{
#ifdef DEBUG
printf("\x1B[33m\t%s: USER FOUND IN LINE %d\n\tREADING \"%s\" TO USER.\n\x1B[0m\n",FUNCTION(datagetusr()), cid, line);
#endif
		int i, a, s;
		char n[50], p[50];
		float b;
		USER usr;

		sscanf(line, "%d\t%[^\t]\t%d\t%d\t%f\t%[^\n]\n", &i, n, &a, &s, &b, p);
		
		usr.name = (char *) malloc(sizeof(char) * (strlen(n) + 1));
		usr.password= (char *) malloc(sizeof(char) * (strlen(p) + 1));

		usr.id = i;
		usr.active = a;
		usr.supervisor = s;
		usr.balance = b;
		strcpy(usr.name, n);
		strcpy(usr.password, p);
#ifdef DEBUG
printf("\x1B[33m\t%s: DATA{%d, %s, %d, %d, %f, %s}\n\x1B[0m\n",FUNCTION(datagetusr()), usr.id, usr.name, usr.active, usr.supervisor, usr.balance, usr.password);
#endif
		return usr;
	}
}

void dataupdate(int id, USER usr){
	FILE *m, *t;
	char line[200];
	int cid = 1;
	
	m = fopen(PRINCIPAL, "r");
	t = fopen(TEMPORAL, "w");

	while(fgets(line, sizeof(line), m) != NULL){
		if(cid == id){
			fprintf(t, "%d\t%s\t%d\t%d\t%.2f\t%s\n", usr.id, usr.name, usr.active, usr.supervisor, usr.balance, usr.password);
			cid++;
		} 
		else{
			fprintf(t, "%s", line);
			cid++;
		}
	}
	fclose(m);
	fclose(t);


	m = fopen(PRINCIPAL, "w");
	t = fopen(TEMPORAL, "r");
	int ch;

	while((ch = fgetc(t)) != EOF){
		fputc(ch, m);
	}
	
	fclose(m);
	fclose(t);

	t = fopen(TEMPORAL, "w");
	fclose(t);
}
