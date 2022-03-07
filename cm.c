#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>

int POSITION=0;
struct idPass
{
    char name[101];//name = phone(changed later)
    char pass[101];
};

struct STUDENT//for student.txt
{
    char dept[21],roll[21],name[51],phone[21],email[51],addr[101],pass[51];
};

struct TEACHER//for teacher_list.txt
{
    char dept[21],name[51],phone[21],email[51],addr[101],pass[51];
};

struct STC_FORMAT//student course format // student_course.txt
{
    char phone[21],cc[20],roll[21],name[51],dept[21];
};
//phone[21],cc[20],roll[21],name[51],dept[21],marks[21];

struct MARKS_FORMAT//ct_marks.txt
{
    char phone[21],tphone[21],cc[20],roll[21],name[51],dept[21],marks[21];//tPhone = teacher's phone
};

char STUDENT_PHONE[21];//for showing signed in teacher data
char TEACHER_PHONE[21];//for showing signed in student data

int handleLogin(int);
    //(below + above)func. will take phone, pass and return true(1,2,or 3) if user found else false
struct idPass getNamePass();

char getValidInput();//just take one char and return if char is 1,2,3

int loginUser(char[],char[],int);//return 1 if user is in file otherwise return 0

void handleAdminPanel();
void handleTeacherPanel();//show panel menu and navigate use to other sub - menu
void handleStudentPanel();

void addTeacher();//add teacher
void addStudent();//add student

void remateTeachent(int,int);// remate[remove/update] + teachent[teacher/student]

int getSelectedInput(int,int);//will return a number between 1 to int(1st)

int convertStringToInt(char[]);//will convert char array and return int

int doesContainInvalid(char[]);//true if there is no char except 0-9, else false

struct STUDENT takeStudentInfo();//will take student info and return STUDENT struct

int isDuplicateStudentAvailable(struct STUDENT);//will check for duplicate student
int isDuplicateTeacherAvailable(struct TEACHER);//will check for duplicate teacher

void showExtraCommandAdmin(int);
void showExtraCommandTeacher(int);//will show menu and navigate based on input
void showExtraCommandStudent(int);

struct TEACHER takeTeacherInfo();//take teacher info and return TEACHER struct


void searchByRoll(char*);//...
void searchByName();//...

int isMatched(char *,char *);//return true if string-1 contains string-2 else false

void assateCourse(int);//assate[assign+update] + Course
void showAssignedCourses(char *,int);//will show assigned courses of this teacher assigned by admin

int isCCAlreadyAssigned(char *,char *);//true if string-2 is assigned to teacher[string-1]

void remRoll(int);//remove+enroll = remRoll

int isCCAssignedToTeacher(char*);//true if string-1 is assigned to any teacher else false

void addCTMarks(int);//..
int getTotalStudent(char[],char[],int);
//return total students in dept[string-1] and enrolled to course [string-2]


int isMarkAdded(char[],char[],char[]);
//return true after updating marks in ct_marks.txt otherwise return false without doing anything

void showTotalStudents();//will show total student dept wise
void showCTMarks();//will show current signed in students marks

void modifyAllStudentFiles(struct STUDENT,char*,int);
    //will update all data related to the student whose info has been deleted or updated
void modifyAllTeacherFiles(struct TEACHER,char*,int);
    //will update all data related to the teacher whose info has been deleted or updated

void displayText(char *);//show string-1 in heading

int main()
{
    displayText("WELCOME");
    printf("%25s %25s\n%25s %25s\nCommand:","ADMIN PANEL(1)","TEACHER'S PANEL(2)","STUDENT'S PORTAl(3)","EXIT PROGRAM(4)");
    char inp[3];//inp[2] is always null(0)
    fgets(inp,3,stdin);
    fflush(stdin);
    while(inp[0]<49 || inp[0]>52 || inp[1]!=10)//10 = ascii value of newline('\n')
    {
        printf("Please type 1 to 4 only\nCommand:");
        fgets(inp,3,stdin);
        fflush(stdin);
    }

    int val = (int)inp[0] -48;//converting to int
    if(val==4)
    {
        printf("< - - Program closed successfully - - >\n");
        exit(1);
    }
    else
    {
        system("cls");
        switch(val)//will show the box heading only
        {
        case 1:
            displayText("ADMIN LOGIN");
            break;
        case 2:
            displayText("TEACHER LOGIN");
            break;
        case 3:
            displayText("STUDENT LOGIN");
            break;
        default:
            displayText("LOGIN");
            break;
        }
        int check = handleLogin(val);//true if login is successfull
        system("cls");
        if(check==1)
        {
            handleAdminPanel();
        }
        else if(check==2)
        {
            handleTeacherPanel();
        }
        else if(check==3)
        {
            handleStudentPanel();
        }
    }
    return 0;
}

int handleLogin(int optionCheck)
{//return 1 if user is in file otherwise return 0
    char u_name[101],pass[101];

    struct idPass user = getNamePass();
    //printf("%s %s",user.name,user.pass);
    strcpy(u_name,user.name);
    strcpy(pass,user.pass);

    if(loginUser(u_name,pass,optionCheck)) //optionCheck: 1 = admin, 2 = teacher, 3 = student
    {
        return optionCheck; //login successful
    }
    else
    {
        printf("Invalid info\n1.Try again \t2.Go Back \t3.Exit\nCommand:");
        char ch = getValidInput();
        if(ch=='1')
        {
            system("cls");
            switch(optionCheck)
            {
            case 1:
                displayText("ADMIN LOGIN");
                break;
            case 2:
                displayText("TEACHER LOGIN");
                break;
            case 3:
                displayText("STUDEBT LOGIN");;
                break;
            default:
                displayText("LOGIN");
                break;
            }
            handleLogin(optionCheck);
        }
        else if(ch=='2')
        {
            system("cls");
            main();
        }
        else if(ch=='3')
        {
            printf("Program closed. Type any key to close window\n");
            exit(0);
        }
        else//for unexpected error handling
        {
            printf("Something went wrong. Going back to main menu\n");
            main();
        }
    }
}

struct idPass getNamePass()
{   //will take phone, pass and return structure containing phone and pass
    struct idPass user;

    printf("Phone:");
    fgets(user.name,101,stdin);
    fflush(stdin);
    while(user.name[0]==10) //10 == newline character(\n);
    {
        printf("Phone can't be empty. Enter phone again: ");
        fgets(user.name,101,stdin);
        fflush(stdin);
    }

    int j=0;
    while(user.name[j]!='\n' && user.name[j]!=0) j++;
    user.name[j]=0;

    printf("Password:");
    fgets(user.pass,101,stdin);
    fflush(stdin);
    while(user.pass[0]==10)
    {
        printf("WOW. Empty password. Enter password again: ");
        fgets(user.pass,101,stdin);
        fflush(stdin);
    }

    j=0;
    while(user.pass[j]!='\n' && user.pass[j]!=0) j++;
    user.pass[j]=0;

    return user;
}

char getValidInput()
{
    //just take one char and return if char is 1,2,3
    char inp[3];
    fgets(inp,3,stdin);
    fflush(stdin);
    while(inp[0]<49 || inp[0]>51 || inp[1]!=10) //10 = ascii value of newline('\n')
    {
        printf("Please type 1, 2 or 3 only\nCommand:");
        fgets(inp,3,stdin);
        fflush(stdin);
    }
    return inp[0];
}

int loginUser(char name[],char pss[],int check)//name = phone
{
    //return 1 if user is in file otherwise return 0
    if(check==1)//admin
    {
        FILE *ptr = fopen("admin_list.txt","rb");
        struct idPass user;
        int checker=0;
        if(ptr!=NULL)
        {
            while(fread(&user,sizeof(user),1,ptr)!=0)
            {
                if(strcmp(user.name,name)==0 && strcmp(user.pass,pss)==0)
                {
                    checker=1;//user found
                    break;
                }
            }
            fclose(ptr);
        }
        return checker;
    }
    else if(check==2) //teacher
    {
        FILE *ptr = fopen("teacher_list.txt","rb");
        struct TEACHER user;
        int checker=0;
        if(ptr!=NULL)
        {
            while(fread(&user,sizeof(user),1,ptr)!=0)
            {
                if(strcmp(user.phone,name)==0 && strcmp(user.pass,pss)==0)
                {
                    strcpy(TEACHER_PHONE,user.phone);
                    checker=1;//user found
                    break;
                }
            }
            fclose(ptr);
        }
        return checker;
    }
    else if(check==3) //student
    {
        FILE *ptr = fopen("student.txt","rb");
        struct STUDENT user;
        int checker=0;
        if(ptr!=NULL)
        {
            while(fread(&user,sizeof(user),1,ptr))
            {
                if(strcmp(user.phone,name)==0 && strcmp(user.pass,pss)==0)//name = phone
                {
                    strcpy(STUDENT_PHONE,user.phone);
                    checker=1;//user found
                    break;
                }
            }
            fclose(ptr);
        }
        return checker;
    }
    return 0;//user not found(won'e be executed hopefully except error)
}

