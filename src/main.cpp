#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "OneginFunctions.hpp"
#include "string_functions.hpp"

int main(void)
{
    const char HAMLET_PATH[] = "hamlet.txt";
    size_t hamletLength = GetFileLength(HAMLET_PATH);

    char* rawText = (char*)calloc(hamletLength + 2, sizeof(char));
    rawText[hamletLength] = '\n';
    rawText[hamletLength + 1] = '\0';
    FILE* hamlet = fopen(HAMLET_PATH, "r");
    fread(rawText, sizeof(char), hamletLength, hamlet);
    fclose(hamlet);

    puts(rawText);
    free(rawText);

    return 0;
}