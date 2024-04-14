#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct student_t {
    char * name;
    int sid;
};

void *print_info(void *input) {
    printf("Name: %s\n", ((struct student_t*)input)->name);
    printf("Student ID: %d\n", ((struct student_t*)input)->sid);
}

int main(int argc, char* argv[]) {
    
    return 0;
}