void handleAdminPanel()
{//show panel menu and navigate use to other sub - menu
    displayText("ADMIN PANEL");
    printf("%25s%25s\n%25s%25s\n%25s%25s\n%25s%25s\n%25s\nCommand: ","ADD TEACHER(1)","ADD STUDENT(2)","UPDATE TEACHER INFO(3)","UPDATE STUDENT INFO(4)","REMOVE TEACHER(5)","REMOVE STUDENT(6)","ASSIGN COURSE(7)","UPDATE COURSE(8)","GO BACK(9)");

    char inp[3];//inp[2] is always null(0)
    fgets(inp,3,stdin);
    fflush(stdin);
    while(inp[0]<49 || inp[0]>57 || inp[1]!=10)//10 = ascii value of newline('\n')
    {
        printf("Please type 1 to 9 only\nCommand:");
        fgets(inp,3,stdin);
        fflush(stdin);
    }
    int val = (int)inp[0] -48;
    system("cls");
    switch(val)
    {
    case 1:
        displayText("ADD TEACHER");
        addTeacher();
        break;
    case 2:
        displayText("ADD STUDENT");
        addStudent();
        break;
    case 3:
        displayText("UPDATE TEACHER");
        remateTeachent(0,1);//update teacher
        break;
    case 4:
        displayText("UPDATE STUDENT");
        remateTeachent(1,1);//update student
        break;
    case 5:
        displayText("REMOVE TEACHER");
        remateTeachent(0,0);//remove teacher
        break;
    case 6:
        displayText("REMOVE STUDENT");
        remateTeachent(1,0);//remove student
        break;
    case 7:
        displayText("ASSIGN COURSE");
        assateCourse(0);//0 = assign course
        break;
    case 8:
        displayText("UPDATE COURSE");
        assateCourse(1);//1 = update course
        break;
    case 9:
        main();//going back to main menu
        break;
    default:
        printf("Something went wrong. Going back to admin panel\n");
        handleAdminPanel();
        break;
    }
}

void handleTeacherPanel()
{
    //show panel menu and navigate use to other sub - menu
    displayText("TEACHER'S PANEL");
    printf("%25s%25s\n%25s%25s\n%25s%25s\nCommand:","Add CT marks(1)","Update CT marks(2)","Find student by roll(3)","Find student by name(4)","Total students(5)","Go Back(6)");

    char inp[3];//inp[2] is always null(0)
    fgets(inp,3,stdin);
    fflush(stdin);
    while(inp[0]<49 || inp[0]>54 || inp[1]!=10)//10 = ASCII value of newline('\n')
    {
        printf("Please type 1 to 6 only\nCommand:");
        fgets(inp,3,stdin);
        fflush(stdin);
    }
    int val = (int)inp[0] -48;

    system("cls");
    switch(val)
    {
    case 1:
        displayText("ADD CT MARKS");
        addCTMarks(0);// 0 = add ct marks
        break;
    case 2:
        displayText("UPDATE CT MARKS");
        addCTMarks(1);// 1 = update ct marks
        break;
    case 3:
    {
        displayText("SEARCH BY ROLL");
        char arr[51];
        printf("Enter student's roll:");
        fgets(arr,51,stdin);
        fflush(stdin);
        while(arr[0]==10)
        {
            printf("Can't be empty. Enter roll:");
            fgets(arr,51,stdin);
            fflush(stdin);
        }
        int j=0;
        while(arr[j]!='\n' && arr[j]!=0) j++;
        arr[j]=0;//removing newline if have
        searchByRoll(arr);
    }
    break;
    case 4:
        displayText("SEARCH BY NAME");
        searchByName();
        break;
    case 5:
        displayText("SHOW TOTAL STUDENTS");
        showTotalStudents();
        break;
    case 6:
        main();
        break;
    default:
        printf("Something went wrong. Returning to Teacher's panel.\n");
        handleTeacherPanel();
        break;
    }
}

void handleStudentPanel()
{
    //show panel menu and navigate use to other sub - menu
    displayText("STUDENT PORTAL");
    printf("%25s%25s\n%25s%25s\nCommand: ","Enroll course(1)","Remove course(2)","Show CT marks(3)","Go Back(4)");

    char inp[3];//inp[2] is always null(0)
    fgets(inp,3,stdin);
    fflush(stdin);
    while(inp[0]<49 || inp[0]>52 || inp[1]!=10)//10 = ASCII value of newline('\n')
    {
        printf("Please type 1 to 4 only\nCommand:");
        fgets(inp,3,stdin);
        fflush(stdin);
    }
    int val = (int)inp[0] -48;

    system("cls");
    switch(val)
    {
    case 1:
        displayText("ENROLL COURSE");
        remRoll(0);//enroll course
        break;
    case 2:
        displayText("REMOVE COURSE");
        remRoll(1);//remove course
        break;
    case 3:
        displayText("SHOW CT MARKS");
        showCTMarks();
        break;
    case 4:
        main();
        break;
    default:
        break;
    }
}

void addTeacher()//working fine till now
{
    printf("Enter teacher info:\n");
    //dept name phone email address
    struct TEACHER t1;

    t1 = takeTeacherInfo();//taking input from user

    int tempCheck = isDuplicateTeacherAvailable(t1);//checking for duplicate teacher
    if(tempCheck==2)//teacher found with full duplicate details
    {
        printf("< - - \"%s\" IS ALREADY IN TEACHER'S LIST - - >\n",t1.name);
        printf("1.Try again\t2.Go Back\t3.Exit\nCommand:");
    }
    else if(tempCheck==1)//phone number found only
    {
        printf("< - - SOMEONE IS REGISTERED WITH PHONE NUMBER \"%s\" - - >\n",t1.phone);
        printf("1.Try again\t2.Go Back\t3.Exit\nCommand:");
    }
    else//ok
    {
        //writing to file
        FILE *ptr = fopen("teacher_list.txt","ab");
        if(ptr!=NULL)
        {
            fwrite(&t1,sizeof(t1),1,ptr);
            fclose(ptr);
            printf("\n< - - \"%s\" ADDED AS TEACHER SUCCESSFULLY - ->\n",t1.name);
        }
        else
        {
            printf("Something went wrong.\n");
        }
        //writing to file above

        printf("1.Add another\t2.Go Back\t3.Exit\nCommand:");
    }

    //show try again
    {
        char ch = getValidInput();
        system("cls");
        if(ch=='1')
        {
            displayText("ADD TEACHER");
            addTeacher();
        }
        else if(ch=='2')
        {
            handleAdminPanel();
        }
        else if(ch=='3')
        {
            printf("Program closed.\n");
            exit(0);
        }
        else
        {
            printf("Something went wrong. Going back to Admin panel\n");
            handleAdminPanel();
        }
    }
    //show try again above
}

void addStudent()//working fine till now
{
    printf("Enter student info:\n");
    struct STUDENT t1;
    t1 = takeStudentInfo();//taking input from user
    //printf(" %s %s %s %s %s %s %s\n",t1.dept,t1.roll,t1.name,t1.phone,t1.email,t1.addr,t1.pass);
    int tempCheck = isDuplicateStudentAvailable(t1);//checking for duplicate student
    //puts("Error");
    if(tempCheck==2)//100% duplicate student found
    {
        printf("< - - \"%s\" IS ALREADY IN STUDNET'S LIST - - >\n",t1.name);
        printf("1.Try again\t2.Go Back\t3.Exit\nCommand:");
    }
    else if(tempCheck==1)//phone number found
    {
        printf("< - - SOMEONE IS REGISTERED WITH PHONE NUMBER \"%s\" - - >\n",t1.phone);
        printf("1.Try again\t2.Go Back\t3.Exit\nCommand:");
    }
    else
    {
        //writing to file
        FILE *ptr = fopen("student.txt","ab");
        //struct STUDENT wrt = t1;

        if(ptr!=NULL)
        {
            fwrite(&t1,sizeof(t1),1,ptr);
            //struct STUDENT stt3;
            fclose(ptr);
            printf("\n< - - \"%s\" ADDED AS STUDENT SUCCESSFULLY - - >\n",t1.name);
        }
        else printf("Something went wrong\n");
        printf("1.Add another\t2.Go Back\t3.Exit\nCommand:");
    }
    showExtraCommandAdmin(0);//0=add student
}

