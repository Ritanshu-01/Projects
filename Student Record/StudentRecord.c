#include <stdio.h>   // For input output functions like printf , scanf
#include <windows.h> // For windows related functions
#include <conio.h>   // For getch() like functions
#include <string.h>  // For string manipulation functions
#include <stdlib.h>  // For malloc function or using file handling

void gotoxy(int, int); // To format the text
void page1(void);      // Code for page 1
void details(void);
void line(int); // Code to print line
void password(void);
void signIn(void);
void signUp(void);
void addRecord(void);     // Code to add student record through linked list
void displayRecord(void); // Code to display record
void deleteRecord(void);  // Code to delete the record of previous student
void updateRecord(void);  // Code to update the record of previous student
void searchRecord(void);  // Code to search the record
void Exit(void);          // Code to terminate everything

// Structure to make a node to store the student details
typedef struct student
{
    int fees, id;
    char name[13], smobile[12];
    char fname[13], fmobile[12], email[34], course[11];
    struct student *next;
} st;
// Structure to fetch details from file , store into structure members through linked list
struct Student
{
    int ffees, fid;
    char fname[13], ffname[13], ffmobile[11], femail[34], fsmobile[11], fcourse[11];
} stu;

// Structure for password generation.
typedef struct Password
{
    char _uname[20];
    char _pass[20];
    char _email[50];
    struct Password *_next;
} pass;

st *head, *newnode, *temp, *fnewnode, *temp2; // pointers to structure student
/* head pointer points to the starting of the list
   newnode pointer points to the newnode
   temp pointer is used to traverse the linked list
   fnewnode is used to fetch details from file and store into node to make a linked list*/
FILE *fp = NULL; // File pointer fp is used to handle the file StudentRecord.txt
int srno = 0, k = 0;

int main()
{
    password();
    while (1)
    {
        system("color B4");
        page1();
        int choice = 0;
    start1:
        gotoxy(40, 22);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            displayRecord();
            break;
        case 3:
            deleteRecord();
            break;
        case 4:
            updateRecord();
            break;
        case 5:
            searchRecord();
            break;
        case 6:
            Exit();
            break;
        default:
            gotoxy(0, 22);
            printf("\33[2K\r");
            goto start1;
            break;
        }
    }

    return 0;
}
// Function used to coordinate the text
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void page1(void)
{
    system("cls");
    system("color B4");
    gotoxy(40, 2);
    printf("WELCOME TO STUDENT MANAGEMENT SYSTEM");
    gotoxy(39, 3);
    line(39);
    gotoxy(40, 7);
    printf("1. Add New Record");
    gotoxy(40, 9);
    printf("2. Display Previous Record");
    gotoxy(40, 11);
    printf("3. Delete Previous Record");
    gotoxy(40, 13);
    printf("4. Update Previous Record");
    gotoxy(40, 15);
    printf("5. Search Previous Record");
    gotoxy(40, 17);
    printf("7. Exit");
}

