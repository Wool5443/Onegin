#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "OneginFunctions.hpp"
#include "StringFunctions.hpp"
#include "Utils.hpp"

int main(void)
{
    const char HAMLET_PATH[] = "hamlet2.txt";

    Text hamlet = CreateText(HAMLET_PATH);
    FILE* out = fopen("out.txt", "w");

    SortTextLines(&hamlet, START_TO_END);

    for (size_t i = 0; i < hamlet.numberOfLines; i++)
        if (!StringEqual(hamlet.lines[i], "\n", 1))
            StringPrint(out, hamlet.lines[i], '\n');

    fputs("-------------------------------------------------------------------------------------\n", out);

    SortTextLines(&hamlet, END_TO_START);

    for (size_t i = 0; i < hamlet.numberOfLines; i++)
        if (!StringEqual(hamlet.lines[i], "\n", 1))
            StringPrint(out, hamlet.lines[i], '\n');
            
    fputs("-------------------------------------------------------------------------------------\n", out);

    fputs(hamlet.rawText, out);

    DestroyText(&hamlet);
    fclose(out);

    return 0;
}