void remateTeachent(int isStudent,int isFromUpdate) //teacher and student; 0 = teacher, 1 = student
{
    // remate[remove/update] + teachent[teacher/student]
    //isStudent = 1(student) else 0(teacher)
    //isFromUpdate = 1(calling from update) else 0(calling from remove)
    char temp[6] = "Dept",tt[10] = "TEACHER";//by default
    if(isStudent)
    {
        strcpy(temp,"Roll");//used previously
        strcpy(tt,"STUDENT");
    }
    struct TEACHER t1,t2;
    struct STUDENT st1,st2;

    printf("Enter %s's Dept:",tt);
    fgets(t1.dept,21,stdin);
    fflush(stdin);
    while(t1.dept[0]==10)
    {
        printf("Can't be empty. Enter dept again:");
        fgets(t1.dept,21,stdin);
        fflush(stdin);
    }
    int j=0;
    while(t1.dept[j]!='\n' && t1.dept[j]!=0) j++;
    t1.dept[j]=0;//removing newline if have

    //checking for value below
    int tempCheck=0;//not found
    FILE *ptr;
    if(isStudent) ptr = fopen("student.txt","rb");
    else ptr = fopen("teacher_list.txt","rb");

    char **matched=0;// 2D character array/pointer

    if(ptr!=NULL)
    {
        int isPrinted=0;
        if(isStudent)//if user is student
        {
            while(fread(&st1,sizeof(st1),1,ptr)!=0)
            {
                if(strcmp(st1.dept,t1.dept)==0)
                {
                    if(!isPrinted)
                    {
                        printf("SHOWING ALL STUDENTS IN \"%s\" DEPARTMENT:\n\n",t1.dept);
                        printf("%*s %*s %*s %*s %*s %*s %*s %*s\n",4,"S.N.",11,"DEPARTMENT",10,"ROLL",15,"NAME",14,"PHONE",25,"EMAIL",30,"ADDRESS",15,"PASSWORD");
                        isPrinted = 1;
                    }
                    printf("%*d %*s %*s %*s %*s %*s %*s %*s\n",4,tempCheck+1,11,st1.dept,10,st1.roll,15,st1.name,14,st1.phone,25,st1.email,30,st1.addr,15,st1.pass);
                    matched = (char **) realloc(matched,(tempCheck+1)*21*sizeof(char));
                    matched[tempCheck] = calloc(21,sizeof(char));
                    strcpy(matched[tempCheck],st1.phone);
                    tempCheck++;//student found
                }
            }

        }
        else//teacher
        {
            while(fread(&t2,sizeof(t2),1,ptr)!=0)
            {
                if(strcmp(t2.dept,t1.dept)==0)
                {
                    if(!isPrinted)
                    {
                        printf("SHOWING ALL TEACHERS IN \"%s\" DEPARTMENT: \n\n",t1.dept);
                        printf("%*s %*s %*s %*s %*s %*s %*s\n",4,"S.N.",11,"DEPARTMENT",15,"NAME",14,"PHONE",25,"EMAIL",30,"ADDRESS",15,"PASSWORD");
                        isPrinted = 1;
                    }
                    printf("%*d %*s %*s %*s %*s %*s %*s\n",4,tempCheck+1,11,t2.dept,15,t2.name,14,t2.phone,25,t2.email,30,t2.addr,15,t2.pass);
                    matched = (char **) realloc(matched,(tempCheck+1)*21*sizeof(char));
                    matched[tempCheck] = calloc(21,sizeof(char));
                    strcpy(matched[tempCheck],t2.phone);
                    tempCheck++;//teacher found

                }
            }
        }
        fclose(ptr);
    }
    //checking for value above

    if(!tempCheck)//0
    {
        printf("< - - NO %s FOUND - - >\n",tt);
        printf("1.Try again\t2.Go Back\t3.Exit\nCommand:");
    }
    else
    {
        printf("\n");

        //taking selected number input
        int selectedNum = getSelectedInput(tempCheck,isFromUpdate);//will return integer input from user
        //taking selected number input above

        struct STUDENT up_st;
        struct TEACHER up_t;

        if(isFromUpdate)//will take new info from user
        {
            if(isStudent) //
            {
                up_st = takeStudentInfo();//taking student new info from user
                int checking=isDuplicateStudentAvailable(up_st);
                while(strcmp(up_st.phone,matched[selectedNum-1])!=0 && checking)
                {
                    if(checking==1) //phone number found
                    {
                        printf("< - - SOMEONE IS ALREADY REGISTERED WITH PHONE \"%s\" - - > Enter info again:\n",up_st.phone);
                    }
                    else //2 full duplicate student found
                    {
                        printf("< - - \"%s\" IS ALREADY IN STUDENT'S LIST - - > Enter info again:\n",up_st.name);
                    }
                    up_st = takeStudentInfo();
                    checking=isDuplicateStudentAvailable(up_st);
                }
            }
            else
            {
                up_t = takeTeacherInfo();
                int checking = isDuplicateTeacherAvailable(up_t);
                while(strcmp(up_t.phone,matched[selectedNum-1])!=0 && checking)
                {
                    if(checking==1) //phone number found
                    {
                        printf("< - - SOMEONE IS ALREADY REGISTERED WITH PHONE \"%s\"- - > Enter info again:\n",up_t.phone);
                    }
                    else //2 full duplicate student found
                    {
                        printf("< - - \"%s\" IS ALREADY IN TEACHER'S LIST - - > Enter info again:\n",up_t.name);
                    }
                    up_t = takeTeacherInfo();
                    checking = isDuplicateTeacherAvailable(up_t);
                }
            }
        }

        //writing to file
        FILE *ptr2,*tempPtr;
        char old[30],now[30];
        if(isStudent)
        {
            strcpy(old,"student.txt");
            strcpy(now,"tempst_list.txt");

            ptr2 = fopen("student.txt","rb");
            tempPtr = fopen("tempst_list.txt","ab");//temp student list
            if(ptr2!=NULL && tempPtr!=NULL)
            {
                while(fread(&st1,sizeof(st1),1,ptr2)!=0)
                {
                    if(strcmp(matched[selectedNum-1],st1.phone)!=0)fwrite(&st1,sizeof(st1),1,tempPtr);
                    else
                    {
                        if(isFromUpdate) fwrite(&up_st,sizeof(up_st),1,tempPtr);//up_st updated student info
                    }
                }
                fclose(ptr2);
                fclose(tempPtr);
                remove(old);
                rename(now,old);
            }
            else
            {
                if(ptr2!=NULL) fclose(ptr2);
                if(tempPtr!=NULL) fclose(tempPtr);
                printf("< - - SOMETHING WENT WRONG - - >\n");
            }
        }
        else
        {
            strcpy(old,"teacher_list.txt");
            strcpy(now,"tempt_list.txt");

            ptr2 = fopen("teacher_list.txt","rb");
            tempPtr = fopen("tempt_list.txt","ab");//temporary teacher list
            if(ptr2!=NULL && tempPtr!=NULL)
            {
                while(fread(&t1,sizeof(t1),1,ptr2)!=0)
                {
                    if(strcmp(matched[selectedNum-1],t1.phone)!=0)fwrite(&t1,sizeof(t1),1,tempPtr);
                    else
                    {
                        if(isFromUpdate) fwrite(&up_t,sizeof(up_t),1,tempPtr);//updated teacher info
                    }

                }
                fclose(ptr2);
                fclose(tempPtr);
                remove(old);
                rename(now,old);
            }
            else
            {
                if(ptr2!=NULL) fclose(ptr2);
                if(tempPtr!=NULL) fclose(tempPtr);
                printf("< - - SOMETHING WENT WRONG - - >\n");
            }
        }
        //writing to file above

        if(isStudent)
        {
            modifyAllStudentFiles(up_st,matched[selectedNum-1],isFromUpdate);//will update all info in all related file
        }
        else
        {
            modifyAllTeacherFiles(up_t,matched[selectedNum-1],isFromUpdate);//..... for teacher
        }
        free(matched);
        if(isFromUpdate)
        {
            if(isStudent)
                printf("< - - ALL DATA RELATED TO \"%s\" HAS BEEN UPDATED SUCCESSFULLY - - >\n",up_st.name);
            else
                printf("< - - ALL DATA RELATED TO \"%s\" HAS BEEN UPDATED SUCCESSFULLY - - >\n",up_t.name);
            printf("1.Update another\t2.Go Back\t3.Exit\nCommand:");
        }
        else
        {
            printf("< - - \"%s\" REMOVED SUCCESSFULLY - - >\n",tt);
            printf("1.Remove another\t2.Go Back\t3.Exit\nCommand:");
        }
    }

    //2,3,4,5 remove teacher, student, update teac,stud
    // (0,0) (1,0), (0,1), (1,1)
    int pass=5;
    if(!isStudent && !isFromUpdate) pass=2;
    else if(isStudent && !isFromUpdate) pass=3;
    else if(!isStudent && isFromUpdate) pass =4;
    showExtraCommandAdmin(pass);
}

int getSelectedInput(int num,int isFromUpdate)
{
    //will return a number between 1 to num
    int tNum=num;
    int count=0;//length
    while(num)
    {
        num/=10;
        count++;
    }
    //char arr[51];
    if(isFromUpdate==0) printf("Enter serial number that you want to remove:");
    else if(isFromUpdate==1) printf("Enter serial number that you want to update:");
    else if(isFromUpdate==-1) printf("Enter teacher's serial number:");
    else if(isFromUpdate==2) printf("Enter course number you want to remove:");
    else if(isFromUpdate==3) printf("Enter course number you want to add marks:");
    else
    {
        printf("Enter serial number:");
    }

    char arr[51];
    fgets(arr,51,stdin);
    fflush(stdin);
    int j=0;
    while(arr[j]!='\n' && arr[j]!=0) j++;
    arr[j]=0;
    while(arr[count]!=0 || doesContainInvalid(arr) ||
            convertStringToInt(arr)<1 || convertStringToInt(arr)>tNum)
    {
        printf("Enter 1 to %d only. Enter again:",tNum);
        fgets(arr,51,stdin);
        fflush(stdin);
        int jj=0;
        while(arr[jj]!='\n' && arr[jj]!=0) jj++;
        arr[jj]=0;
    }
    return convertStringToInt(arr);
}

int convertStringToInt(char arr[])
{
    //will convert char array and return int

    //arr = 456 example
    int n=(int)arr[0] - 48;//n = 4
    int i=1;
    while(arr[i]!=0)//
    {
        n*=10;
        n+=((int)arr[i] - 48);// n = 45,456
        i++;
    }
    return n;//456
}

int doesContainInvalid(char arr[])
{
    //true if there is no char except 0-9, else false
    int i=0;
    while(arr[i]!=0)
    {
        if(arr[i]<48 || arr[i]>57)
        {
            return 1;//contain invalid
        }
        i++;
    }
    return 0;// does not contain invalid
}

