/**********************************************PREPROCESSORS**********************************************************/
//Train Reservation System
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

/*******************************************GLOBAL VARIABLES**********************************************************/
//ALl the globle variables and the composite data types will be declared here
typedef struct{
	char name[50];
	int train_num;
	int num_of_seats;
}pd;




/*******************************************FUNCTION PROTOTYPE**********************************************************/
//function prototypes to be used
void reservation(void);							//main reservation function
void viewdetails(void);							//view details of all the trains
void cancel(void);								//cancel reservation
void printticket(char name[],int,int,float);	//print ticket 
void specifictrain(int);						//print data related to specific train
float charge(int,int);							//charge automatically w.r.t number of seats and train
void login();									//login page
void alltickets(void);							//print all booked tickets
int count(void);								//count no of tickets from count.txt
void deleteallrecords(void);					//delete all records of reservation

/*********************************************MAIN()*************************************************/

int main()

{
		system("cls"); 
	printf("\t\t=========================================================\n");
	printf("\t\t|                                                       |\n");
	printf("\t\t|                   MINI PROJECT EXPO                   |\n");
	printf("\t\t|                                                       |\n");
	printf("\t\t|                       WELCOME                         |\n");
	printf("\t\t|                                                       |\n");
	printf("\t\t|        INDIA'S LUXURIOUS TRAIN BOOKING SYSTEM         |\n");
	printf("\t\t|                                                       |\n");
	printf("\t\t|                   PRESENTED  BY                       |\n");
	printf("\t\t|              ANSH, ARNAV and ABHISHEK                 |\n");
	printf("\t\t|                                                       |\n");
	printf("\t\t=========================================================\n\n\n");
		
	    
	printf(" \n Press any key to continue:");
	
	getch();	
    system("cls");
	login();
	int menu_choice,choice_return;
	start:
	system("cls");
	printf("\n=================================\n");
	printf("    TRAIN RESERVATION SYSTEM");
	printf("\n=================================");
	printf("\n1>> Reserve A Ticket");
	printf("\n------------------------");
	printf("\n2>> View All Available Trains");
	printf("\n------------------------");
	printf("\n3>> Cancel Reservation");
	printf("\n------------------------");
	printf("\n4>> View Tickets");
	printf("\n------------------------");
	printf("\n5>> Delete All Records");
	printf("\n------------------------");
	printf("\n6>> Exit");
	printf("\n\n-->");
	scanf("%d",&menu_choice);
	switch(menu_choice)
	{
		case 1:
			reservation();	
			break;
		case 2:
			viewdetails();
			printf("\n\nPress any key to go to Main Menu..");
			getch();
			break;
		case 3:
			cancel();
			break;
		case 4:
			alltickets();
			printf("\n\nPress any key to go to Main Menu..");
			getch();
			break;
		case 5:
			deleteallrecords();
			break;
		case 6:
			return(0);
		default:
			printf("\nInvalid choice");
	}
	goto start;
	return(0);
}

/*********************************************VIEWDETAILS()*************************************************/

void viewdetails(void)
{
	system("cls");
	printf("------------------------------------------------------------------------------------------------------------------");	
	printf("\nTr.No\tName\t\t\t\t\tDestinations\t\t\tCharges\t\tPackage\n");
	printf("------------------------------------------------------------------------------------------------------------------");
	printf("\n1001\tMAHARAJA EXPRESS		 \tDelhi-Mumbai Tour      \t\t$ 47400\t\t6 nights 7 days");
	printf("\n1002\tPALACE ON WHEELS		 \tDelhi-Rajasthan Tour   \t\t$ 12600\t\t7 nights 8 days");
	printf("\n1003\tGOLDEN CHARIOT  		 \tSouth India Tour	      \t$ 6135 \t\t7 nights 8 days");
	printf("\n1004\tDECCAN ODYSSEY  		 \tDeccan India Tour      \t\t$ 14584\t\t7 nights 8 days");
	printf("\n1005\tROYAL RAJASTHAN ON WHEELS\t\tRoyal Rajasthan Tour   \t\t$ 9500 \t\t7 nights 8 days");
	printf("\n1006\tROYAL ORIENT TRAIN		 \tDelhi-Rajasthan-Gujarat\t\t$ 250  \t\t7 nights 8 days");
    printf("\n1007\tFAIRY QUEEN EXPRESS		 \tWest India Tour		  \t$ 200  \t\t1 night  2 days");	
    printf("\n1008\tMARS EXPRESS			 \tEarth-Mars Tour		  \t$ 79545\t\t2 years  4 months");
    printf("\n1009\tMETEOR EXPRESS			 \tAsteroid Belt Adventure\t\t$ 58989\t\t4 years  2 months");
    printf("\n1010\tSOLAR FLARE EXPRESS		 \tSolar System Tour	  \t$ 98989\t\tLifetime Tour    ");    
}

