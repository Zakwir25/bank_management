/* GROUP 2
2501977052 - Eric Cokasta 
2501992261 - Zaki Widyadhana Wirawan
2501964730 - Lie Melinda Putri Wardana */

//Library Declaration : //Eric Cokasta - 2501977052
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Var. Declaration : //Lie Melinda - 2501964730
struct Data{
	char name[300];
	char date[20];
	double money;
	char contacts[15];
}list[101], temp;

int SIZE;
char keyword[300];

//Funct. Declaration : //Zaki Widyadhana - 2501992261
void create();
void depo();
void draw();
void close();
void show();
void update();
void readList();
int search();

//Zaki Widyadhana - 2501992261
int search(char key[]){ //Binary Search Function
	int left = 0;
	int mid = -1;
	int right = SIZE;
	while (left <= right){
		mid = (left + right)/2;
		if (strcmp(list[mid].name, key) > 0){
			right = mid-1;
		}
		else if(strcmp(list[mid].name, key) < 0){
			left = mid + 1;
		}
		else {
			return mid;
		}
	}
	return -1;
}

//Lie Melinda - 2501964730
int main(){ //Main Function untuk menu utama
	int opt;
	while (opt != 6){ //Selama input bukan 6, maka akan terus mengulang menu.
		printf("\n Welcome to BMS (Bank Management System)	\n");
		printf(" ======================================= 	\n");
		printf(" What would you like to do today?	\n");
		printf(" --------------------------------------- 	\n");
		printf("1. Create Account \n");
		printf("2. Deposit \n");
		printf("3. Withdraw \n");
		printf("4. Close Account \n");
		printf("5. List Accounts \n");
		printf("6. Exit Bank \n");
		printf(">> "); 
		scanf("%d", &opt); //meminta input menu yang diinginkan user
	
		switch(opt){
			case 1:{
				printf("\n creating account... \n"); getchar();
				create(); //calling create() function, to create a new saving account
				break;
			}
			case 2:{
				printf("\n depositing money... \n"); getchar();
				depo(); //calling depo() function, to deposit money
				break;
			}
			case 3:{
				printf("\n withdrawing money... \n"); getchar();
				draw(); //calling draw() function, to withdraw money
				break;
			}
			case 4:{
				printf("\n closing account... \n"); getchar();
				close(); //calling close() function, to close a saving account
				break;
			}
			case 5:{
				readList(); //calling readList() function, to make sure the data shown will be the latest data in the file
				printf("\n showing account(s)... \n"); getchar();
				show(); //calling show() function, to print the full list of data
				break;
			}
			case 6:{
				printf("Program Exited! \n"); //closing the program, as the user input 6
				break;
			}
			default:{ //other than input 1/2/3/4/5/6 the program will tell the user to check the input again.
				printf("Check your input again! \n");
				printf("Press ENTER to continue... \n"); getchar();
				break;
			}
		}
	}
 return 0;
}

//Eric Cokasta - 2501977052
void readList(){ //meng-update struct dengan membaca text file berisi data terbaru.
	FILE *fp = fopen("listaccounts.txt", "r"); 
	int i=0;
	while(!feof(fp)){ 
		fscanf(fp, "%[^#]#%[^#]#%[^#]#%lf\n", list[i].name, list[i].date, list[i].contacts, &list[i].money);
		i++;
	}
	SIZE = i;
	fclose(fp);
}

//Eric Cokasta - 2501977052
void update(){ //meng-update text file berisi data terbaru yang ada (digunakan dalam function deposit dan withdrawal).
	FILE *fp = fopen("listaccounts.txt", "w");
	for(int i=0; i<SIZE; i++){
		fprintf(fp, "%s#%s#%s#%.2lf\n", list[i].name, list[i].date, list[i].contacts, list[i].money);
	}
	fclose(fp);
}