struct STUDENT takeStudentInfo()
{
    //will take student info and return STUDENT struct

    struct STUDENT t1;
    char text[7][15]= {"Dept:","Roll:","Full Name:","Phone:","Email:","Address:","Password:"};
    int size[7]= {21,21,51,21,51,101,51};
    //21,21,51,21,51,101,51
    for(int i=0; i<7; i++)
    {
        printf("%s",text[i]);
        char arr[size[i]];
        fgets(arr,size[i],stdin);
        fflush(stdin);
        while(arr[0]==10)
        {
            printf("Can't be empty. Enter %s",text[i]);
            fgets(arr,size[i],stdin);
            fflush(stdin);
        }
        int j=0;
        while(arr[j]!='\n' && arr[j]!=0) j++;
        arr[j]=0;//removing newline if have

        switch(i)
        {//this may be the worst way I am doing...
        case 0:
            strcpy(t1.dept,arr);
            break;
        case 1:
            strcpy(t1.roll,arr);
            break;
        case 2:
            strcpy(t1.name,arr);
            break;
        case 3:
            strcpy(t1.phone,arr);
            break;
        case 4:
            strcpy(t1.email,arr);
            break;
        case 5:
            strcpy(t1.addr,arr);
            break;
        case 6:
            strcpy(t1.pass,arr);
            break;
        }

    }
    //printf("take= %s %s %s %s %s %s %s\n",t1.dept,t1.roll,t1.name,t1.phone,t1.email,t1.addr,t1.pass);
    return t1;

}

int isDuplicateStudentAvailable(struct STUDENT st1)
{
    //will check for duplicate student
    struct STUDENT st2;
    int tempCheck=0;//student not found
    FILE *stPtr = fopen("student.txt","rb");
    if(stPtr!=NULL)
    {
        while(fread(&st2,sizeof(st2),1,stPtr))
        {
            //puts(st2.phone);
            if(strcmp(st1.phone,st2.phone)==0)
            {
                tempCheck = 1;//phone number found
                if(strcmp(st2.roll,st1.roll)==0 && strcmp(st2.dept,st1.dept)==0 &&
                        strcmp(st2.name,st1.name)==0 && strcmp(st2.email,st1.email)==0 &&
                        strcmp(st2.addr,st1.addr)==0)
                {
                    tempCheck = 2;//student found
                }
                break;
            }
        }
        fclose(stPtr);
    }
    return tempCheck;
}

int isDuplicateTeacherAvailable(struct TEACHER t1)
{
    //checking for duplicate teacher
    int tempCheck=0;//teacher not found
    FILE *ptr = fopen("teacher_list.txt","rb");
    struct TEACHER t2;
    if(ptr!=NULL)
    {
        while(!feof(ptr))
        {
            fread(&t2,sizeof(t2),1,ptr);
            if(strcmp(t1.phone,t2.phone)==0)
            {
                tempCheck = 1;//phone number found
                if(strcmp(t2.dept,t1.dept)==0 && strcmp(t2.name,t1.name)==0 && strcmp(t2.email,t1.email)==0 && strcmp(t2.addr,t1.addr)==0)
                {
                    tempCheck = 2;//teacher found
                }
                break;
            }
        }
        fclose(ptr);
    }
    return tempCheck;
    //checking for duplicate teacher above
}

void showExtraCommandAdmin(int checker)
{
    //will show menu and navigate based on input
    //checker 0=addStudent,1=addTeacher,2=removeStudent,3=removeTeacher,4=updateStudent,5=updateTeacher
    //6 = asset course
    char ch = getValidInput();//return '1','2' or '3' based on user input
    if(ch=='1')//try again
    {
        switch(checker)
        {
        case 0:
            system("cls");
            displayText("ADD STUDENT");
            addStudent();
            break;
        case 1:
            system("cls");
            displayText("ADD TEACHER");
            addTeacher();
            break;
        case 2:
            system("cls");
            displayText("REMOVE TEACHER");
            remateTeachent(0,0);//remove teacher
            break;
        case 3:
            system("cls");
            displayText("REMOVE STUDENT");
            remateTeachent(1,0);//remove student
            break;
        case 4:
            system("cls");
            displayText("UPDATE TEACHER");
            remateTeachent(0,1);//update teacher
            break;
        case 5:
            system("cls");
            displayText("UPDATE STUDENT");
            remateTeachent(1,1);//update student
            break;
        case 6:
            system("cls");
            displayText("COURSE ASSIGN");
            assateCourse(0);//assign course
            break;
        case 7:
            system("cls");
            displayText("UPDATE COURSE");
            assateCourse(1);//update course
            break;
        }

    }
    else if(ch=='2')//GO BACK
    {
        system("cls");
        handleAdminPanel();
    }
    else if(ch=='3')//EXIT
    {
        system("cls");
        printf("Program closed.\n");
        exit(0);
    }
    else
    {
        system("cls");
        printf("Something went wrong. Going back to Admin panel\n");
        handleAdminPanel();
    }
}

void showExtraCommandTeacher(int checker)
{
    //will show menu and navigate based on input
    // 0=add CT, 1=update CT, 2=findRoll, 3=findName, 4=total students
    char ch = getValidInput();//will return '1','2',or '3' based on user input
    if(ch=='1')//try again
    {
        switch(checker)
        {
        case 0:
            system("cls");
            displayText("ADD CT MARKS");
            addCTMarks(0);//0 = addCtMarks
            break;
        case 1:
            system("cls");
            displayText("UPDATE CT MARKS");
            addCTMarks(1); // 1 = update ct marks
            break;
        case 2:
        {
            system("cls");
            displayText("SEARCH BY ROLL");
            char arr[51];
            printf("Enter student's roll:");
            fgets(arr,51,stdin);
            fflush(stdin);
            while(arr[0]==10)
            {
                printf("Can't be empty. Enter roll:");
                fgets(arr,51,stdin);
                fflush(stdin);
            }
            int j=0;
            while(arr[j]!='\n' && arr[j]!=0) j++;
            arr[j]=0;
            searchByRoll(arr);
        }
        break;
        case 3:
            system("cls");
            displayText("SEARCH BY NAME");
            searchByName();
            break;
        case 4:
            system("cls");
            displayText("SHOW TOTAL STUDENT");
            showTotalStudents();
            break;
        }

    }
    else if(ch=='2')//go back
    {
        system("cls");
        handleTeacherPanel();
    }
    else if(ch=='3')//exit
    {
        system("cls");
        printf("Program closed.\n");
        exit(0);
    }
    else
    {
        printf("Something went wrong. Going back to Teacher's panel\n");
        handleTeacherPanel();
    }

}

void showExtraCommandStudent(int checker)
{
    //will show menu and navigate based on input
    // 0=enRoll course, 1= Remove course, 2 = show CT marks // remove = update
    char ch = getValidInput();
    system("cls");
    if(ch=='1')//try again
    {
        switch(checker)
        {
        case 0:
            displayText("ENROLL COURSE");
            remRoll(0);
            break;
        case 1:
            displayText("REMOVE COURSE");
            remRoll(1);
            break;
        case 2:
            displayText("SHOW CT MARKS");
            showCTMarks();
            break;
        default:
        {
            printf("Something went wrong.\n Going back to Student's panel.\n");
            handleStudentPanel();
            break;
        }
        }

    }
    else if(ch=='2')//go back
    {
        handleStudentPanel();
    }
    else if(ch=='3')//exit
    {
        printf("Program closed.\n");
        exit(0);
    }
    else
    {
        printf("Something went wrong. Going back to Student's panel\n");
        handleStudentPanel();
    }
}

struct TEACHER takeTeacherInfo()
{
    //take teacher info and return TEACHER struct
    struct TEACHER t1;
    char text[6][15]= {"Dept:","Full Name:","Phone:","Email:","Address:","Password:"};

    int size[]= {21,51,21,51,101,51};
    for(int i=0; i<6; i++)
    {
        printf("%s",text[i]);
        char arr[size[i]];
        fgets(arr,size[i],stdin);
        fflush(stdin);
        while(arr[0]==10)
        {
            printf("Can't be empty. Enter %s",text[i]);
            fgets(arr,size[i],stdin);
            fflush(stdin);
        }
        int j=0;
        while(arr[j]!='\n' && arr[j]!=0) j++;
        arr[j]=0;
        switch(i)
        {
        case 0:
            strcpy(t1.dept,arr);
            break;
        case 1:
            strcpy(t1.name,arr);
            break;
        case 2:
            strcpy(t1.phone,arr);
            break;
        case 3:
            strcpy(t1.email,arr);
            break;
        case 4:
            strcpy(t1.addr,arr);
            break;
        case 5:
            strcpy(t1.pass,arr);
            break;
        }
    }
    return t1;
}


void searchByRoll(char *arr)//
{
    FILE *ptr = fopen("student.txt","rb");
    struct STUDENT st1;
    int tempCheck=0,isPrinted=0;;
    if(ptr!=NULL)
    {
        while(fread(&st1,sizeof(st1),1,ptr)!=0)
        {
            if(strcmp(st1.roll,arr)==0)
            {
                if(!isPrinted)
                {
                    printf("SHOWING ALL STUDENTS BEARING ROLL \"%s\":\n\n",arr);
                    printf("%*s %*s %*s %*s %*s %*s %*s\n",3,"SN.",11,"DEPARTMENT",10,"ROLL",15,"NAME",14,"PHONE",25,"EMAIL",30,"ADDRESS");
                    isPrinted = 1;
                }
                printf("%*d %*s %*s %*s %*s %*s %*s\n",3,tempCheck+1,11,st1.dept,10,st1.roll,15,st1.name,14,st1.phone,25,st1.email,30,st1.addr);
                tempCheck++;//student found
            }
        }
        fclose(ptr);
    }
    if(!tempCheck)
    {
        printf("< - - NO STUDENT FOUND BEARING ROLL \"%s\" - - >\n",arr);
    }
    printf("\n1.Search again\t2.Go Back\t3.Exit\nCommand:");
    showExtraCommandTeacher(2);
}