/*count.txt contains a '#' for every tickets booked. It makes counting of tickets easy*/  

int count(void){
    FILE *count = fopen("count.txt","r");
    int num =0; //no of tickets
    char ch = getc(count);
    while(ch != EOF){
        if(ch == '#')
            num++;
        ch = getc(count);
    }
    fclose(count);
    return num;
}

//add extra features if you want to add

void reservation(void)
{
	char confirm;
	float charges;
	pd passdetails;
	FILE *countptr,*newptr;
	char ch;
	int num = count();
	system("cls");	
	printf("\nEnter Your Name:> ");
	fflush(stdin);
	gets(passdetails.name);
	//error here have to take input of the name 
	printf("\nEnter Number of seats:> ");
	scanf("%d",&passdetails.num_of_seats);
	printf("\n\n>>Press Enter To View Available Trains<< ");
	getch();
	system("cls");
	viewdetails();
	printf("\n\nEnter train number:> ");
	start1:
	scanf("%d",&passdetails.train_num);
	if(passdetails.train_num>=1001 && passdetails.train_num<=1010)
	{
		charges=charge(passdetails.train_num,passdetails.num_of_seats);
		printticket(passdetails.name,passdetails.num_of_seats,passdetails.train_num,charges);		
	}
	else
	{
		printf("\nInvalid train Number! Enter again--> ");
		goto start1;
	}
	
	printf("\n\nConfirm Ticket (y/n):>");
	start:
	scanf(" %c",&confirm);
	if(confirm == 'y')
	{	//creating tkt = 'TICKET@.txt' where @ is ticket no
		char tkt[15] = "TICKET",txt[] = ".txt";
    	tkt[6] = 49+num;
    	for(int i=7;i<=10;i++){
        	tkt[i] = txt[i-7];
		}
		newptr = fopen(tkt,"w"); //add passenger details to the text file
		fprintf(newptr,"%d\t%s\t\t%d\t\t%d\t\t%.2f\t",num+1,&passdetails.name,passdetails.num_of_seats,passdetails.train_num,charges);
		fclose(newptr);
		printf("==================");
		printf("\n Reservation Done\n");
		printf("==================");
		printf("\nPress any key to go back to Main menu");
	}
	else
	{
		if(confirm=='n'){
			printf("\nReservation Not Done!\nPress any key to go back to  Main menu!");
		}
		else
		{
			printf("\nInvalid choice entered! Enter again-----> ");
			goto start;
		}
	}
	countptr = fopen("count.txt","a");
    fputs("#\n",countptr); //put a '#' in count.txt to increase ticket count
    fclose(countptr);
	getch();
}

/*********************************************CHARGE()*************************************************/

float charge(int train_num,int num_of_seats)
{
		if (train_num==1001)
	{
		return(47400.0*num_of_seats);
	}
	if (train_num==1002)
	{
		return(12600.0*num_of_seats);
	}
	if (train_num==1003)
	{
		return(6135.0*num_of_seats);
	}
	if (train_num==1004)
	{
		return(14584.0*num_of_seats);
	}
	if (train_num==1005)
	{
		return(9500.0*num_of_seats);
	}
	if (train_num==1006)
	{
		return(250.0*num_of_seats);
	}
	if (train_num==1007)
	{
		return(200.0*num_of_seats);
	}
	if (train_num==1008)
	{
		return(79545.0*num_of_seats);
	}
	if (train_num==1009)
	{
		return(58989.0*num_of_seats);
	}
	if (train_num==1010)
	{
		return(98989.0*num_of_seats);
	}
}


