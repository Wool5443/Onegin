#include <stdio.h>
#include <time.h>

#include "OneginFunctions.hpp"
#include "StringFunctions.hpp"
#include "Utils.hpp"

int main(const int argc, const char* const* argv)
{
    if (argc < 3)
    {
        printf("Enter input and output paths!\n");
        return -1;
    }

    Text hamlet = CreateText(argv[1]);
    FILE* out = fopen(argv[2], "w");

    clock_t start = clock();
    SortTextLines(&hamlet, START_TO_END);
    printf("Sorting took %g seconds\n", ((double)(clock() - start)) / CLOCKS_PER_SEC);

    fputs("[Alphabetic sort Start To End.]\n\n", out);
    PrintTextLines(&hamlet, out);
    fputs("------------------------------------------------------------------------------------------\n", out);

    start = clock();
    SortTextLines(&hamlet, END_TO_START);
    printf("Sorting took %g seconds\n", ((double)(clock() - start)) / CLOCKS_PER_SEC);

    fputs("[Alphabetic sort End To Start.]\n\n", out);
    PrintTextLines(&hamlet, out);
    fputs("------------------------------------------------------------------------------------------\n", out);

    fputs("[Original text.]\n\n", out);
    PrintRawText(&hamlet, out);

    DestroyText(&hamlet);
    fclose(out);

    return 0;
}