#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "OneginFunctions.hpp"

int main(void)
{
    const char HAMLET_PATH[] = "hamlet.txt";

    const size_t MAX_LINES = 10,
                 MAX_LINE_LENGTH = 200;

    size_t hamletLength = GetFileLength(HAMLET_PATH);

    char* rawText = (char*)calloc(hamletLength + 2, sizeof(char));

    FILE* hamlet = fopen(HAMLET_PATH, "r");

    fread(rawText, MAX_LINES, MAX_LINE_LENGTH, hamlet);

    fclose(hamlet);

    printf(rawText);

    free(rawText);

    return 0;
}