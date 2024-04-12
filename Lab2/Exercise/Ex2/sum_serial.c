#include "header.h"

typedef long long ll;
ll sum = 0;

void * sumSerial()

int main(int argc, char * argv[]){
    printf("Num of thread: %d", atoi(argv[1]));
    printf("Result = %lld\n", sumSerial(atoi(argv[1])));
}
