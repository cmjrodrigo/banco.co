#ifndef USER_H
#define USER_H
typedef struct{
	int id, supervisor, active;
	char *name, *password;
	float balance;
} USER;

//New user creation
USER usrmakef();

//usrprint(USER);
void usrprint(USER usr);

//usrprintall(USER);
void usrprintall(USER usr);

//usrsetsu(&USER, SUPERVISOR);
void usrsetsu(USER *usr, int su);

//usrsetact(&USER, ACTIVE);
void usrsetact(USER *usr, int act);

//usrsetname(&USER, NEWNAME);
void usrsetname(USER *usr, char*nn);

//usrsetpass(&USER, NEWPASSWORD);
void usrsetpass(USER *usr, char*np);

//usraddbal(&USER, AMOUNT);
void usraddbal(USER *usr, float b);
#endif
