// g++ main.cpp -o output

#include <ctype.h>
#include <stdio.h>
#include <string.h>



int main()
{
    char *morseAlphabet[27] = {
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--.."  // Z
};

    char input[100];
    char *output[200];

    printf("Hello, input string: \n");
    fgets (input, 100, stdin);

    for (int index = 0; index < strlen(input) - 1; index++){
        if(isalpha(input[index])){
            output[index] = morseAlphabet[toupper(input[index]) - 65];
        }else if(input[index] == ' '){
            output[index] = "/";
        }
    }

    for(int index = 0; index < strlen(input) - 1; index++){
        printf("%s ", output[index]);
    }
    printf("\n");

    return 0;
}