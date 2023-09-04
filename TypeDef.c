#include<stdio.h>
typedef struct student
{
int id;
int mark;
char fav_character;
char name[43];
} std;

int main(){
    std s1,s2;
    s1.id=69;
    printf("%d\n",s1.id);
    int* a,b;
    int c=20;
    a=&c;
    // b=&c;
    
    typedef int* pointers;
    pointers x,y;
    int d=30;
    x=&c;
    y=&d;
    return 0;
}