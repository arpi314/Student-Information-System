#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct studentInfo{
    char studentNumber[15];
    char lastName[15];
    char firstName[15];
    char course[15];
    int yearLevel;
    int age;
    char sex[15];
    int finalGrade;

    int idNumber; 
};
typedef struct studentInfo studentInfo;

struct myNode{
    struct studentInfo *student;
    struct myNode *next;
};
typedef struct myNode myNode;

struct studentList{
    myNode *head;
    myNode *tail;
    int size;
};
typedef struct studentList studentList;

//Necessary Functions
void initList(studentList *list);
myNode* getNode(studentList *list, int index);
myNode* getItem(studentList *list, int index);
void setItem(studentList *list, int index, studentInfo *student);
myNode *createNode(studentInfo *student);
void insertItem(studentList *list, int index, studentInfo *student);
int removeItem(studentList *list, int index); 

//General Functions
studentInfo *createStudent(studentList *list);
void enrolStudent (studentList *list, studentInfo *student);
void dropStudent(studentList *list, char temp[15]);
void editStudent(studentList *list, char temp[15]);
void displayStudent(studentList *list);
void filterLastName(studentList *list, char temp[15]);
void filterStudentNumber(studentList *list, char temp[15]);
void filterYearLevel(studentList *list, int n);
void filterCourse(studentList *list, char temp[15]);
void filterSex(studentList *list, char temp[15]);
void filterPassing(studentList *list);
void filterFailing(studentList *list);
void sortLastName(myNode *start, studentList *list);
void sortStudentNumber(studentList *list);

//Extra Functions
int verifyStudentNum(char arr[15], studentList *list);
void menu();

int main(){

    int choice;
    studentInfo *student;
    studentList list;
    myNode *start = NULL;

    initList(&list);

    char tempChar;
    char temp[15];
    int n;

    do{
        
        printf("\n");
        menu();
        printf("\n\n? ");
        scanf("%i", &choice);

        switch (choice){
            case 1: //Enrol a student
                student = createStudent(&list);
                enrolStudent(&list, student);
                break;

            case 2: //Drop a student
                printf("\nStudent Number: ");
                scanf("%s", &temp);
                dropStudent(&list, temp);
                break;
                
            case 3: //Edit a student
                printf("\nStudent Number: ");
                scanf("%s", &temp);
                editStudent(&list, temp);
                break;
            
            case 4: //Displays all students

                displayStudent(&list);
                break;

            case 5: //Filter by last name
                printf("\nLast Name: ");
                scanf("%s", &temp);
                filterLastName(&list, temp);
                break;

            case 6: //Filter by student number
                printf("\nStudent Number: ");
                scanf("%s", &temp);
                filterStudentNumber(&list, temp);

                break;
            
            case 7://Filter by year level
                printf("\nYear Level: ");
                scanf("%i", &n);
                filterYearLevel(&list, n);
                break;

            case 8://Filter by course
                printf("\nCourse: ");
                scanf("%s", &temp);
                filterCourse(&list, temp);
                break;
            
            case 9: //Filter Sex
                printf("\nSex: ");
                scanf("%s", &temp);
                filterSex(&list, temp);
                break;
            
            case 10: //Filter passing
                printf("\n\nFiltering students with passing grades...\n\n");
                filterPassing(&list);
                break;
            
            case 11://Filter failing
                printf("\n\nFiltering students with failing grades...\n\n");
                filterFailing(&list);
                break;
            
            case 12: 
            
                sortLastName(start, &list);
                break;

            case 13:

                break;
            
            default: 
                break;
        } 

    }while(choice != 14);

    return 0; 
}

//Initialize the list to null
void initList(studentList *list){
    list->head = 0;
    list->tail = 0;
    list->size = 0;
}

//Retrives an item from the list
myNode* getNode(studentList *list, int index){
    myNode *current = list->head;
    for(int i = 0; i<index; i++){
        current = current->next;
    }
    return current;
}

