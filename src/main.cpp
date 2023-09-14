#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "OneginFunctions.hpp"
#include "StringFunctions.hpp"
#include "Utils.hpp"


int main(void)
{
    const char HAMLET_PATH[] = "hamlet.txt";

    Text hamlet = CreateText(HAMLET_PATH);
    FILE* out = fopen("out.txt", "w");

    SortTextLines(&hamlet, START_TO_END);

    fputs("[Alphabetic sort start to end]\n\n", out);

    for (size_t i = 0; i < hamlet.numberOfLines; i++)
        if (!StringEqual(hamlet.lines[i], "\n", 1))
            StringPrint(out, hamlet.lines[i], '\n');

    fputs("-------------------------------------------------------------------------------------\n", out);
    fputs("[Alphabetic sort end to start]\n\n", out);

    clock_t t = clock();
    SortTextLines(&hamlet, END_TO_START);
    printf("Sorting took %g seconds\n", (double)(clock() - t) / CLOCKS_PER_SEC);

    for (size_t i = 0; i < hamlet.numberOfLines; i++)
        if (!StringEqual(hamlet.lines[i], "\n", 1))
            StringPrint(out, hamlet.lines[i], '\n');
            
    fputs("-------------------------------------------------------------------------------------\n", out);
    fputs("[Original text]\n\n", out);

    fputs(hamlet.rawText, out);

    DestroyText(&hamlet);
    fclose(out);

    return 0;
}