void details(void)
{
    gotoxy(50, 1);
    printf("STUDENT RECORD");
    gotoxy(49, 2);
    for (int i = 0; i < 17; i++)
    {
        printf("-");
    }
    gotoxy(1, 5);
    printf("ID");
    gotoxy(7, 5);
    printf("STUDENT NAME");
    gotoxy(22, 5);
    printf("S.MOBILE");
    gotoxy(37, 5);
    printf("FATHER NAME");
    gotoxy(52, 5);
    printf("F.MOBILE");
    gotoxy(67, 5);
    printf("EMAIL");
    gotoxy(103, 5);
    printf("COURSE");
    gotoxy(113, 5);
    printf("FEES");
}
// Function to make a line
void line(int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("-");
    }
}
// Function for password
void password(void)
{
    system("color A4");
    char choice;
    gotoxy(45, 7);
    printf("APPLICATION LOGIN");
    gotoxy(43, 8);
    line(22);
    gotoxy(45, 10);
    printf("1. Sign in");
    gotoxy(45, 11);
    printf("2. Sign up");
start:
    gotoxy(45, 13);
    printf("Enter choice: ");
    scanf("%c", &choice);
    switch (choice)
    {
    case '1':
        system("cls");
        signIn();
        break;
    case '2':
        system("cls");
        signUp();
        break;
    default:
        gotoxy(0, 13);
        printf("\33[2K\r");
        goto start;
        break;
    }
}
void signIn(void)
{
    system("color B4");
    int flag = 0, passLength = 0;
    char _funame[20], _femail[50];
    char _fpass[20], _pass1[20];
    pass *head, *temp, *new;
    FILE *fp = NULL;
    char _user_name[20];
    fp = fopen("Password1.txt", "a+");
    if (fp == NULL)
    {
        puts("Error : Cannot open Password.txt file.");
        exit(1);
    }
    head = temp = new = NULL;
    while (fscanf(fp, "%s %s %s", _funame, _femail, _fpass) != EOF)
    {
        new = malloc(sizeof(pass));
        strcpy(new->_uname, _funame);
        strcpy(new->_email, _femail);
        strcpy(new->_pass, _fpass);
        new->_next = NULL;

        if (head == NULL)
        {
            head = temp = new;
        }
        else
        {
            temp->_next = new;
            temp = new;
        }
    }
    gotoxy(50, 8);
    printf("SIGN IN DETAILS");
    gotoxy(48, 9);
    line(20);
start1:
    flag = 0;
    gotoxy(45, 11);
    printf("Username/Email\t:");
    gotoxy(67, 11);
    fflush(stdin);
    gets(_user_name);
    temp = head;
    while (temp != NULL)
    {
        if (strcmp(_user_name, temp->_uname) == 0 || strcmp(_user_name, temp->_email) == 0)
        {
            gotoxy(0, 12);
            printf("\33[2K\r");
            passLength = strlen(temp->_pass);
            strcpy(_pass1, temp->_pass);
            flag++;
            break;
        }
        temp = temp->_next;
    }
    if (flag == 0)
    {
        gotoxy(0, 11);
        printf("\33[2K\r");
        gotoxy(45, 12);
        printf("Wrong Username or email. Try Again.");
        goto start1;
    }
    char _password[passLength];
    do
    {
        gotoxy(0, 12);
        printf("\33[2K\r");
        gotoxy(45, 12);
        puts("Password\t\t:");
        gotoxy(67, 12);
        fflush(stdin);
        int i = 0;
        while (i < passLength)
        {
            _password[i] = getch();
            printf("*");
            i++;
        }
        _password[i] = '\0';
    } while (strcmp(_pass1, _password) != 0);
    gotoxy(45, 14);
    printf("Press Enter key to Log in.");
    fclose(fp);
    getch();
}
void signUp(void)
{
    system("color B4");
    int flag = 0, passLength = 0;
    char _funame[20], _femail[50];
    char _fpass[20];
    pass *head, *temp, *new;
    FILE *fp = NULL;
    char _user_name[50], _user_email[50], _user_pass[20];
    fp = fopen("Password1.txt", "a+");
    if (fp == NULL)
    {
        puts("Error : Cannot open Password.txt file.");
        exit(1);
    }
    head = temp = new = NULL;
    while (fscanf(fp, "%s %s %s", _funame, _femail, _fpass) != EOF)
    {
        new = malloc(sizeof(pass));
        strcpy(new->_uname, _funame);
        strcpy(new->_email, _femail);
        strcpy(new->_pass, _fpass);
        new->_next = NULL;

        if (head == NULL)
        {
            head = temp = new;
        }
        else
        {
            temp->_next = new;
            temp = new;
        }
    }
    gotoxy(50, 8);
    printf("SIGN UP DETAILS");
    gotoxy(48, 9);
    line(20);
start2:
    gotoxy(45, 11);
    printf("Email\t:");
    gotoxy(60, 11);
    fflush(stdin);
    gets(_user_email);
    temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->_email, _user_email) == 0)
        {
            gotoxy(45, 12);
            printf("This email is already exists. Please enter another.");
            gotoxy(0, 11);
            printf("\33[2K\r");
            goto start2;
        }
        temp = temp->_next;
    }
    gotoxy(0, 12);
    printf("\33[2K\r");