//gets the item looked for in the node
myNode* getItem(studentList *list, int index){ //changed to myNode
    if(index >= 0 && index <= list->size-1){
        myNode* node = getNode(list, index);
        return node;
    }
    return NULL;
}

//changes the values for the item index
void setItem(studentList *list, int index, studentInfo *student){
    if(index >= 0 && index <= list->size-1){
        myNode *node = getNode(list, index);
        node->student = student;
    }
    return; 
}

//create linked node for the list and the necessary info for that 
myNode *createNode(studentInfo *student){
    myNode *a = (myNode*)malloc(sizeof(myNode));
    a->student = student;
    a->next = 0;
    return a;
}

//Inserts student in the list 
void insertItem(studentList *list, int index, studentInfo *student){
    if(index >= 0 && index <= list->size){

        myNode *toInsert = createNode(student); //This creates the node with a value of item

        if (index == 0){ //Inserting at the beginning of the list. 
            toInsert->next = list->head;
            list->head = toInsert;
        }
        if(index == list->size){ //Inserting at the tail 
            if(list->tail != 0){
                list->tail->next = toInsert;
            }
            list->tail = toInsert;
        }
        if(index > 0 && index < list->size){ //Inserting somewhere in the middle of the list
            myNode *previous = getNode(list,index-1);
            toInsert->next = previous->next;
            previous->next = toInsert;
        }
        student->idNumber = list->size; 
    }
}

//Deletes an item on the list
int removeItem(studentList *list, int index){
    if(index >= 0 && index <= list->size-1){
        myNode *toRemove;
        if(index == 0){ //Removes from the head
            toRemove = list->head;
            list->head = toRemove->next;
        }else{
            myNode *previous = getNode(list, index-1);
            toRemove = previous->next;
            previous->next = toRemove->next;
            if(index == list->size-1){
                list->tail = previous;
            }
        }
        free(toRemove);
        list->size--;
    }
}

//Adds student information to the list 
studentInfo *createStudent(studentList *list){

    //does it allocate different memory each time in rerun? 
    studentInfo *student = (studentInfo*)malloc(sizeof(studentInfo));

    char tempStudNum[15], tempLast[15], tempFirst[15], tempCourse[15], tempSex[15];
    int tempYear, tempAge, tempFinal;

    do{
        printf("Student number: \n");
        scanf("%s", &tempStudNum);
    }while(verifyStudentNum(tempStudNum, list) == 0);

    printf("Last Name: \n");
    scanf("%s", &tempLast);

    for(int i = 0; tempLast[i] != '\0';i++){
        if(i == 0){
            if(tempLast[i] >= 'a' && tempLast[i] <= 'z'){
                tempLast[i] -= 32;
            }
        }else{
            if(tempLast[i] >= 'A' && tempLast[i] <= 'Z'){
                tempLast[i] += 32;
            }
        }
    }

    printf("First name: \n");
    scanf("%s", &tempFirst);

    for(int i = 0; tempFirst[i] != '\0';i++){
        if(i == 0){
            if(tempFirst[i] >= 'a' && tempFirst[i] <= 'z'){
                tempFirst[i] -= 32;
            }
        }else{
            if(tempFirst[i] >= 'A' && tempFirst[i] <= 'Z'){
                tempFirst[i] += 32;
            }
        }
    }

    printf("Course: \n");
    scanf("%s", &tempCourse);

    for(int i = 0; tempCourse[i] != '\0'; i++){
        if(tempCourse[i] >= 'a' && tempCourse[i] <= 'z'){
            tempCourse[i] -= 32;
        }
    }

    do{
        printf("Year level: \n");
        scanf("%d", &tempYear);
    }while(tempYear < 0);
        
    do{
        printf("Age: \n");
        scanf(" %d", &tempAge);
    }while(tempAge < 0);
        
    do{
        printf("Sex: \n");
        scanf("%s", &tempSex);

        for(int i = 0; tempSex[i] != '\0';i++){
            if(i == 0){
                if(tempSex[i] >= 'a' && tempSex[i] <= 'z'){
                    tempSex[i] -= 32;
                }
            }else{
                if(tempSex[i] >= 'A' && tempSex[i] <= 'Z'){
                    tempSex[i] += 32;
                }
            }
        }

    }while(strcmp("Female", tempSex) != 0 && strcmp("Male", tempSex) != 0);

    do{
        printf("Final grade: \n");
        scanf(" %d", &tempFinal);
    }while(tempFinal < 0 || tempFinal > 100);

    strcpy(student->studentNumber, tempStudNum);
    strcpy(student->lastName, tempLast);
    strcpy(student->firstName, tempFirst);
    strcpy(student->course, tempCourse);
    student->yearLevel = tempYear;
    student->age = tempAge;
    strcpy(student->sex, tempSex);
    student->finalGrade = tempFinal;

    printf("\n%s added!\n", student->studentNumber);

    return student;
}