//Lie Melinda - 2501964730
void create(){
	
	printf("Date of making (dd/mm/yyyy): ");
	scanf("%[^\n]", temp.date); getchar();
	
	printf("Enter Name: ");
	scanf("%[^\n]", temp.name); getchar();
	
	printf("Enter Contacts: "); 
	scanf("%s", temp.contacts);  getchar();
	
	printf("Enter Initial Amount: ");
	scanf("%lf", &temp.money);  getchar();
	
	FILE *fp = fopen("listaccounts.txt", "a");
	fprintf(fp, "%s#%s#%s#%lf\n", temp.name, temp.date, temp.contacts, temp.money);
	fclose(fp);
	
	printf("\nAccount Successfully Created! \n");
	printf("Press ENTER to continue... \n");
	getchar();
	
}

//Zaki Widyadhana - 2501992261
void depo(){ 
	
	printf("Enter Account Name to Deposit to : ");
	scanf("%[^\n]",keyword); 
	int in = search(keyword);
	if(in == -1){
		printf("\nKeyword not found! \n");
		printf("Press ENTER to continue... \n");
		getchar();
	} else {
		double depo;
		printf("Minimum Deposit amount : Rp. 100.000\n");
		printf("Enter Deposit amount : ");
		scanf("%lf",&depo); getchar();
		if(depo >= 100000){
			list[in].money += depo;
			update();
			printf("\nDeposit success! \n");
			printf("Press ENTER to continue... \n"); getchar();
		} else {
			printf("\nDeposit failed, Minimum amount not reached! \n");
			printf("Press ENTER to continue... \n"); getchar();
		}
	}
}

//Zaki Widyadhana - 2501992261
void draw(){
	
	printf("Enter Account Name to Withdraw from : ");
	scanf("%[^\n]",keyword); 
	int in = search(keyword);
	if(in == -1){
		printf("\nKeyword not found! \n");
		printf("Press ENTER to continue... \n");
		getchar();
	} else {
		double draw;
		printf("Maximum withdrawal amount : Rp. 5.000.000\n");
		printf("Enter Withdrawal amount : ");
		scanf("%lf",&draw); getchar();
		if(draw <= 5000000){
			list[in].money -= draw;
			update();
			printf("\nWithdrawal success! \n");
			printf("Press ENTER to continue... \n"); getchar();
		} else {
			printf("\nWithdrawal failed, Maximum Limit Reached! \n");
			printf("Press ENTER to continue... \n"); getchar();
		}
	}	
}

//Lie Melinda - 2501964730
void close(){
	int key, i=0;
	readList();
	show();
	printf("Which Data do you want do delete? (Enter Number) >> ");
	scanf("%d", &key);
	
	FILE *fp = fopen("listaccounts.txt", "r");
	FILE *tfp = fopen("temp.txt", "a");
	while(!feof(fp)){
		fscanf(fp, "%[^#]#%[^#]#%[^#]#%lf\n", list[i].name, list[i].date, list[i].contacts, &list[i].money);
		if (i != key-1){
			fprintf(tfp, "%s#%s#%s#%lf\n", list[i].name, list[i].date, list[i].contacts, list[i].money);
			i++;
		}
		else{
			i++;
			SIZE--;
		}
	}
	fclose(fp);
	fclose(tfp);
	remove("listaccounts.txt");
	rename("temp.txt", "listaccounts.txt");
	
	readList();
	printf("\nAccount Successfully Deleted! \n");
	printf("Press ENTER to continue... \n");
	getchar();
	
}

//Lie Melinda - 2501964730
void show(){
	
	printf("==========================================================================\n");
	printf("| NO | NAME		| DATE CREATED	| CONTACT	| SAVING		\n");
	printf("==========================================================================\n");
	for(int i=0; i<SIZE; i++){
		printf("| %-2d | %-16s | %-13s | %-13s | %-13.2lf | \n", i+1, list[i].name, list[i].date, list[i].contacts, list[i].money);
	}
	printf("==========================================================================\n"); 
	
	printf("Press ENTER to continue... \n");
	getchar();
}
