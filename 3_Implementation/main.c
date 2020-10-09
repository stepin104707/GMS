#include<stdio.h>
#include<conio.h>
void insertion();
void display();
void deletion();
void sorting();
void update();
void search();
struct student
{
	int roll;
	char sec[10];
	char name[200];
	int marks;
	float grade;
};
struct student s;
void main()
{
	int ch;
	while(ch!=7)
	{
		printf("\t***************************************************************\n");
		printf("\t\t WELCOME TO GRADES MANAGEMENT SYSTEM\n");
		printf("\t***************************************************************\n\n\n");

		printf("OPERATIONS CAN BE PERFORMED\n");
		printf("\t\t1) INSERT STUDENT RECORDS\n");
		printf("\t\t2) DISPLAY STUDENT RECORD\n");
		printf("\t\t3) DELETE STUDENT RECORD\n");
		printf("\t\t4) SEARCH STUDENT RECORD BY ROLLNUMBER\n");
		printf("\t\t5) UPDATE  STUDENT RECORD\n");
		printf("\t\t6) SORT STUDENT RECORD\n");
		printf("\t\t7) EXIT\n\n");

		printf("ENTER YOUR CHOICE: ");
		scanf("%d",&ch);
		switch(ch)
		{
		   case 1: insertion();
		           break;
		   case 2: display();
		            break;
		   case 3: deletion();
		            break;
		   case 4: search();
		            break;
		   case 5: update();
		            break;
		   case 6: sorting();
		            break;
		   case 7: exit(1);
		   default:
		          printf("\n\t\t WRONG CHOICE ENTERED");
			}
		printf("\n\t\tPress key to Continue");
		getch();
	}
}
void insertion()
{
	FILE *fp;
	fp=fopen("student.txt","ab+");

	if(fp==NULL)
	{
		printf("\n\t\t Error: Cannot open the File!!!");
		return 0;
	}
	printf("\t****Previous stored data****");
	display();

	printf("\n\n\t*****ENTER NEW STUDENT DATA*****\n\n");
	printf("\n\t\t Enter Student roll number:");
	scanf("%d",&s.roll);
	fflush(stdin);
	printf("\n\t\t Enter student name: ");
	gets(s.name);
	printf("\n\t\t Enter student section: ");
	gets(s.sec);
	printf("\n\t\t Enter student Total marks: ");
	scanf("%d",&s.marks);
	printf("\n\t\t Enter student grade: ");
	scanf("%f",&s.grade);
	fwrite(&s,sizeof(s),1,fp);
	{

	    printf("\n\n\t !!! Student record inserted Successfully\n");

	}
	fclose(fp);
	printf("\n\t\t Updated Record!!\n");
	display();
}
void display()
{

    FILE *fp;
    fp=fopen("student.txt","rb");

    if(fp==NULL)
    {

        printf("\n\t\tError: cannot open the file");
        return 0;

    }
    printf("\n\n\t******** Student details as follows****\n");
    printf("\n Roll number\t Name of the student\t section\t\tMarks\t\tGrade\n\n");
   // printf("a.student rollnumber\tb.student name\tc.student section\t\t d.student marks\t\t e.student grade\n");
    while(fread(&s,sizeof(s),1,fp)==1)
    {

        printf("\t%d\t\t%s\t\t\%s  \t\t%d\t\t\t%f\n",s.roll,s.name,s.sec,s.marks,s.grade);
    }
    fclose(fp);
}
void search()
{

    int ro,flag=0;
    FILE *fp;
    fp=fopen("student.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\tError:cannot open the file****");
        return 0;
    }
    printf("\n\n\t Enter the student roll number in which you want to search: ");
    scanf("%d",&ro);
    while(fread(&s,sizeof(s),1,fp)>0 && flag==0)
    {

        if(s.roll==ro)
        {
            flag=1;
            printf("\n\n\tSearching is Successfull and Student record is as follows");
            printf("\n Roll number\t Name of the student\t section\t\tMarks\t\tGrade\n\n");
            printf("%d\t%s\t%s\t\t%d\t\t%f\n",s.roll,s.name,s.sec,s.marks,s.grade);

        }
        if(flag==0)
        {
            printf("No such record found!!!\n");
        }
    }
    fclose(fp);
}
void deletion()
{

    char name[40];
    unsigned flag=0;
    FILE *fp,*ft;
    fp=fopen("student.txt","rb");
   // ft=fopen("student1.txt","ab+");
    if(fp==NULL)
    {

        printf("\n\t\t Error:cannot open the file!!1");
        return 0;
    }
    printf("\n\t\t *********Previously Stored data**********");
    display();
    printf("\n\n\tEnter the student name in which you want to delete\n");
    scanf("%s",name);
    ft=fopen("student1.txt","ab+");
    while(fread(&s,sizeof(s),1,fp)==1)
    {

        if(strcmp(name,s.name)!=0)
        {
         printf("\n\t\t Record deleted Successfully\n");
         fwrite(&s,sizeof(s),1,ft);

        }
        else
            flag=1;
    }
    if(flag==0)
    {

        printf("\n\t\t\t No such Record found!!!");
    }
    fclose(ft);
    fclose(fp);
    remove("student.txt");
    rename("student1.txt","student.txt");
    printf("\n\t\t Updated Record !!\n");
    display();
}
void update()
{

    int ro,flag=0;
    FILE *fp;
    fp=fopen("student.txt","rb+");
    if(fp==NULL)
    {

        printf("\n\t\t Error:cannot open the file!!!");
        return 0;
    }
    printf("\n\n\t Enter the roll number of the student in which you want to update");
    scanf("%d",&ro);
    printf("\n\t\t********Previously stored record of given roll number******\n");
    while(fread(&s,sizeof(s),1,fp)>0 && flag==0)
    {

        if(s.roll==ro)
        {

            flag=1;
            printf("\n Roll number\t Name of the student\t section\t\tMarks\t\tGrade\n\n");
            printf("%d\t%s\t%s\t\t%d\t\t%f\n",s.roll,s.name,s.sec,s.marks,s.grade);
            printf("\n\t\t*********Now Enter the New record******\n\n");
            printf("\n\t\t Updated student roll number: ");
            scanf("%d",&s.roll);
            fflush(stdin);
            printf("\n\t\t Updated student name: ");
            gets(s.name);
            printf("\n\t\t Updated student section: ");
            gets(s.sec);
            printf("\n\t\t Updated student Marks: ");
            scanf("%d",&s.marks);
            printf("\n\t\t Updated student grade: ");
            scanf("%d",&s.grade);
            fseek(fp,-(long)sizeof(s),1);
            fwrite(&s,sizeof(s),1,fp);
            printf("\n\n\t Record Updated Successfully  ");

        }
        if(flag==0)
           {
               printf("\n\t\t Error:Something went wrong");
           }

    }
    fclose(fp);
}
void sorting()
{

    struct student temp;
    struct student arr[50];
    int i,j,k=0;
    FILE *fp;
    fp=fopen("student.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\t Error:cannot open the file\n");
        return 0;
    }
    i=0;
    while(fread(&arr[i],sizeof(arr[i]),1,fp)==1)
    {

        i++;
        k++;
    }
    for(i=0;i<k;i++)
    {
        for(j=0;j<k-i-1;j++)
        {
            if(arr[j].roll>arr[j+1].roll)
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    printf("\n\t\t After sorting student details as follows\n\n");
    for(i=0;i<k;i++)
    {
        printf("%d\t\t%s\t\t%s\t\t%d\t\t%f\n",arr[i].roll,arr[i].name,arr[i].sec,arr[i].marks,arr[i].grade);

    }
    fclose(fp);
}