//adds student in the list
void enrolStudent (studentList *list, studentInfo *student){
    insertItem(list, list->size, student);
    student->idNumber = list->size; //remember list starts at 0
    list->size++;
}

void dropStudent(studentList *list, char temp[15]){
    
    myNode *student;
    int found = 0;
    for(int i = 0; i < list->size; i++){
        student = getItem(list, i);
        if(strcmp(temp, student->student->studentNumber) == 0){
            removeItem(list, i);
            i =  list->size;
            found = 1;
        }
    }

    if(found){
        printf("\n%s has been dropped.\n", student->student->studentNumber);
    }else{
        printf("\nStudent %s not found.\n", temp);
    }
    
}

void editStudent(studentList *list, char temp[15]){

    int choice; 

    myNode *student;
    for(int i = 0; i <list->size; i++){
        student = getItem(list, i);
        if(strcmp(temp, student->student->studentNumber) == 0){
            do{
                printf("\n\nEdit\n");
                printf("1. Student Number\n");
                printf("2. Last Name\n");
                printf("3. First Name\n");
                printf("4. Course\n");
                printf("5. Year Level\n");
                printf("6. Age\n");
                printf("7. Sex\n");
                printf("8. Final grade\n");
                printf("9. Back\n? ");
                scanf("%i", &choice);

                switch(choice){
                    case 1: 
                        printf("Student number (%s): ", student->student->studentNumber);
                        scanf("%s", student->student->studentNumber);
                        printf("\nStudent number updated!");
                        break;

                    case 2: 
                        printf("Last Name (%s): ", student->student->lastName);
                        scanf("%s", student->student->lastName);
                        printf("\nLast name updated!");
                        break;
                    
                    case 3: 
                        printf("First Name (%s): ", student->student->firstName);
                        scanf("%s", student->student->firstName);
                        printf("\nFirst name updated!");
                        break;

                    case 4: 
                        printf("Course (%s): ", student->student->course);
                        scanf("%s", student->student->course);
                        printf("\nCourse updated!");
                        break;

                    case 5:
                        printf("Year Level (%d): ", student->student->yearLevel);
                        scanf(" %d", &student->student->yearLevel);
                        printf("\nYear level updated!");
                        break;

                    case 6: 
                        printf("Age (%i): ", student->student->age);
                        scanf("%i", &student->student->age);
                        printf("\nAge updated!");
                        break;

                    case 7:
                        printf("Sex (%s): ", student->student->sex);
                        scanf("%s", student->student->sex);
                        printf("\nSex updated!");
                        break;

                    case 8:
                        printf("Final Grade (%i): ", student->student->finalGrade);
                        scanf("%i", &student->student->finalGrade);
                        printf("\nFinal grade updated!");
                        break;
                }

            }while(choice != 9);
        }
    }
}