/*********************************************PRINTTICKET()*************************************************/

void printticket(char name[],int num_of_seats,int train_num,float charges)
{
	system("cls");
	printf("-------------------\n");
	printf("\tTICKET\n");
	printf("-------------------\n\n");
	printf("Name:\t\t\t%s",name);
	printf("\nNumber Of Seats:\t%d",num_of_seats);
	printf("\nTrain Number:\t\t%d",train_num);
	specifictrain(train_num);
	printf("\nCharges:\t\t%.2f",charges);
}

/*********************************************SPECIFICTRAIN()*************************************************/

void specifictrain(int train_num)
{
	
	if (train_num==1001)
	{
		printf("\nTrain:\t\t\tMAHARAJA EXPRESS");
		printf("\nTour:\t\t\tDelhi-Mumbai Tour");
		printf("\nPackage:\t\t6 nights 7 days ");
	}
	if (train_num==1002)
	{
		printf("\nTrain:\t\t\tPALACE ON WHEELS");
		printf("\nTour:\t\t\tDelhi-Rajasthan Tour");
		printf("\nPackage:\t\t7 nights 8 days ");
	}
	if (train_num==1003)
	{
		printf("\nTrain:\t\t\tGOLDEN CHARIOT");
		printf("\nTour:\t\t\tSouth India Tour");
		printf("\nPackage:\t\t7 nights 8 days ");
	}
	if (train_num==1004)
	{
		printf("\nTrain:\t\t\tDECCAN ODYSSEY");
		printf("\nTour:\t\t\tDecan India Tour");
		printf("\nPackage:\t\t7 nights 8 days ");
	}
	if (train_num==1005)
	{
		printf("\nTrain:\t\t\tROYAL RAJASTHAN ON WHEELS");
		printf("\nTour:\t\t\tRoyal Rajasthan Tour");
		printf("\nPackage:\t\t7 nights 8 days ");
	}
	if (train_num==1006)
	{
		printf("\nTrain:\t\t\tROYAL ORIENT TRAIN");
		printf("\nTour:\t\t\tDelhi-Rajasthan-Gujarat");
		printf("\nPackage:\t\t7 nights 8 days ");
	}
	if (train_num==1007)
	{
		printf("\nTrain:\t\t\tFAIRY QUEEN EXPRESS");
		printf("\nTour:\t\t\tWest India Tour");
		printf("\nPackage:\t\t1 nights 2 days ");
	}
	if (train_num==1008)
	{
		printf("\nTrain:\t\t\tMARS EXPRESS");
		printf("\nTour:\t\t\tEarth Mars Tour");
		printf("\nPackage:\t\t2 years 4 months ");
	}
	if (train_num==1009)
	{
		printf("\nTrain:\t\t\tMETEOR EXPRESS");
		printf("\nTour:\t\t\tAsteroid Belt Adventure");
		printf("\nPackage:\t\t4 years 2 months ");
	}
	if (train_num==1010)
	{
		printf("\nTrain:\t\t\tSOLAR FLARE EXPRESS");
		printf("\nTour:\t\t\tSolar System Tour");
		printf("\nPackage:\t\tLifetime Tour ");
	}
}