void searchByName()
{
    char arr[51];
    printf("Enter student's name:");
    fgets(arr,51,stdin);
    fflush(stdin);
    while(arr[0]==10)
    {
        printf("Can't be empty. Enter name:");
        fgets(arr,51,stdin);
        fflush(stdin);
    }
    int j=0;
    while(arr[j]!='\n' && arr[j]!=0) j++;
    arr[j]=0;
    struct STUDENT st1;
    FILE *ptr = fopen("student.txt","rb");
    int isPrinted=0,tempCheck=0;

    if(ptr!=NULL)
    {
        while(fread(&st1,sizeof(st1),1,ptr)!=0)
        {
            if(isMatched(st1.name,arr))
            {
                //puts(arr);
                if(!isPrinted)
                {
                    printf("SHOWING ALL STUDENTS CONTAINING \"%s\" IN NAME:\n\n",arr);
                    printf("%*s %*s %*s %*s %*s %*s %*s\n",3,"SN.",11,"DEPARTMENT",10,"ROLL",15,"NAME",14,"PHONE",25,"EMAIL",30,"ADDRESS");
                    isPrinted = 1;
                }
                printf("%*d %*s %*s %*s %*s %*s %*s\n",3,tempCheck+1,11,st1.dept,10,st1.roll,15,st1.name,14,st1.phone,25,st1.email,30,st1.addr);
                tempCheck++;//student found
            }
        }
        fclose(ptr);
    }
    if(!tempCheck)
    {
        printf("< - - NO STUDENT FOUND WITH NAME \"%s\" - ->\n",arr);
    }
    Sleep(250);
    printf("\n1.Search again\t2.Go Back\t3.Exit\nCommand:");
    showExtraCommandTeacher(3);
}
//system("cls")

int isMatched(char name[51],char key[51])
{
    //return true if name contains key else false

    int kL=0;
    while(key[kL]!=0) kL++;
    int i=0;
    while(name[i+kL-1]!=0)
    {
        int j=0,tp=i,isMatched=1;//matched
        while(key[j]!=0)
        {
            if(tolower(name[tp])!=tolower(key[j]))
            {
                isMatched = 0;
                break;
            }
            tp++;
            j++;
        }
        if(isMatched==1) return 1;
        i++;
    }
    return 0;
}

void assateCourse(int isFromUpdate) //assign + update courses
{
    struct TEACHER t2;

    char dep[21];

    printf("Enter teacher's Dept:");

    fgets(dep,21,stdin);
    fflush(stdin);
    while(dep[0]==10)
    {
        printf("Can't be empty. Enter dept. again:");
        fgets(dep,21,stdin);
        fflush(stdin);
    }
    int j=0;
    while(dep[j]!='\n' && dep[j]!=0) j++;
    dep[j]=0;

    //checking for value
    int tempCheck=0;//not found
    FILE *ptr = fopen("teacher_list.txt","rb");

    char **matched=0;

    if(ptr!=NULL)
    {
        int isPrinted=0;

        while(fread(&t2,sizeof(t2),1,ptr)!=0)
        {
            if(strcmp(t2.dept,dep)==0)
            {
                if(!isPrinted)
                {
                    printf("SHOWING ALL TEACHERS IN \"%s\" DEPARTMENT:\n\n",dep);
                    printf("%*s %*s %*s %*s %*s %*s\n",4,"S.N.",11,"DEPARTMENT",15,"NAME",14,"PHONE",25,"EMAIL",30,"ADDRESS");
                    isPrinted = 1;
                }
                printf("%*d %*s %*s %*s %*s %*s\n",4,tempCheck+1,11,t2.dept,15,t2.name,14,t2.phone,25,t2.email,30,t2.addr);
                matched = (char **) realloc(matched,(tempCheck+1)*21*sizeof(char));
                matched[tempCheck] = calloc(21,sizeof(char));
                strcpy(matched[tempCheck],t2.phone);
                tempCheck++;//teacher found

            }
        }
        fclose(ptr);
    }

    //checking for value above

    if(!tempCheck)//0
    {
        printf("< - - NO TEACHER FOUND - - >\n");
        printf("1.Try again\t2.Go Back\t3.Exit\nCommand:");
        showExtraCommandAdmin(6+(isFromUpdate==1));
    }
    else
    {
        printf("\n");

        //taking selected number input
        int selectedNum = getSelectedInput(tempCheck,-1);
        //taking selected number input above

        //will show teacher's name and assigned courses
        showAssignedCourses(matched[selectedNum-1],isFromUpdate);

        free(matched);
        if(isFromUpdate) printf("1.Update course again\t2.Go Back\t3.Exit\nCommand:");
        else printf("1.Assign course again\t2.Go Back\t3.Exit\nCommand:");
        showExtraCommandAdmin(6+(isFromUpdate==1));
    }
}

void showAssignedCourses(char *phone,int isFromUpdate)
{
    //will show assigned courses of this teacher assigned by admin
    struct TEACHER t1;
    FILE *ptr = fopen("teacher_list.txt","rb");

    if(ptr!=NULL)
    {
        while(fread(&t1,sizeof(t1),1,ptr)!=0)
        {
            if(strcmp(t1.phone,phone)==0)
            {
                printf("< - - \"%s\", DEPARTMENT OF \"%s\" - - >\n",t1.name,t1.dept);
                break;
            }
        }
        fclose(ptr);
        //showing teacher's name and dept above

        struct cFormat //course format
        {
            char phone[21],cc[20];//cc = course code
        } cf1;
        FILE *ptr2 = fopen("course_assign.txt","rb");
        int total_course=0;
        char **matched=0;
        if(ptr2!=NULL)
        {
            while(fread(&cf1,sizeof(cf1),1,ptr2)!=0)
            {
                if(strcmp(cf1.phone,phone)==0)
                {
                    total_course++;
                    matched = (char **) realloc(matched,(total_course)*sizeof(cf1.cc));
                    matched[total_course-1] = calloc(20,sizeof(char));

                    strcpy(matched[total_course-1],cf1.cc);
                    if(isFromUpdate) //show serially
                    {
                        if(!(total_course-1)) printf("ASSIGNED COURSES:\n");
                        printf("%3d. %s\t",total_course,cf1.cc);
                        if(total_course%2==0) printf("\n");
                    }
                    else
                    {
                        if(!(total_course-1)) printf("ASSIGNED COURSES: \"%s\"",cf1.cc);
                        else printf(", \"%s\"",cf1.cc);
                    }
                }
            }
            if(total_course%2==1 || (!isFromUpdate && total_course))printf("\n");
            if(total_course==0) printf("NO COURSE ASSIGNED.\n");
            fclose(ptr2);
        }
        else
        {
            printf("< - - NO COURSE ASSIGNED - - >\n");
        }

        //while ((getchar()) != '\n'); for clearing buffer

        int selectedNum;
        if(isFromUpdate)
        {
            if(total_course)
            {
                selectedNum = getSelectedInput(total_course,1);
                printf("New course code:(LEAVE \"BLANK\" FOR REMOVING):");
            }
            else
            {
                printf("< - - NOTHING TO DO HERE - - >\n");
                return;
            }
        }
        else
        {
            printf("Enter course code you want to assign:");
        }
        //taking class code from user

        char arr[21];
        fgets(arr,21,stdin);
        fflush(stdin);
        while(arr[0]==10 && !isFromUpdate)
        {
            printf("Can't be empty. Enter again:");
            fgets(arr,21,stdin);
            fflush(stdin);
        }
        int j=0;
        while(arr[j]!='\n' && arr[j]!=0) j++;
        arr[j]=0;
        //taking class code from user above

        if(!isFromUpdate)//function is called from assign course
        {
            if(isCCAlreadyAssigned(phone,arr))//phone, class_code
            {
                //checking if course is already assigned or not
                printf("< - - \"%s\" IS ALREADY ASSIGNED TO THIS TEACHER - - >\n",arr);
            }
            else
            {
                FILE *ccw = fopen("course_assign.txt","ab");
                struct cFormat //course format
                {
                    char phone[21],cc[20];//cc = course code
                } cf1;
                strcpy(cf1.phone,phone);
                strcpy(cf1.cc,arr);
                if(ccw!=NULL)
                {
                    fwrite(&cf1,sizeof(cf1),1,ccw);
                    fclose(ccw);
                }
                printf("< - - COURSE ASSIGNMENT COMPLETED - - >\n");
            }
        }
        else //function is called from update course
        {
            FILE *ptr = fopen("course_assign.txt","rb+");

            struct cFormat //course format
            {
                char phone[21],cc[20];//cc = course code
            } cf1,cf2;
            if(arr[0]==0) //remove course code
            {
                if(ptr!=NULL)
                {
                    FILE *temp = fopen("temp_assign.txt","ab");
                    if(temp!=NULL)
                    {
                        while(fread(&cf1,sizeof(cf1),1,ptr)!=0)
                        {
                            if(strcmp(cf1.phone,phone)!=0 || strcmp(cf1.cc,matched[selectedNum-1])!=0)
                            {
                                fwrite(&cf1,sizeof(cf1),1,temp);
                            }
                        }
                        fclose(temp);
                        fclose(ptr);
                        remove("course_assign.txt");
                        rename("temp_assign.txt","course_assign.txt");
                        printf("< - - COURSE SUCCESSFULLY REMOVED - - >\n");
                    }
                    else fclose(ptr);
                }
                else
                {
                    printf("Something went wrong.\n");
                }
            }
            else //modify/update class code
            {
                if(ptr!=NULL)
                {
                    if(strcmp(matched[selectedNum-1],arr)!=0 && isCCAlreadyAssigned(phone,arr))
                    {
                        printf("< - - \"%s\" IS ALREADY ASSIGNED TO THIS TEACHER - - >\n",arr);
                    }
                    else
                    {
                        while(fread(&cf1,sizeof(cf1),1,ptr)!=0)
                        {
                            if(strcmp(cf1.phone,phone)==0 && strcmp(cf1.cc,matched[selectedNum-1])==0)
                            {
                                fseek(ptr,-(long)sizeof(cf1),SEEK_CUR);
                                strcpy(cf2.phone,cf1.phone);
                                strcpy(cf2.cc,arr);
                                fwrite(&cf2,sizeof(cf2),1,ptr);
                                fseek(ptr,0,SEEK_CUR);
                                //fclose(ptr);
                                break;
                            }
                        }
                        printf("< - - COURSE SUCCESSFULLY UPDATED - - >\n");
                    }
                    fclose(ptr);
                }
                else
                {
                    printf("Something went wrong\n");
                }
            }
        }

        if(isFromUpdate)printf("1.Update again\t2.Go Back\t3.Exit\nCommand:");
        else printf("1.Assign again\t2.Go Back\t3.Exit\nCommand:");

        showExtraCommandAdmin(6+(isFromUpdate==1));
    }

    else
    {
        printf("Something went wrong. Going back to teacher's panel\n");
        handleTeacherPanel();
    }
}