void displayStudent(studentList *list){
    myNode *student;
    for(int i = 0; i < list->size; i++){
        student = getItem(list, i);
        printf("\n\nStudent Number: %s\n", student->student->studentNumber);
        printf("Last Name: %s\n", student->student->lastName);
        printf("First Name: %s\n", student->student->firstName);
        printf("Course: %s\n", student->student->course);
        printf("Year Level: %i\n", student->student->yearLevel);
        printf("Age: %i\n", student->student->age);
        printf("Sex: %s\n", student->student->sex);
        printf("Final Grade: %i\n", student->student->finalGrade);
    }

    printf("\nDisplaying (%i) of (%i) student(s).\n", list->size,list->size);

}

void filterLastName(studentList *list, char temp[15]){

    myNode *student;
    for(int i = 0; i < list->size; i++){
        student = getItem(list,i);
        if(strcmp(temp, student->student->lastName) == 0){
            printf("\n\nStudent Number: %s\n", student->student->studentNumber);
            printf("Last Name: %s\n", student->student->lastName);
            printf("First Name: %s\n", student->student->firstName);
            printf("Course: %s\n", student->student->course);
            printf("Year Level: %i\n", student->student->yearLevel);
            printf("Age: %i\n", student->student->age);
            printf("Sex: %c\n", student->student->sex);
            printf("Final Grade: %i\n", student->student->finalGrade);
        }
    }
}

void filterStudentNumber(studentList *list, char temp[15]){

    myNode *student;
    for(int i = 0; i <list->size; i++){
        student = getItem(list, i);
        if(strcmp(temp, student->student->studentNumber) == 0){
            printf("\n\nStudent Number: %s\n", student->student->studentNumber);
            printf("Last Name: %s\n", student->student->lastName);
            printf("First Name: %s\n", student->student->firstName);
            printf("Course: %s\n", student->student->course);
            printf("Year Level: %i\n", student->student->yearLevel);
            printf("Age: %i\n", student->student->age);
            printf("Sex: %c\n", student->student->sex);
            printf("Final Grade: %i\n", student->student->finalGrade);
        }
    }
}

void filterYearLevel(studentList *list, int n){

    myNode *student;
    for(int i = 0; i<list->size;i++){
        student = getItem(list, i);
        if(student->student->yearLevel == n){
            printf("\n\nStudent Number: %s\n", student->student->studentNumber);
            printf("Last Name: %s\n", student->student->lastName);
            printf("First Name: %s\n", student->student->firstName);
            printf("Course: %s\n", student->student->course);
            printf("Year Level: %i\n", student->student->yearLevel);
            printf("Age: %i\n", student->student->age);
            printf("Sex: %c\n", student->student->sex);
            printf("Final Grade: %i\n", student->student->finalGrade);
        }
    }
}

void filterCourse(studentList *list, char temp[15]){

    myNode *student;
    for(int i = 0; i<list->size;i++){
        student = getItem(list, i);
        if(strcmp(temp, student->student->course) == 0){
            printf("\n\nStudent Number: %s\n", student->student->studentNumber);
            printf("Last Name: %s\n", student->student->lastName);
            printf("First Name: %s\n", student->student->firstName);
            printf("Course: %s\n", student->student->course);
            printf("Year Level: %i\n", student->student->yearLevel);
            printf("Age: %i\n", student->student->age);
            printf("Sex: %s\n", student->student->sex);
            printf("Final Grade: %i\n", student->student->finalGrade);
        }
    }
}


void filterSex(studentList *list, char temp[15]){

    myNode *student;
    for(int i = 0; i<list->size;i++){
        student = getItem(list, i);
        if(strcmp(student->student->sex, temp) == 0){
            printf("\n\nStudent Number: %s\n", student->student->studentNumber);
            printf("Last Name: %s\n", student->student->lastName);
            printf("First Name: %s\n", student->student->firstName);
            printf("Course: %s\n", student->student->course);
            printf("Year Level: %i\n", student->student->yearLevel);
            printf("Age: %i\n", student->student->age);
            printf("Sex: %s\n", student->student->sex);
            printf("Final Grade: %i\n", student->student->finalGrade);
        }
    }
}

