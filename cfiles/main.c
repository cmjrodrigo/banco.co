#include "../headers/user.h"
#include "../headers/data.h"
#include <stdio.h>
#include <string.h>

int active = 0;
int option;
char input[51];
USER usr;

int main(){
	//SIGN IN PAGE
	login:
	while (!active){
		int attn = 1;
		printf("Welcome to Banco.Co!!\nPlease type the numbers to select the given options.\n1)Sign In\n2)Sign Up\n3)Exit\n");
		scanf("%d", &option);
		getchar();

		switch(option){
			case 1:
				printf("\nEnter your accound name (case sensitive): ");
				scanf("%[^\n]", input);
				getchar();
				int id = datasearchname(input);
				
				//If username is found inside of the database
				if(id){
					usr = datagetusr(id);
					enter_password:
					printf("Please enter your account's password: ");
					scanf("%[^\n]", input);
					getchar();

					if(!strcmp(usr.password, input) && usr.active){
						active = 1;
						break;
					}
					else{
						if(!usr.active){
							printf("Your account is inactive. Please contact a supervisor.\n");
							break;
						}
						else{
							printf("Incorrect password entered. Please try again. Attempt:%d/3\n", attn++);
							if(attn > 3){
								break;
							}
							else{
								goto enter_password;
							}
						}
					}
				}
				
				//If username isn't found inside of the database
				else{
					printf("The username \"%s\" was not found in the database.\n", input);
					break;
				}
				break;
				
			case 2:
				usr = usrmakef();
				if(usr.id){
					active = 1;
					dataaddusr(usr);
				}
				break;
			case 3:
				puts("Exiting the program");
				return 0;
			default:
				printf("Please enter a valid number.\n\n");
				break;
		}
	}

	//MAIN LOBBY
	while(active){
		lobby:

		printf("\nThis is the main lobby. Please type a number to select between the given options:\n");
		printf("1)Exit\n2)See account info\n3)Add or retire to balance\n4)Make a transaction\n5)Profile settings\n6)Log-out");
		usr.supervisor ? puts("\n7)Manage users") : puts("");
		scanf("%d", &option);
		getchar();

		switch(option){
			//Exit
			case 1:
				dataupdate(usr.id, usr);
				puts("Exiting program");
				return 0;
				break;

			//Print user info
			case 2:
				puts("");
				usr.supervisor ? usrprintall(usr) : usrprint(usr);
				printf("Press ENTER to continue.\n");
				getchar();
				break;

			//Balance management
			case 3:
				printf("Amount to add or retire (to retire use negative numbers): ");
				float amount;
				scanf("%f", &amount);
				getchar();

				usraddbal(&usr, amount);
				printf("Added $%.2f to balance.\n", amount);

				puts("Press ENTER to continue.");
				getchar();
				break;

			//Transactions
			case 4:
				printf("Please enter your current password: ");
				char n[50], p[50];
				scanf("%[^\n]", p);
				getchar();
											       
				if(!strcmp(usr.password, p)){
					char n2[50];

					printf("Please enter the account's name to which you wish to transfer: ");
					scanf("%[^\n]", n2);
					getchar();

					int id = datasearchname(n2);

					if(id){
						USER usrt = datagetusr(id);

						printf("Enter the amount you wish to transfer: $");
						float amount;
						scanf("%f", &amount);
						if (amount > 0){
							usraddbal(&usr, (-1)*(amount));
							usraddbal(&usrt, amount);

							dataupdate(usr.id, usr);
							dataupdate(usrt.id, usrt);
						}
						else{
							puts("Cannot transfer a negative amount of money.");
						}
					}
					else{
						printf("User \"%s\" was not found on the database.\n", n2);
					}
				}
				else {
					puts("Input does not match the current password.");
				}

				break;

			//User settings
			case 5:
				printf("Select an option:\n0)Return to main menu\n1)Change username\n2)Change password\n");
				scanf("%d", &option);
				getchar();

				//Change name
				if(option == 1){
					char n[50], p[50];
					printf("Please enter your current password: ");
					scanf("%[^\n]", p);
					getchar();

					if(!strcmp(usr.password, p)){
						printf("Enter your new name: ");
						scanf("%[^\n]", n);
						getchar();

						usrsetname(&usr, n);
						printf("Changed name to \"%s\".\n", n);
					}
					else {
						puts("Input does not match the current password.");
					}
				}
				
				//Change password
				else if (option == 2){
					char n[50], p[50];
					printf("Please enter your current password: ");
					scanf("%[^\n]", p);
					getchar();

					if(!strcmp(usr.password, p)){
						printf("Enter your new password: ");
						scanf("%[^\n]", n);
						getchar();

						usrsetpass(&usr, n);
						printf("Changed password to \"%s\".\n", n);
					}
					else {
						puts("Input does not match the current password.");
					}
				}
				break;

			//Log-out
			case 6:
				active = 0;
				dataupdate(usr.id, usr);
				goto login;
				break;

			//User Management
			case 7:
				supervisor:
				if(usr.supervisor == 1){
					USER usr2;
					int id;
					char n[50];

					printf("Select an option:\n0)Return to main menu\n1)View accounts\n2)Manage accounts\n");
					scanf("%d", &option);
					getchar();

					switch (option){
						case 1:
							printf("Please enter an account name: ");
							scanf("%[^\n]", n);
							getchar();

							id = datasearchname(n);

							if(!id){
								printf("The user \"%s\" was not found on the database.\n", n);
								puts("Press ENTER to continue");
								getchar();
								goto supervisor;
							}

							usr2 = datagetusr(id);
							usrprintall(usr2);

							puts("Press ENTER to continue");
							getchar();

							goto supervisor;
						case 2:
							printf("Please enter an account name: ");
							scanf("%[^\n]", n);
							getchar();
							                                                                               
							id = datasearchname(n);
							                                                                               
							if(!id){
								printf("The user \"%s\" was not found on the database.\n", n);
								puts("Press ENTER to continue");
								getchar();
								goto supervisor;
							}
							                                                                               
							usr2 = datagetusr(id);


							printf("Select an option:\n0)Return to main menu\n1)Change username\n2)Change password\n3)Change account status\n");
							scanf("%d", &option);
							getchar();

							//Change name
							if(option == 1){
								char n[50];
								printf("\nEnter the user's new name: ");
								scanf("%[^\n]", n);
								getchar();

								usrsetname(&usr2, n);
								printf("Changed name to \"%s\".\n", n);
							}
							
							//Change password
							else if (option == 2){
								char n[50];

								printf("\nEnter the user's new password: ");
								scanf("%[^\n]", n);
								getchar();

								usrsetpass(&usr2, n);
								printf("Changed password to \"%s\".\n", n);
							}
							else if(option == 3){
								printf("\nEnter the user's new activity status: ");
								scanf("%d", &option);
								getchar();

								usrsetact(&usr2, option);
								printf("Changed activity status to: %d\n", usr2.active);
							}

							dataupdate(usr2.id, usr2);
							goto supervisor;
						default:
							break;
					}
					break;
				}
			default:
				puts("Please enter a valid option (Press ENTER to continue)");
				getchar();
				break;
		}
	}
}
