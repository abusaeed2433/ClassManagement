#include<stdio.h>

struct idPass
{
    char name[101];//name = phone(changed later)
    char pass[101];
};

struct STUDENT//student_list.txt
{
    char dept[21],roll[21],name[51],phone[21],email[51],addr[101],pass[51];
};

struct TEACHER//teacher_list.txt
{
    char dept[21],name[51],phone[21],email[51],addr[101],pass[51];
};

struct STC_FORMAT// student_course.txt
{
    char phone[21],cc[20],roll[21],name[51],dept[21];
};

struct MARKS_FORMAT//ct_marks.txt
{
    char phone[21],tphone[21],cc[20],roll[21],name[51],dept[21],marks[21];
};

int main(){
    printf("\t\t\tSHOWING ADMIN LIST[admin_list.txt]\n\n");
    FILE *ptr = fopen("admin_list.txt","rb");
    struct idPass admin;
    int counter=0;
    if(ptr!=NULL){
        printf("%5s %20s %20s\n","SN.","PHONE","PASSWORD");
        while(fread(&admin,sizeof(admin),1,ptr)){
            printf("%5d %20s %20s\n",counter+1,admin.name,admin.pass);
            counter++;
        }
    }
    fclose(ptr);
    printf("\n\n\n");

    printf("\t\t\tSHOWING TEACHER'S LIST[teacher_list.txt]\n\n");
    ptr = fopen("teacher_list.txt","rb");
    struct TEACHER tt;
    printf("%5s %12s %20s %12s %20s %20s %20s\n","SN.","DEPARTMENT","NAME","PHONE","EMAIL","ADDRESS","PASSWORD");
    counter=0;
    if(ptr!=NULL){
        while(fread(&tt,sizeof(tt),1,ptr)){
            printf("%5d %12s %20s %12s %20s %20s %20s\n",counter+1,tt.dept,tt.name,tt.phone,tt.email,tt.addr,tt.pass);
            counter++;
        }
        fclose(ptr);
    }



    printf("\n\t\t\tSHOWING STUDENT'S LIST[student.txt]\n\n");
    ptr = fopen("student.txt","rb");
    struct STUDENT st;
    printf("%5s %12s %20s %12s %12s %25s %20s %20s\n","SN.","DEPARTMENT","NAME","ROLL","PHONE","EMAIL","ADDRESS","PASSWORD");
    counter=0;
    if(ptr!=NULL){
        while(fread(&st,sizeof(st),1,ptr)){
            printf("%5d %12s %20s %12s %12s %25s %20s %20s\n",counter+1,st.dept,st.name,st.roll,st.phone,st.email,st.addr,st.pass);
            counter++;
        }
    }
    fclose(ptr);

    printf("\n\n\n");

    printf("\n\n\t\t\tSHOWING STUDENTS COURSE[student_course.txt]\n\n");
    ptr = fopen("student_course.txt","rb");
    counter=0;
    printf("%4s%20s%20s%20s%20s%20s\n","SN.","DEPT.","ROLL","NAME","PHONE","CODE");
    if(ptr!=NULL){
        //phone[21],cc[20],roll[21],name[51],dept[21];
        struct STC_FORMAT stc;
        while(fread(&stc,sizeof(stc),1,ptr)){
            printf("%4d%20s%20s%20s%20s%20s\n",counter+1,stc.dept,stc.roll,stc.name,stc.phone,stc.cc);
            counter++;
        }
        fclose(ptr);
    }

    printf("\n\n\t\t\tSHOWING ASSIGNED COURSE[course_assign.txt]\n\n");
    ptr = fopen("course_assign.txt","rb");
    counter=0;
    printf("%4s%20s%20s\n","SN.","PHONE","CODE");
    if(ptr!=NULL){
        struct cFormat //course_assign.txt
        {
            char phone[21],cc[20];//cc = course code
        } cf1;

        while(fread(&cf1,sizeof(cf1),1,ptr)){
            counter++;
            printf("%4d%20s%20s\n",counter,cf1.phone,cf1.cc);
        }
        fclose(ptr);
    }

    printf("\n\n\t\t\tSHOWING CT MARKS[ct_marks.txt]\n\n");

    ptr = fopen("ct_marks.txt","rb");
    counter=0;
    //char phone[21],cc[20],roll[21],name[51],dept[21],marks[21];
    printf("%4s%20s%20s%20s%20s%20s%20s%20s\n","SN.","DEPT","ROLL","NAME","PHONE","TPHONE","CODE","MARKS");
    if(ptr!=NULL){
        struct MARKS_FORMAT mf;
        while(fread(&mf,sizeof(mf),1,ptr)){
            counter++;
            printf("%4d%20s%20s%20s%20s%20s%20s%20s\n",counter,mf.dept,mf.roll,mf.name,mf.phone,mf.tphone,mf.cc,mf.marks);
        }
        fclose(ptr);
    }

    return 0;
}
