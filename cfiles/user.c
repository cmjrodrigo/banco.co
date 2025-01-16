#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/user.h"
#include "../headers/data.h"

USER usrmakef(){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(usrmakef()));
#endif
	char n[50], p[50];
	float b;

	printf("Please enter your name: ");
	scanf("%[^\n]", n);
	getchar();
	if(datasearchname(n)){
		printf("User \"%s\" already exists.\n", n);
		USER usr = {0,0,0,0,0,0}; 
		return usr;
	}
	printf("Please enter a password: ");
	scanf("%[^\n]", p);
	getchar();
	printf("Money to deposit: $");
	scanf("%f", &b);

	USER usr;
	usr.id = datacurrentid() + 1;
	usr.active = 1;
	usr.supervisor = 0;
	usr.name = (char *) malloc(sizeof(char) * (strlen(n) + 1));
	strcpy(usr.name, n);
	usr.password = (char *) malloc(sizeof(char) * (strlen(p) + 1));
	strcpy(usr.password, p);
	usr.balance = b;

	return usr;
}

/*
	USER MANAGEMENT 
 */

//usrprint(USER);
void usrprint(USER usr){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(usrprint()));
#endif
	printf("ID: %d\n", usr.id);
	printf("NAME: %s\n", usr.name);
	printf("PASSWORD: %s\n", usr.password);
	printf("BALANCE: %.2f\n", usr.balance);
}

//usrprintall(USER);
void usrprintall(USER usr){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(usrprintall()));
#endif
	usrprint(usr);
	printf("SUPERVISOR: %d\n", usr.supervisor);
	printf("ACTIVE: %d\n", usr.active);
}


/*
	USER PARAMETER MANAGEMENT 
 */

//usrsetsu(&USER, SUPERVISOR);
void usrsetsu(USER *usr, int su){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(usrsetsu()));
#endif
	usr -> supervisor = su;
}

//usrsetact(&USER, ACTIVE);
void usrsetact(USER *usr, int act){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(usrsetact()));
#endif
	usr -> active = act;
}

//usrsetname(&USER, NEWNAME);
void usrsetname(USER *usr, char*nn){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(usrsetname()));
#endif
	usr -> name = (char * ) malloc(sizeof(char) * (strlen(nn) + 1));
	strcpy(usr -> name, nn);
}

//usrsetpass(&USER, NEWPASSWORD);
void usrsetpass(USER *usr, char*np){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(usrsetpass()));
#endif
	usr -> password= (char * ) malloc(sizeof(char) * (strlen(np) + 1));
	strcpy(usr -> password, np);
}

//usraddbal(&USER, AMOUNT);
void usraddbal(USER *usr, float b){
#ifdef DEBUG
printf("\x1B[33m%s, ln.%d, fn:%s\n\x1B[0m", __FILE__, __LINE__, FUNCTION(usraddbal()));
#endif
	usr -> balance += b;
}