void login()
{
	int a=0,i=0;
    char uname[10],c=' '; 
    char pword[10],code[10];
    char user[10]="ansh";
    char pass[10]="ansh";
    do
{
	
    printf("\n                           LOGIN FORM                     \n  ");
    printf(" \n                       LOGIN ID:-");
	scanf("%s", &uname); 
	printf(" \n                       PASSWORD:-");
	while(i<10)
	{
	    pword[i]=getch();
	    c=pword[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';
	//char code=pword;
	i=0;
	//scanf("%s",&pword); 
		if(strcmp(uname,"ansh")==0 && strcmp(pword,"ansh")==0)
	{
	system("cls");
	printf("\n\n\n\t\t\t\t\tYOUR LOGIN IS SUCCESSFUL");
	printf("\n\n\n\t\t\t\t\tWELCOME TO OUR SYSTEM !! ");
	printf("\n\n\n\t\t\tWE PROVIDE BOOKING FOR MOST LUXORIOUS TRAINS IN INDIA");
	printf("\n\n\n\t\t\t\t\tPress any key to continue...");
	getch();//holds the screen
	break;
	}
	else
	{
		printf("\n        SORRY !!!!  LOGIN IS UNSUCESSFUL");
		a++;
		
		getch();//holds the screen
		system("cls");
	}
}
	while(a<=2);
	if (a>2)
	{
		printf("\nSorry you have entered the wrong username and password for four times!!!");
		exit(1);
		getch();
		
		}
		system("cls");	
}

void alltickets(void){
	char c[1000];
	FILE *file;
	char tkt[15] = "TICKET",txt[] = ".txt";
	int i,j,num = count();
	system("cls");
	if(!num){
		printf("NO TICKETS BOOKED!\n");
	}
	else{
		for(i=1;i<=num;i++){
			tkt[6] = 48+i;
    		for(j=7;j<=10;j++){
        		tkt[j] = txt[j-7];
			}
			file = fopen(tkt,"r");
			if (file) {
			    while (fgets(c, 100, file)!=NULL)
			        printf("%s",c);
			    fclose(file);
			}
			printf("\n");
		}
	}

}

//add 'CANCELLED #' in the ticket@.txt to mark it as cancelled

void cancel(void)
{	
	int num,cancelled=0,tktnum;
	FILE *check;
	char tkt[15] = "TICKET",txt[] = ".txt",confirm;
	system("cls"); 
    

	tktnum = count();

	if(tktnum == 0){
		printf("NO BOOKINGS TO CANCEL!!!\n");
	}
	else{
		alltickets();
		printf("\nenter the ticket number you want to delete: ");
readnum:    	scanf("%d",&num);	
		if(num>tktnum){
			printf("Enter a valid ticket number: ");
			goto readnum;
		}
		else{
			tkt[6] = 48+num;
	    	for(int i=7;i<=10;i++){
	        	tkt[i] = txt[i-7];
	    	}
			check = fopen(tkt,"r");
			char ch = getc(check);
	    	while(ch != EOF){
	    	    if(ch == '#') // search for '#' in 'CANCELLED #'
	        	    cancelled++;
				ch = getc(check);
	    	}
			fclose(check);
			if(cancelled){
				printf("TICKET ALREADY CANCELLED!!\n");
			}
			else{

checkpoint:
				printf("\n do you confirm to delete?(y/n) ");
				scanf(" %c",&confirm);
				if(confirm == 'y'){
					FILE *tktptr = fopen(tkt,"a");
	    			fprintf(tktptr, "\tCANCELLED #\t");
	    			fclose(tktptr);
					printf("TICKET CANCELLED!!!\n");
				}
				else if(confirm == 'n'){
					printf("TICKET NOT CANCELLED!!\n");
				}
				else{
					printf("Enter a valid choice...!!\n");
					goto checkpoint;
				}	
			}
		}
	}
	
	
	printf("press any key to go to main menu\n");
	getch();
}

//remove all 'TICKET@.txt' and 'count.txt' and make another 'count.txt' to clear all records

void deleteallrecords(void){
	char tkt[15] = "TICKET", txt[] = ".txt",confirm;
	int num = count();
	int i,j;
	system("cls");
	printf("do you really want to clear all records? (y/n) ");
	scanf(" %c",&confirm);
	
	if(confirm == 'y'){
		for(i=1;i<=num;i++){
			tkt[6] = 48+i;
		    for(int j=7;j<=10;j++){
	    		tkt[j] = txt[j-7];
    		}
		}
		remove("count.txt");
		FILE *ptr = fopen("count.txt","w");
		fclose(ptr);
		printf("ALL RECORDS DELETED...!!\n");
	}
	
	printf("\npress any key to go to main menu\n");
	getch();
}
              