start3:
    gotoxy(45, 12);
    printf("Username\t:");
    gotoxy(60, 12);
    fflush(stdin);
    gets(_user_name);
    temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->_uname, _user_name) == 0)
        {
            gotoxy(45, 13);
            printf("This username is already exists. Please enter another.");
            gotoxy(0, 12);
            printf("\33[2K\r");
            goto start3;
        }
        temp = temp->_next;
    }
    gotoxy(0, 13);
    printf("\33[2K\r");
    gotoxy(45, 13);
    printf("Password\t:");
    gotoxy(60, 13);
    fflush(stdin);
    gets(_user_pass);
    fprintf(fp, "\n%s %s %s", _user_name, _user_email, _user_pass);
    gotoxy(45, 15);
    printf("Please press Enter key to Log in.");
    fclose(fp);
    getch();
}
// Function to add record of student
void addRecord(void)
{
    system("cls");
    details();
    gotoxy(1, 6);
    line(119);

    // Opening file in a+ mode
    fp = fopen("StudentRecord.txt", "a+");
    if (fp == NULL)
    {
        printf("Error While opening file.");
        exit(1);
    }

    // Allocation of memory
    newnode = malloc(sizeof(st));
    if (newnode == NULL)
    {
        printf("Error: Memory not Allocated.");
        exit(1);
    }
    srno = 1;
    k = 8;
    char more;
    head = NULL;
    do
    {
        gotoxy(2, k);
        scanf("%d", &newnode->id);
        fprintf(fp, "%d ", newnode->id);
        gotoxy(7, k);
        fflush(stdin);
        fgets(newnode->name, sizeof(newnode->name), stdin);
        newnode->name[strlen(newnode->name) - 1] = '\0';
        fprintf(fp, "%s ", newnode->name);
        gotoxy(22, k);
        fflush(stdin);
        fgets(newnode->smobile, sizeof(newnode->smobile), stdin);
        newnode->smobile[strlen(newnode->smobile) - 1] = '\0';
        fprintf(fp, "%s ", newnode->smobile);
        gotoxy(37, k);
        fflush(stdin);
        fgets(newnode->fname, sizeof(newnode->fname), stdin);
        newnode->fname[strlen(newnode->fname) - 1] = '\0';
        fprintf(fp, "%s ", newnode->fname);
        gotoxy(52, k);
        fflush(stdin);
        fgets(newnode->fmobile, sizeof(newnode->fmobile), stdin);
        newnode->fmobile[strlen(newnode->fmobile) - 1] = '\0';
        fprintf(fp, "%s ", newnode->fmobile);
        gotoxy(67, k);
        fflush(stdin);
        fgets(newnode->email, sizeof(newnode->email), stdin);
        newnode->email[strlen(newnode->email) - 1] = '\0';
        fprintf(fp, "%s ", newnode->email);
        gotoxy(103, k);
        fflush(stdin);
        fgets(newnode->course, sizeof(newnode->course), stdin);
        newnode->course[strlen(newnode->course) - 1] = '\0';
        fprintf(fp, "%s ", newnode->course);
        gotoxy(113, k);
        scanf("%d", &newnode->fees);
        fprintf(fp, "%d\n", newnode->fees);
        newnode->next = NULL;
        if (head == NULL)
        {
            head = temp = newnode;
        }
        else
        {
            temp->next = newnode;
            temp = newnode;
        }
        k++;
        gotoxy(1, srno + 20);
        printf("Do You want to add more record? Press (y/n).  ");
        fflush(stdin);
        scanf("%c", &more);
        if (more == 'y')
        {
            gotoxy(1, srno + 20);
            printf("\33[2K\r");
            srno++;
        }
    } while (more == 'y');

    fclose(fp);
    getch();
}
// Function to display record of student
void displayRecord(void)
{
    system("cls");
    system("color A4");
    // Opening file in r mode
    fp = fopen("StudentRecord.txt", "r");
    if (fp == NULL)
    {
        printf("Error While opening file.");
        exit(1);
    }
    head = NULL;
    while (fscanf(fp, "%d %s %s %s %s %s %s %d", &stu.fid, stu.fname, stu.fsmobile, stu.ffname, stu.ffmobile, stu.femail, stu.fcourse, &stu.ffees) != EOF)
    {
        fnewnode = malloc(sizeof(st));
        fnewnode->id = stu.fid;
        strcpy(fnewnode->name, stu.fname);
        strcpy(fnewnode->smobile, stu.fsmobile);
        strcpy(fnewnode->fname, stu.ffname);
        strcpy(fnewnode->fmobile, stu.ffmobile);
        strcpy(fnewnode->email, stu.femail);
        strcpy(fnewnode->course, stu.fcourse);
        fnewnode->fees = stu.ffees;
        fnewnode->next = NULL;

        if (head == NULL)
        {
            head = temp = fnewnode;
        }
        else
        {
            temp->next = fnewnode;
            temp = fnewnode;
        }
    }
    details();
    gotoxy(1, 6);
    line(119);
    temp = head;
    k = 8;
    while (temp != NULL)
    {
        gotoxy(2, k);
        printf("%d", temp->id);
        gotoxy(7, k);
        printf("%s", strupr(temp->name));
        gotoxy(22, k);
        printf("%s", temp->smobile);
        gotoxy(37, k);
        printf("%s", strupr(temp->fname));
        gotoxy(52, k);
        printf("%s", temp->fmobile);
        gotoxy(67, k);
        printf("%s", temp->email);
        gotoxy(103, k);
        printf("%s", temp->course);
        gotoxy(113, k);
        printf("%d", temp->fees);
        temp = temp->next;
        k++;
    }

    fclose(fp);
    getch();
}
// Function to delete record of student
void deleteRecord(void)
{
    system("cls");
    system("color A4");
    // Opening file in r mode
    fp = fopen("StudentRecord.txt", "r");
    if (fp == NULL)
    {
        printf("Error While opening file.");
        exit(1);
    }
    FILE *fd = NULL;
    fd = fopen("DeletedRecord.txt", "a+");
    if (fd == NULL)
    {
        printf("Error: While opening DeletedRecord.txt file.");
        exit(1);
    }
    head = NULL;
    while (fscanf(fp, "%d %s %s %s %s %s %s %d", &stu.fid, stu.fname, stu.fsmobile, stu.ffname, stu.ffmobile, stu.femail, stu.fcourse, &stu.ffees) != EOF)
    {
        fnewnode = (st *)malloc(sizeof(st));
        fnewnode->id = stu.fid;
        strcpy(fnewnode->name, stu.fname);
        strcpy(fnewnode->smobile, stu.fsmobile);
        strcpy(fnewnode->fname, stu.ffname);
        strcpy(fnewnode->fmobile, stu.ffmobile);
        strcpy(fnewnode->email, stu.femail);
        strcpy(fnewnode->course, stu.fcourse);
        fnewnode->fees = stu.ffees;
        fnewnode->next = NULL;
        if (head == NULL)
        {
            head = temp = fnewnode;
        }
        else
        {
            temp->next = fnewnode;
            temp = fnewnode;
        }
    }
    int search_id = 0;
    fflush(stdin);
    gotoxy(1, 2);
    printf("Whose detail you want to delete? Please Enter ID.  ");
    scanf("%d", &search_id);
    int flag = 0;
    st *dp = NULL; // dp = pointer to perform delete operation
    temp = dp = head;
    temp2 = NULL;
    // Searching of record and deletion of node.
    while (temp != NULL)
    {
        if (head->id == search_id)
        {
            head = head->next;
            temp2 = head;
            flag = 0;
            free(dp);
            break;
        }
        else if (temp->id == search_id)
        {
            dp->next = temp->next;
            temp2 = temp;
            flag = 0;
            free(temp);
            break;
        }
        else if (temp->id == search_id && temp->next == NULL)
        {
            dp->next = NULL;
            temp2 = temp;
            flag = 0;
            free(temp);
            break;
        }
        flag = 1;
        dp = temp;
        temp = temp->next;
    }
    // Printing message and deleting record if found.
    if (flag == 1)
    {
        gotoxy(1, 4);
        printf("No such record found with ID - %d.", search_id);
        gotoxy(1, 5);
        printf("Please press any key to go back to main menu.");
        fclose(fp);
        getch();
        return;
    }
    // system("cls");
    // system("color D7");
    // details();
    // gotoxy(1,6);
    // line(119);
    // gotoxy(2,8);
    // printf("%d", temp2->id);
    // gotoxy(7,8);
    // printf("%s", strupr(temp2->name));
    // gotoxy(22,8);
    // printf("%s", temp2->smobile);
    // gotoxy(37,8);
    // printf("%s", strupr(temp2->fname));
    // gotoxy(52,8);
    // printf("%s", temp2->fmobile);
    // gotoxy(67,8);
    // printf("%s", temp2->email);
    // gotoxy(103,8);
    // printf("%s", temp2->course);
    // gotoxy(113,8);
    // printf("%d", temp2->fees);
    char want_delete;
    fflush(stdin);
    gotoxy(1, 11);
    printf("Really want to delete this record. Press(y/n):  ");
    scanf("%c", &want_delete);
    fflush(stdin);
    if (want_delete == 'y' || want_delete == 'Y')
    {
        FILE *ft = NULL;
        ft = fopen("temp.txt", "w");
        if (ft == NULL)
        {
            printf("Error: Cannot open file.");
            exit(1);
        }

        temp = head;
        while (temp != NULL)
        {
            fprintf(ft, "%d ", temp->id);
            fprintf(ft, "%s ", temp->name);
            fprintf(ft, "%s ", temp->smobile);
            fprintf(ft, "%s ", temp->fname);
            fprintf(ft, "%s ", temp->fmobile);
            fprintf(ft, "%s ", temp->email);
            fprintf(ft, "%s ", temp->course);
            fprintf(ft, "%d\n", temp->fees);
            temp = temp->next;
        }

        fclose(fp);
        fclose(ft);

        remove("StudentRecord.txt");             /// remove the orginal file
        rename("temp.txt", "StudentRecord.txt"); /// rename the temp file to original file name

        gotoxy(1, 13);
        printf("The Record with ID - %d has been successfully deleted.", search_id);
        gotoxy(1, 14);
        printf("Please press any key to go back to main menu.");
    }
    else
    {
        gotoxy(1, 13);
        printf("The Record has been saved successfully.");
        gotoxy(1, 14);
        printf("Please press any key to go back to main menu.");
        fclose(fp);
    }
    getch();
}
// Function to update record of student
void updateRecord(void)
{
    system("cls");
    system("color A4");

    // Opening file in a+ mode
    fp = fopen("StudentRecord.txt", "a+");
    if (fp == NULL)
    {
        printf("Error While opening file.");
        exit(1);
    }

    head = NULL;
    while (fscanf(fp, "%d %s %s %s %s %s %s %d", &stu.fid, stu.fname, stu.fsmobile, stu.ffname, stu.ffmobile, stu.femail, stu.fcourse, &stu.ffees) != EOF)
    {
        fnewnode = (st *)malloc(sizeof(st));
        fnewnode->id = stu.fid;
        strcpy(fnewnode->name, stu.fname);
        strcpy(fnewnode->smobile, stu.fsmobile);
        strcpy(fnewnode->fname, stu.ffname);
        strcpy(fnewnode->fmobile, stu.ffmobile);
        strcpy(fnewnode->email, stu.femail);
        strcpy(fnewnode->course, stu.fcourse);
        fnewnode->fees = stu.ffees;
        fnewnode->next = NULL;
        if (head == NULL)
        {
            head = temp = fnewnode;
        }
        else
        {
            temp->next = fnewnode;
            temp = fnewnode;
        }
    }
    int search_id = 0;
    gotoxy(1, 2);
    printf("Whose detail you want to update? Please Enter ID.  ");
    scanf("%d", &search_id);
    fflush(stdin);
    int flag = 0;
    temp = head;
    while (temp != NULL)
    {
        if (temp->id == search_id)
        {
            flag = 0;
            break;
        }
        temp = temp->next;
        flag = 1;
    }
    // if(flag==1)
    // {
    //     gotoxy(1,4);
    //     printf("Sorry, No such record found with ID - %d.",search_id);
    //     gotoxy(1,5);
    //     printf("Please press any key to go back to main menu.");
    //     fclose(fp);
    //     getch();
    //     return;
    // }
    system("cls");
    system("color D7");
    details();
    gotoxy(1, 6);
    line(119);
    gotoxy(2, 8);
    printf("%d", temp->id);
    gotoxy(7, 8);
    printf("%s", strupr(temp->name));
    gotoxy(22, 8);
    printf("%s", temp->smobile);
    gotoxy(37, 8);
    printf("%s", strupr(temp->fname));
    gotoxy(52, 8);
    printf("%s", temp->fmobile);
    gotoxy(67, 8);
    printf("%s", temp->email);
    gotoxy(103, 8);
    printf("%s", temp->course);
    gotoxy(113, 8);
    printf("%d", temp->fees);
    gotoxy(40, 15);
    printf("What do you want to update?");
    gotoxy(40, 17);
    printf("Press the following:");
    gotoxy(40, 20);
    printf("1. Student Name");
    gotoxy(40, 22);
    printf("2. Student Mobile No");
    gotoxy(40, 24);
    printf("3. Father Name");
    gotoxy(40, 26);
    printf("4. Father Mobile No");
    gotoxy(40, 28);
    printf("5. Email");
    gotoxy(40, 30);
    printf("6. Course");
    gotoxy(40, 32);
    printf("7. Fees");
    int choice = 0;
    gotoxy(40, 36);
    printf("Enter Choice: ");
    scanf("%d", &choice);
    fflush(stdin);
    switch (choice)
    {
    case 1:
        system("cls");
        gotoxy(1, 3);
        printf("Previous Student Name : %s", temp->name);
        gotoxy(1, 5);
        printf("Enter Correct Student Name: ");
        fgets(temp->name, sizeof(temp->name), stdin);
        temp->name[strlen(temp->name) - 1] = '\0';
        break;
    case 2:
        system("cls");
        gotoxy(1, 3);
        printf("Previous Student Mobile: %s", temp->smobile);
        gotoxy(1, 5);
        printf("Enter Correct Student Mobile: ");
        fgets(temp->smobile, sizeof(temp->smobile), stdin);
        temp->smobile[strlen(temp->smobile) - 1] = '\0';
        break;
    case 3:
        system("cls");
        gotoxy(1, 3);
        printf("Previous Father Name: %s", temp->fname);
        gotoxy(1, 5);
        printf("Enter Correct Father Name: ");
        fgets(temp->fname, sizeof(temp->fname), stdin);
        temp->fname[strlen(temp->fname) - 1] = '\0';
        break;
    case 4:
        system("cls");
        gotoxy(1, 3);
        printf("Previous Father Mobile: %s", temp->fmobile);
        gotoxy(1, 5);
        printf("Enter Correct Father Mobile: ");
        fgets(temp->fmobile, sizeof(temp->fmobile), stdin);
        temp->fmobile[strlen(temp->fmobile) - 1] = '\0';
        break;
    case 5:
        system("cls");
        gotoxy(1, 3);
        printf("Previous Email: %s", temp->email);
        gotoxy(1, 5);
        printf("Enter Correct Email: ");
        fgets(temp->email, sizeof(temp->email), stdin);
        temp->email[strlen(temp->email) - 1] = '\0';
        break;
    case 6:
        system("cls");
        gotoxy(1, 3);
        printf("Previous Course: %s", temp->course);
        gotoxy(1, 5);
        printf("Enter Correct Course: ");
        fgets(temp->course, sizeof(temp->course), stdin);
        temp->course[strlen(temp->course) - 1] = '\0';
        break;
    case 7:
        system("cls");
        gotoxy(1, 3);
        printf("Previous Fees: %s", temp->fees);
        gotoxy(1, 5);
        printf("Enter Correct Fees: ");
        scanf("%d", &temp->fees);
        break;
    default:
        break;
    }

    FILE *ft = NULL;
    ft = fopen("temp.txt", "w");
    if (ft == NULL)
    {
        printf("Error: Cannot open file.");
        exit(1);
    }

    temp = head;
    while (temp != NULL)
    {
        fprintf(ft, "%d ", temp->id);
        fprintf(ft, "%s ", temp->name);
        fprintf(ft, "%s ", temp->smobile);
        fprintf(ft, "%s ", temp->fname);
        fprintf(ft, "%s ", temp->fmobile);
        fprintf(ft, "%s ", temp->email);
        fprintf(ft, "%s ", temp->course);
        fprintf(ft, "%d\n", temp->fees);
        temp = temp->next;
    }

    fclose(fp);
    fclose(ft);

    remove("StudentRecord.txt");             /// remove the orginal file
    rename("temp.txt", "StudentRecord.txt"); /// rename the temp file to original file name
    gotoxy(1, 7);
    printf("The Record with ID - %d has been successfully updated.", search_id);
    gotoxy(1, 8);
    printf("Please press any key to go back to main menu.");
    getch();
}
// Function to search the record
void searchRecord(void)
{
    system("cls");
    system("color A4");

    // Opening file in a+ mode
    fp = fopen("StudentRecord.txt", "a+");
    if (fp == NULL)
    {
        printf("Error While opening file.");
        exit(1);
    }

    head = NULL;
    while (fscanf(fp, "%d %s %s %s %s %s %s %d", &stu.fid, stu.fname, stu.fsmobile, stu.ffname, stu.ffmobile, stu.femail, stu.fcourse, &stu.ffees) != EOF)
    {
        fnewnode = (st *)malloc(sizeof(st));
        fnewnode->id = stu.fid;
        strcpy(fnewnode->name, stu.fname);
        strcpy(fnewnode->smobile, stu.fsmobile);
        strcpy(fnewnode->fname, stu.ffname);
        strcpy(fnewnode->fmobile, stu.ffmobile);
        strcpy(fnewnode->email, stu.femail);
        strcpy(fnewnode->course, stu.fcourse);
        fnewnode->fees = stu.ffees;
        fnewnode->next = NULL;
        if (head == NULL)
        {
            head = temp = fnewnode;
        }
        else
        {
            temp->next = fnewnode;
            temp = fnewnode;
        }
    }
    int search_id = 0;
    gotoxy(1, 2);
    printf("Whose detail you want to Search? Please Enter ID.  ");
    scanf("%d", &search_id);
    fflush(stdin);
    int flag = 0;
    temp = head;
    while (temp != NULL)
    {
        if (temp->id == search_id)
        {
            flag = 0;
            break;
        }
        temp = temp->next;
        flag = 1;
    }
    if (flag == 1)
    {
        gotoxy(1, 4);
        printf("Sorry, No such record found with ID - %d.", search_id);
        gotoxy(1, 5);
        printf("Please press any key to go back to main menu.");
        fclose(fp);
        getch();
        return;
    }
    system("cls");
    system("color D7");
    details();
    gotoxy(1, 6);
    line(119);
    gotoxy(2, 8);
    printf("%d", temp->id);
    gotoxy(7, 8);
    printf("%s", strupr(temp->name));
    gotoxy(22, 8);
    printf("%s", temp->smobile);
    gotoxy(37, 8);
    printf("%s", strupr(temp->fname));
    gotoxy(52, 8);
    printf("%s", temp->fmobile);
    gotoxy(67, 8);
    printf("%s", temp->email);
    gotoxy(103, 8);
    printf("%s", temp->course);
    gotoxy(113, 8);
    printf("%d", temp->fees);
    gotoxy(1, 11);
    printf("The Record with ID - %d has been successfully found.", search_id);
    gotoxy(1, 12);
    printf("Please press any key to go back to main menu.");
    getch();
}
// Function to exit or terminate th program
void Exit(void)
{
    // Free up the space of linked list
    temp = head;
    while (temp != NULL)
    {
        st *temp1 = temp->next;
        free(temp);
        temp = temp1;
    }

    exit(0); /// exit from the program
}