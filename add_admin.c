#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct idPass
{
    char name[101];
    char pass[101];
};

void writeToFile(struct idPass);
int isUserDuplicate(char[]);
int main()
{
    char cPass[101];
    //int a;
    struct idPass admin;
    printf("Enter Phone:");
    gets(admin.name);
    printf("Enter password:");
    gets(admin.pass);
    printf("Re-enter your password:");
    gets(cPass);
    if(admin.name[0]==0 || admin.pass[0]==0)
    {
        printf("Name or Password is empty. Try again\n");
        main();
    }
    else
    {
        if(strcmp(admin.pass,cPass)==0)
        {
            if(!isUserDuplicate(admin.name)) writeToFile(admin);
            else{
                printf("Username \"%s\" already exists. Try again.\n",admin.name);
                main();
            }
        }
        else
        {
            printf("Password doesn't match.Try again\n");
            main();
        }

    }
    return 0;
}

int isUserDuplicate(char name[101]){
    FILE *ptr = fopen("admin_list.txt","rb");
    if(ptr==NULL){
        fclose(ptr);
        return 0;//not found
    }
    else{
        struct idPass user;
        while(fread(&user,sizeof(user),1,ptr)!=0){
            //fread(&user,sizeof(user),1,ptr);
            if(strcmp(user.name,name)==0){
                fclose(ptr);
                return 1;//user found
            }
        }
        fclose(ptr);
        return 0;//not found
    }
}

void writeToFile(struct idPass admin)
{
    FILE *ptr = fopen("admin_list.txt","ab");
    fwrite(&admin,sizeof(admin),1,ptr);
    fclose(ptr);
    printf("Admin added successfully\n");
}
