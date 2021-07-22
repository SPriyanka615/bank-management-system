#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bank
{
   int accno;
   char name[40];
   char address[40];
   double phone;
   int bal;
}acc;
int i=0;
FILE *DataFile;

void add()
{
    fseek(DataFile, i*sizeof(struct bank), SEEK_SET);
    printf("Enter the account number " );
    scanf("%d", &acc.accno);
    printf("Enter the name " );
    scanf("%s", acc.name);
    printf("Your name is %s.", acc.name);
    printf("Enter the address " );
    scanf("%s", acc.address);
    printf("Enter the phone number " );
    scanf("%lf", &acc.phone);
    printf("Enter the account balance " );
    scanf("%d", &acc.bal);
    fwrite (&acc, sizeof(struct bank), 1, DataFile);
    i = i + 1;
}

void removeit(int n)
{
    int j = 1;
    FILE *temp;
    temp = fopen("temp.dat", "w+");
    while(j<n)
    {
        fread (&acc, sizeof(struct bank), 1, DataFile);
        fwrite (&acc, sizeof(struct bank), 1, temp);
    }
    fseek(DataFile, sizeof(struct bank), SEEK_CUR);
    while(j<=i)
    {
        fread (&acc, sizeof(struct bank), 1, DataFile);
        fwrite (&acc, sizeof(struct bank), 1, temp);
    }
    DataFile = freopen("Bank.dat", "w+", DataFile);
    j = 1;
    i = i - 1;
    while(j<=i)
    {
        fread (&acc, sizeof(struct bank), 1, temp);
        fwrite (&acc, sizeof(struct bank), 1, DataFile);
    }
    fclose(temp);
}

void modify(int n)
{
    int j = 1;
    FILE *temp;
    temp = fopen("temp.dat", "w+");
    while(j<n)
    {
        fread (&acc, sizeof(struct bank), 1, DataFile);
        fwrite (&acc, sizeof(struct bank), 1, temp);
    }
    printf("Enter the account number " );
    scanf("%d", &acc.accno);
    printf("Enter the name " );
    scanf("%s", acc.name);
    printf("Enter the address " );
    scanf("%s", acc.address);
    printf("Enter the phone number " );
    scanf("%lf", &acc.phone);
    printf("Enter the account balance " );
    scanf("%d", &acc.bal);
    fwrite (&acc, sizeof(struct bank), 1, temp);
    fseek(DataFile, sizeof(struct bank), SEEK_CUR);
    while(j<=i)
    {
        fread (&acc, sizeof(struct bank), 1, DataFile);
        fwrite (&acc, sizeof(struct bank), 1, temp);
    }
    DataFile = freopen("Bank.dat", "w+", DataFile);
    j = 1;
    while(j<=i)
    {
        fread (&acc, sizeof(struct bank), 1, temp);
        fwrite (&acc, sizeof(struct bank), 1, DataFile);
    }
    fclose(temp);
}

void display(int n)
{

    fseek (DataFile, (n-1)*sizeof(struct bank), SEEK_SET);
    fread (&acc, sizeof(struct bank), 1, DataFile);
    printf("\nThe account number is %d", acc.accno);
    printf("\nThe name is " );
    puts(acc.name);
    printf("\nThe address is " );
    puts(acc.address);
    printf("\nThe phone number is %lf", acc.phone);
    printf("\nThe account balance is %d", acc.bal);
}

int main()
{
    int op, n;
    DataFile = fopen ("Bank.dat", "w+");
    if (DataFile == NULL)
    {
        printf("\nError to open the file!\n");
        exit (1);
    }
    while(1)
    {
        printf("*******Welcome to the Bank Management System*******\n-------Please select you option-------\t\n1 Create an account \n2  Delete an account \n3 Modify an account \n4 Display an account");
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                add();
                break;
            case 2:
                printf("Enter the account number to delete ");
                scanf("%d", n);
                removeit(n);
                break;
            case 3:
                printf("Enter the account number to modify ");
                scanf("%d", n);
                modify(n);
                break;
            case 4:
                printf("Enter the account number to display ");
                scanf("%d", n);
                display(n);
                break;
        }
    };
    fclose(DataFile);
    return 0;
}