int isCCAlreadyAssigned(char *phone,char *cc)
{
    //true if cc is assigned to teacher[phone]
    struct cFormat //course format
    {
        char phone[21],cc[20];//cc = course code
    } cf1;

    FILE *ptr = fopen("course_assign.txt","rb");
    int checker=0;//course not assigned
    if(ptr!=NULL)
    {
        while(fread(&cf1,sizeof(cf1),1,ptr)!=0)
        {
            if(strcmp(cf1.phone,phone)==0 && strcmp(cf1.cc,cc)==0)
            {
                checker=1;
                break;//course already assigned
            }
        }
        fclose(ptr);
    }
    return checker;
}


//Remove+Enroll = remRoll
void remRoll(int isFromUpdate) //take input is optional
{
    FILE *ptr = fopen("student_course.txt","rb");
    struct STC_FORMAT stc;
    int counter=0;
    char **matched=0;
    if(ptr!=NULL)
    {
        while(fread(&stc,sizeof(stc),1,ptr)!=0)
        {
            if(strcmp(stc.phone,STUDENT_PHONE)==0)
            {
                if(!counter)
                {
                    printf("ENROLLED COURSES:");
                    if(isFromUpdate) printf("\n");
                }
                if(isFromUpdate)
                {

                    matched = realloc(matched,(counter+1)*sizeof(stc.cc));
                    matched[counter] = calloc(20,sizeof(char));
                    strcpy(matched[counter],stc.cc);

                    printf("%d)%s\t",counter+1,stc.cc);
                    if(counter%3==2) printf("\n");
                }
                else
                {
                    if(counter) printf(", ");
                    printf("\"%s\"",stc.cc);
                }
                counter++;
            }
        }
        fclose(ptr);
    }


    if(isFromUpdate)
    {
        if(counter%3!=0) printf("\n");
    }
    else printf("\n");

    if(isFromUpdate)//remove part
    {
        if(counter)
        {
            int val = getSelectedInput(counter,2);
            FILE *ptr2 = fopen("student_course.txt","rb");
            FILE *temp = fopen("temp_course.txt","ab");
            struct STC_FORMAT cs;
            if(ptr2!=NULL && temp!=NULL)
            {
                while(fread(&cs,sizeof(cs),1,ptr2)!=0)
                {
                    if(strcmp(cs.cc,matched[val-1])!=0 || strcmp(cs.phone,STUDENT_PHONE)!=0)
                    {
                        fwrite(&cs,sizeof(cs),1,temp);
                    }
                }

                fclose(ptr2);
                fclose(temp);
                remove("student_course.txt");
                rename("temp_course.txt","student_course.txt");
                printf("< - - \"%s\" REMOVED SUCCESSFULLY - - >\n",matched[val-1]);
                printf("1.Remove another \t2.Go Back \t3.Exit\nCommand:");
                showExtraCommandStudent(1);
            }
            else
            {
                if(ptr2!=NULL) fclose(ptr2);
                if(temp!=NULL) fclose(temp);
            }
        }
        else
        {
            printf("< - - OOPS!!!. YOU HAVEN'T ENROLLED ANY COURSE - - >\nPress Enter to go back...");
            char tempap[5];
            fgets(tempap,4,stdin);
            fflush(stdin);
            system("cls");
            handleStudentPanel();
        }

    }
    else
    {
        char cc[20];
        printf("Enter course code you want to enroll:");
        fgets(cc,20,stdin);
        fflush(stdin);
        while(cc[0]==10)
        {
            printf("Can't be empty. Enter again:");
            fgets(cc,20,stdin);
            fflush(stdin);
        }
        int j=0;
        while(cc[j]!='\n' && cc[j]!=0) j++;
        cc[j]=0;
        if(isCCAssignedToTeacher(cc))
        {
            FILE *ptr2 = fopen("student_course.txt","rb");
            struct STC_FORMAT st;
            int isPrinted=0;
            if(ptr2!=NULL)
            {
                while(fread(&st,sizeof(st),1,ptr2)!=0)
                {
                    if(strcmp(st.phone,STUDENT_PHONE)==0 && strcmp(st.cc,cc)==0)
                    {
                        isPrinted=1;
                        break;
                    }
                }
                fclose(ptr2);
            }
            if(isPrinted)
            {
                printf("< - - YOU HAVE ALREADY ENROLLED THIS COURSE - - >\n");
                printf("1.Enroll another \t2.Go Back \t3.Exit\nCommand:");
            }
            else
            {
                ptr2 = fopen("student_course.txt","ab");

                if(ptr2!=NULL)
                {

                    struct STUDENT sr;

                    //get student roll
                    FILE *src = fopen("student.txt","rb");
                    if(src!=NULL)
                    {
                        while(fread(&sr,sizeof(sr),1,src)!=0)
                        {
                            if(strcmp(sr.phone,STUDENT_PHONE)==0)
                            {
                                strcpy(st.dept,sr.dept);
                                strcpy(st.name,sr.name);
                                strcpy(st.roll,sr.roll);
                                break;
                            }
                        }
                        fclose(src);
                    }
                    //get student roll above

                    strcpy(st.phone,STUDENT_PHONE);
                    strcpy(st.cc,cc);
                    if(ptr2!=NULL)
                    {
                        fwrite(&st,sizeof(st),1,ptr2);
                        printf("< - - COURSE ENROLLED COMPLETED - - >\n");
                        printf("1.Enroll another \t2.Go Back \t3.Exit\nCommand:");
                    }
                    else
                    {
                        printf("Something went wrong.\n");
                        printf("1.Try again \t2.Go Back \t3.Exit\nCommand:");
                    }
                    fclose(ptr2);
                }
                else
                {
                    printf("< - - SOMETHING WENT WRONG - - >\n");
                }
            }


        }
        else
        {
            printf("< - - \"%s\" IS NOT ASSIGNED TO ANY TEACHER TILL NOW - - >\n",cc);
            printf("1.Try again \t2.Go Back \t3.Exit\nCommand:");
        }
        showExtraCommandStudent(0);
    }
}

int isCCAssignedToTeacher(char cc[21])
{
    //true if cc is assigned to any teacher else false
    struct cFormat //course format
    {
        char phone[21],cc[20];//cc = course code
    } cf1;
    int isAssign=0;//false
    FILE *ptr = fopen("course_assign.txt","rb");

    if(ptr!=NULL)
    {
        while(fread(&cf1,sizeof(cf1),1,ptr)!=0)
        {
            if(strcmp(cf1.cc,cc)==0)
            {
                isAssign = 1;
                break;
            }
        }
        fclose(ptr);
    }
    return isAssign;
}