void filterPassing(studentList *list){

    myNode *student;
    for(int i = 0; i<list->size;i++){
        student = getItem(list, i);
        if(student->student->finalGrade >= 75){
            printf("\n\nStudent Number: %s\n", student->student->studentNumber);
            printf("Last Name: %s\n", student->student->lastName);
            printf("First Name: %s\n", student->student->firstName);
            printf("Course: %s\n", student->student->course);
            printf("Year Level: %i\n", student->student->yearLevel);
            printf("Age: %i\n", student->student->age);
            printf("Sex: %s\n", student->student->sex);
            printf("Final Grade: %i\n", student->student->finalGrade);
        }
    }
}

void filterFailing(studentList *list){

    myNode *student;
    for(int i = 0; i<list->size;i++){
        student = getItem(list, i);
        if(student->student->finalGrade < 75){
            printf("\n\nStudent Number: %s\n", student->student->studentNumber);
            printf("Last Name: %s\n", student->student->lastName);
            printf("First Name: %s\n", student->student->firstName);
            printf("Course: %s\n", student->student->course);
            printf("Year Level: %i\n", student->student->yearLevel);
            printf("Age: %i\n", student->student->age);
            printf("Sex: %s\n", student->student->sex);
            printf("Final Grade: %i\n", student->student->finalGrade);
        }
    }

}

//Doesnt work 
void sortLastName(myNode *start, studentList *list){

    int ok, i;
    struct myNode *ptr1, *temp;
    struct myNode *lptr = NULL;

    if(start == NULL){
        return;
    }

    do{
        ok = 0;
        ptr1 = start;

        while(ptr1->next != lptr){
            if(strcmp(ptr1->student->lastName, ptr1->next->student->lastName) > 0){
                temp->student = ptr1->student;
                ptr1->student = ptr1->next->student;
                ptr1->next->student = temp->student;
                ok = 1; 
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }while(ok);

    for(int i = 0; i < list->size; i++){
        lptr = getItem(list, i);
        printf("\n\nStudent Number: %s\n", lptr->student->studentNumber);
        printf("Last Name: %s\n", lptr->student->lastName);
        printf("First Name: %s\n", lptr->student->firstName);
        printf("Course: %s\n", lptr->student->course);
        printf("Year Level: %i\n", lptr->student->yearLevel);
        printf("Age: %i\n", lptr->student->age);
        printf("Sex: %c\n", lptr->student->sex);
        printf("Final Grade: %i\n", lptr->student->finalGrade);
    }

}

void menu(){

    printf("1. Enrol a student\n");
    printf("2. Drop a student\n");
    printf("3. Edit a student\n");
    printf("4. Display all students\n");
    printf("5. Filter students by last name\n");
    printf("6. Filter students by student number\n");
    printf("7. Filter students by year level\n");
    printf("8. Filter students by course\n");
    printf("9. Filter students by sex\n");
    printf("10. Filter students by passing\n");
    printf("11. Filter students by failing\n");
    printf("12. Sort students by last name\n");
    printf("13. Sort students by student number\n");
    printf("14. Exit\n");

}

int verifyStudentNum(char arr[15], studentList *list){

    myNode *s;
    int ok = 0, valid = 0;

    for(int i = 0; arr[i] != '\0'; i++){
        if(arr[i] < 48 || arr[i] > 57){
            valid++; 
        }else if(arr[4] == '-'){
            valid++;
        }
    }

    if(valid == strlen(arr)){
        ok++;
    }else{
        ok = 0;
    }

    for(int i = 0; i <list->size; i++){
        s = getItem(list, i);
        if(strcmp(s->student->studentNumber, arr) == 0){
            ok = 0;
        }
    }
    return ok; 
}