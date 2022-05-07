#include <string.h>
#include <stdio.h>
int main(){
    char str[] = "Rock,Pop,Punk";
    char *token = strtok(str, ",");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
    printf("%s\n", str);

}