void addCTMarks(int isFromUpdate)
{
    FILE *ptr = fopen("course_assign.txt","rb");
    if(ptr!=NULL)
    {
        struct cFormat //course format
        {
            char phone[21],cc[20];//cc = course code
        } cf1;

        int total_course=0;
        char **matched=0;
        while(fread(&cf1,sizeof(cf1),1,ptr)!=0)
        {
            if(strcmp(cf1.phone,TEACHER_PHONE)==0)
            {
                total_course++;
                matched = (char **) realloc(matched,(total_course)*sizeof(cf1.cc));
                matched[total_course-1] = calloc(20,sizeof(char));
                strcpy(matched[total_course-1],cf1.cc);
                if(!(total_course-1)) printf("ASSIGNED COURSES:\n");
                printf("%3d. %s\t",total_course,cf1.cc);
                if(total_course%2==0) printf("\n");
            }
        }
        fclose(ptr);

        if(total_course%2==1)printf("\n");
        if(total_course==0)
        {
            free(matched);
            printf("< - - YOU ARE NOT ASSIGNED TO ANY COURSES - - > Press enter to go back...");
            char tempa[5];
            fgets(tempa,4,stdin);
            fflush(stdin);
            system("cls");
            handleTeacherPanel();
            return;
        }
        else
        {
            int selectedNum = getSelectedInput(total_course,3);
            char cc[20];//class_code
            strcpy(cc,matched[selectedNum-1]);
            free(matched);

            char dep[21];
            printf("Enter department:");
            fgets(dep,21,stdin);
            fflush(stdin);
            while(dep[0]==10)
            {
                printf("Can't be empty. Enter dept::");
                fgets(dep,21,stdin);
                fflush(stdin);
            }
            int j=0;
            while(dep[j]!='\n' && dep[j]!=0) j++;
            dep[j]=0;

            int total = getTotalStudent(cc,dep,isFromUpdate);

            if(!total)
            {
                if(isFromUpdate) printf("< - - YOU HAVEN'T ADD CT MARKS TO THIS(\"%s\") COURSE - - > ",cc);
                else printf("< - - NO ONE FROM \"%s\" DEPARTMENT HAS ENROLLED THIS COURSE YET - - > ",dep);
                printf("Press enter to go back..");
                char extrA[5];
                fgets(extrA,5,stdin);
                fflush(stdin);
                system("cls");
                handleTeacherPanel();
                return;
            }
            else
            {
                char repl[7] = "add";
                if(isFromUpdate) strcpy(repl,"update");
                printf("Total %d students have enrolled this course. Are you sure you want to %s CT marks?\n",total,repl);
                printf("1) YES\t2) NO\nCommand:");

                //
                char cmd[3];
                fgets(cmd,3,stdin);
                fflush(stdin);
                while(cmd[0]<49 || cmd[0]>50 || cmd[1]!=10)
                {
                    printf("Please type 1 or 2 only\nCommand:");
                    fgets(cmd,3,stdin);
                    fflush(stdin);
                }

                if(cmd[0]=='1')
                {
                    printf("LEAVE \"BLANK\" FOR ABSENT.\n");
                    if(isFromUpdate)//UPDATE CT MARKS
                    {
                        printf("%20s%20s%20s%20s%20s\n","ROLL","NAME","DEPARTMENT","PRE. RESULT","ENTER NEW MARKS");
                        struct MARKS_FORMAT mfr;
                        FILE *ptr_up = fopen("ct_marks.txt","rb+");
                        if(ptr_up!=NULL)
                        {
                            while(fread(&mfr,sizeof(mfr),1,ptr_up)!=0)
                            {
                                if(strcmp(mfr.cc,cc)==0 && strcmp(mfr.dept,dep)==0 && strcmp(mfr.tphone,TEACHER_PHONE)==0)
                                {
                                    char ignored[10]=" ";
                                    printf("%20s%20s%20s%20s%15s",mfr.roll,mfr.name,mfr.dept,mfr.marks,ignored);
                                    char num[21];

                                    fgets(num,21,stdin);
                                    fflush(stdin);

                                    if(num[0]==10) strcpy(num,"Absent");
                                    else
                                    {
                                        int jj=0;
                                        while(num[jj]!='\n' && num[jj]!=0) jj++;
                                        num[jj]=0;//removing newline if have
                                    }
                                    fseek(ptr_up,-(long)sizeof(mfr),SEEK_CUR);
                                    strcpy(mfr.marks,num);
                                    strcpy(mfr.tphone,TEACHER_PHONE);
                                    fwrite(&mfr,sizeof(mfr),1,ptr_up);
                                    fseek(ptr_up,0,SEEK_CUR);
                                }
                            }
                            fclose(ptr_up);
                            printf("< - - MARKS SUCCESSFULLY UPPDATED. GOING BACK TO TEACHER'S PANEL. PLEASE WAIT");
                            Sleep(400);
                            printf(" -");
                            Sleep(500);
                            printf(" -");
                            Sleep(600);
                            printf(" >\n");
                            Sleep(700);
                            system("cls");
                        }
                        else
                        {
                            printf("Something went wrong. Going back to teacher's panel.\n");
                        }
                        handleTeacherPanel();
                    }
                    else//ADD CT MARKS
                    {
                        printf("%20s%20s%20s%20s\n","ROLL","NAME","DEPARTMENT","ENTER MARKS");
                        struct STC_FORMAT stc;
                        FILE *ptr_ad = fopen("student_course.txt","rb");
                        if(ptr_ad!=NULL)
                        {
                            while(fread(&stc,sizeof(stc),1,ptr_ad)!=0)
                            {
                                if(strcmp(stc.cc,cc)==0 && strcmp(stc.dept,dep)==0)
                                {
                                    printf("%20s%20s%20s%15s",stc.roll,stc.name,stc.dept,"");
                                    char num[21];
                                    fgets(num,21,stdin);
                                    fflush(stdin);

                                    if(num[0]==10) strcpy(num,"Absent");
                                    else
                                    {
                                        int jj=0;
                                        while(num[jj]!='\n' && num[jj]!=0) jj++;
                                        num[jj]=0;//removing newline if have
                                    }

                                    if(!isMarkAdded(stc.phone,cc,num))
                                    {
                                        struct MARKS_FORMAT mf1;
                                        //phone[21],cc[20],roll[21],name[51],dept[21],marks[21];
                                        strcpy(mf1.phone,stc.phone);
                                        strcpy(mf1.tphone,TEACHER_PHONE);
                                        strcpy(mf1.cc,stc.cc);
                                        strcpy(mf1.marks,num);
                                        strcpy(mf1.roll,stc.roll);
                                        strcpy(mf1.name,stc.name);
                                        strcpy(mf1.dept,stc.dept);

                                        FILE *ct_ptr = fopen("ct_marks.txt","ab");
                                        if(ct_ptr!=NULL)
                                        {
                                            fwrite(&mf1,sizeof(mf1),1,ct_ptr);
                                            fclose(ct_ptr);
                                        }
                                    }
                                }
                            }

                            fclose(ptr_ad);
                            printf("< - - MARKS SUCCESSFULLY ADDED. GOING BACK TO TEACHER'S PANEL. PLEASE WAIT");
                            Sleep(400);
                            printf(" -");
                            Sleep(500);
                            printf(" -");
                            Sleep(500);
                            printf(" >\n");
                            Sleep(600);
                            system("cls");
                        }
                        else
                        {
                            printf("Something went wrong. Going back to teacher's panel.\n");
                        }
                        handleTeacherPanel();
                        return;
                    }
                }
                else if(cmd[0]=='2')
                {
                    printf("< - - MARKS ADDING PROCESS CANCELED. GOING BACK TO TEACHER'S PANEL. PLEASE WAIT");
                    Sleep(300);
                    printf(" -");
                    Sleep(300);
                    printf(" -");
                    Sleep(450);
                    printf(" >\n");
                    Sleep(500);
                    system("cls");
                    handleTeacherPanel();
                    return;
                }
                else
                {
                    printf("Something went wrong. Going back to Teacher's panel.\n");
                    handleTeacherPanel();
                    return;
                }
            }
        }
    }
    else
    {
        printf("< - - YOU ARE NOT ASSIGNED TO ANY COURSE - - > Press Enter to go back...");
        char tempA[5];
        fgets(tempA,4,stdin);
        fflush(stdin);
        system("cls");
        handleTeacherPanel();
        return;
    }
}

int getTotalStudent(char cc[20],char dep[21],int isFromUpdate)
{
    //return total students in dep and enrolled to course cc
    if(!isFromUpdate)
    {
        FILE *ptr = fopen("student_course.txt","rb");
        struct STC_FORMAT stc;
        int counter=0;
        if(ptr!=NULL)
        {
            while(fread(&stc,sizeof(stc),1,ptr)!=0)
            {
                if(strcmp(stc.cc,cc)==0 && strcmp(stc.dept,dep)==0)counter++;
            }
            fclose(ptr);
        }
        return counter;
    }
    else
    {
        FILE *ptr_tmp = fopen("ct_marks.txt","rb");
        struct MARKS_FORMAT stc;
        int counter=0;
        if(ptr_tmp!=NULL)
        {
            while(fread(&stc,sizeof(stc),1,ptr_tmp)!=0)
            {
                if(strcmp(stc.tphone,TEACHER_PHONE)==0 && strcmp(stc.cc,cc)==0 &&
                   strcmp(stc.dept,dep)==0)counter++;
            }
            fclose(ptr_tmp);
        }
        return counter;
    }
}

int isMarkAdded(char phone[21],char cc[20],char marks[21])
{
    //return true after updating marks in ct_marks.txt otherwise return false without doing anything
    FILE *fpt = fopen("ct_marks.txt","rb+");

    struct MARKS_FORMAT mft;

    int checker=0;
    //phone[21],cc[20],marks[21],roll[21],name[51],dept[21];
    if(fpt!=NULL)
    {
        while(fread(&mft,sizeof(mft),1,fpt)!=0)
        {
            //printf("%s %s %s %s %s %s\n",mft.phone,mft.cc,mft.marks,mft.roll,mft.name,mft.dept);
            if(strcmp(mft.phone,phone)==0 && strcmp(mft.cc,cc)==0 && strcmp(mft.tphone,TEACHER_PHONE)==0)
            {
                //printf("phone matched\n");
                fseek(fpt,-(long)sizeof(mft),SEEK_CUR);
                strcpy(mft.marks,marks);
                fwrite(&mft,sizeof(mft),1,fpt);
                fseek(fpt,0,SEEK_CUR);
                checker=1;
                break;
            }
        }
        fclose(fpt);
    }
    return checker;
}

void showTotalStudents()
{
    //will show total student dept wise
    FILE *fst = fopen("student.txt","rb");//fst = file show total
    char **matched = 0;
    int *arr = calloc(1,sizeof(int));
    int size=0;
    struct STUDENT st3;
    if(fst!=NULL)
    {
        while(fread(&st3,sizeof(st3),1,fst)!=0)
        {
            //printf("name -%s %s-\n",st3.name,st3.dept);
            int checker=-1;
            for(int i=0; i<size; i++)
            {
                if(strcmp(matched[i],st3.dept)==0)
                {
                    checker=i;
                    break;
                }
            }
            if(checker==-1)
            {
                matched = (char **)realloc(matched,(size+1)*21*sizeof(char));
                matched[size] = calloc(21,sizeof(char));
                arr = (int *)realloc(arr,(size+1)*sizeof(int));
                strcpy(matched[size],st3.dept);
                arr[size]=1;
                size++;
            }
            else arr[checker]++;
        }
        fclose(fst);
    }
    if(size==0) printf("< - - NO STUDNET FOUND - - >\n");
    else
    {
        printf("%15s%15s\n","DEPARTMENT","TOTAL");
        for(int i=0; i<size; i++)
        {
            printf("%15s%15d\n",matched[i],arr[i]);
        }
    }
    free(matched);
    free(arr);
    printf("1. Go Back\t2.Exit\nCommand:");
    char inp[3];
    fgets(inp,3,stdin);
    fflush(stdin);
    while(inp[0]==10 || inp[1]!=10 || inp[0]<49 || inp[0]>50)
    {
        if(inp[0]==10) printf("Can't be empty. Enter Command:");
        else printf("Invalid Command. Enter Command:");
        fgets(inp,3,stdin);
        fflush(stdin);
    }
    if(inp[0]=='1')
    {
        system("cls");
        handleTeacherPanel();
    }
    else if(inp[0]=='2')
    {
        system("cls");
        printf("Program closed successfully.\n");
        exit(1);
    }
    else
    {
        printf("Something went wrong. Going back to student panel.\n");
        handleTeacherPanel();
    }
}

void showCTMarks()
{
    //will show current signed in students marks
    struct MARKS_FORMAT mf;
    FILE *ptr = fopen("ct_marks.txt","rb");
    int isPrinted=0;
    struct mFormat{
        char cc[20],tphone[21],tname[51],res[20];
    }*data;
    if(ptr!=NULL)
    {
        data = (struct mFormat*) malloc(1*sizeof(struct mFormat));
        while(fread(&mf,sizeof(mf),1,ptr)!=0)
        {
            if(strcmp(mf.phone,STUDENT_PHONE)==0)
            {
                strcpy(data[isPrinted].cc,mf.cc);
                strcpy(data[isPrinted].res,mf.marks);
                strcpy(data[isPrinted].tphone,mf.tphone);
                //if(!isPrinted) printf("%4s%20s%20s%20s\n","SN","COURSE","TEACHER","RESULT");
                isPrinted++;
                //printf("%4d%20s%20s\n",isPrinted,mf.cc,mf.marks);
                data = (struct mFormat*) realloc(data,(isPrinted+1)*sizeof(struct mFormat));

            }
        }
        fclose(ptr);
    }
    if(!isPrinted) printf("< - - NO MARKS FOUND - - >\n1.Refresh \t2.Go Back \t3.Exit\nCommand:");
    else{
        struct TEACHER tcr;
        for(int i=0;i<isPrinted;i++){
            FILE *tfile = fopen("teacher_list.txt","rb");
            if(tfile!=NULL){
                while(fread(&tcr,sizeof(tcr),1,tfile)){
                    if(strcmp(data[i].tphone,tcr.phone)==0){
                        strcpy(data[i].tname,tcr.name);
                        break;
                    }
                }
                fclose(tfile);
            }
        }
        printf("%4s%20s%20s%20s\n","SN","COURSE","TEACHER","MARKS");
        for(int i=0;i<isPrinted;i++) printf("%4d%20s%20s%20s\n",i+1,data[i].cc,data[i].tname,data[i].res);
        free(data);
        printf("1.Show again \t2.Go Back \t3.Exit\nCommand:");
    }
    showExtraCommandStudent(2);
}

void modifyAllStudentFiles(struct STUDENT nst,char pPhone[21],int isFromUpdate)
{
    FILE *ptr = fopen("student_course.txt","rb");
    FILE *temp = fopen("temp_course.txt","ab");
    struct STC_FORMAT st1;
    int checker=0;
    if(ptr!=NULL && temp!=NULL)
    {
        while(fread(&st1,sizeof(st1),1,ptr))
        {
            if(strcmp(st1.phone,pPhone)==0)
            {
                if(isFromUpdate)
                {
                    strcpy(st1.dept,nst.dept);
                    strcpy(st1.name,nst.name);
                    strcpy(st1.phone,nst.phone);
                    strcpy(st1.roll,nst.roll);
                    fwrite(&st1,sizeof(st1),1,temp);
                }
            }
            else fwrite(&st1,sizeof(st1),1,temp);
        }
        fclose(ptr);
        fclose(temp);
        remove("student_course.txt");
        rename("temp_course.txt","student_course.txt");
        checker++;
    }
    else
    {
        if(ptr!=NULL) fclose(ptr);
        if(temp!=NULL) fclose(temp);
    }
    struct MARKS_FORMAT mf;
    ptr = fopen("ct_marks.txt","rb");
    temp = fopen("temp_marks.txt","ab");
    if(ptr!=NULL && temp!=NULL)
    {
        while(fread(&mf,sizeof(mf),1,ptr))
        {
            if(strcmp(mf.phone,pPhone)==0)
            {
                if(isFromUpdate)
                {
                    strcpy(mf.dept,nst.dept);
                    strcpy(mf.name,nst.name);
                    strcpy(mf.phone,nst.phone);
                    strcpy(mf.roll,nst.roll);
                    fwrite(&mf,sizeof(mf),1,temp);
                }
            }
            else
            {
                fwrite(&mf,sizeof(mf),1,temp);
            }
        }
        fclose(ptr);
        fclose(temp);
        remove("ct_marks.txt");
        rename("temp_marks.txt","ct_marks.txt");
        checker++;
    }
    else
    {
        if(ptr!=NULL) fclose(ptr);
        if(temp!=NULL) fclose(temp);
    }
}

void modifyAllTeacherFiles(struct TEACHER nt,char pPhone[21],int isFromUpdate)
{
    FILE *ptr = fopen("course_assign.txt","rb");
    FILE *temp = fopen("temp_assign.txt","ab");
    struct cFormat //course format
    {
        char phone[21],cc[20];//cc = course code
    } cf;
    if(ptr!=NULL && temp!=NULL)
    {
        while(fread(&cf,sizeof(cf),1,ptr))
        {
            if(strcmp(cf.phone,pPhone)==0)
            {
                if(isFromUpdate){
                    strcpy(cf.phone,nt.phone);
                    fwrite(&cf,sizeof(cf),1,temp);
                }
            }
            else{
                fwrite(&cf,sizeof(cf),1,temp);
            }
        }
        fclose(ptr);
        fclose(temp);
        remove("course_assign.txt");
        rename("temp_assign.txt","course_assign.txt");
    }
    else{
        if(ptr!=NULL) fclose(ptr);
        if(temp!=NULL) fclose(temp);
    }

    ptr = fopen("ct_marks.txt","rb");
    temp = fopen("temp_marks.txt","ab");
    struct MARKS_FORMAT mft;
    if(ptr!=NULL && temp!=NULL){
        while(fread(&mft,sizeof(mft),1,ptr)){
            if(strcmp(mft.tphone,pPhone)==0){
                if(isFromUpdate){
                    strcpy(mft.tphone,nt.phone);
                    fwrite(&mft,sizeof(mft),1,temp);
                }
            }
            else{
                fwrite(&mft,sizeof(mft),1,temp);
            }
        }
        fclose(ptr);
        fclose(temp);
        remove("ct_marks.txt");
        rename("temp_marks.txt","ct_marks.txt");
    }
    else{
        if(ptr!=NULL) fclose(ptr);
        if(temp!=NULL) fclose(temp);
    }
}

void displayText(char *arr){
    char crr[] = {'-','~','*','.','+','o','=','^'};
    int len=0;
    while(arr[len]!=0) len++;
    printf("\n\t\t");
    for(int i=0;i<2*len+11;i++) printf("%c",crr[POSITION]);
    printf("\n\t\t%c     ",crr[POSITION]);

    for(int i=0;i<len-1;i++) printf("%c ",arr[i]);
    printf("%c     %c\n\t\t",arr[len-1],crr[POSITION]);

    for(int i=0;i<2*len+11;i++) printf("%c",crr[POSITION]);
    printf("\n\n");
    POSITION = (POSITION+1)%8;
}
