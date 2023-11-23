#include <stdio.h>
#include <time.h>

#include "OneginFunctions.hpp"
#include "StringFunctions.hpp"
#include "Utils.hpp"

#ifdef TESTING
int intC(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}
#endif

int main(const int argc, const char* const* argv)
{
#ifndef TESTING
    if (argc < 3)
    {
        printf("Enter input and output paths!\n");
        return -1;
    }

    Text hamlet = CreateText(argv[1], '\n');
    FILE* out = fopen(argv[2], "w");

    clock_t start = clock();
    SortTextTokens(&hamlet, START_TO_END);
    printf("Sorting took %g seconds\n", ((double)(clock() - start)) / CLOCKS_PER_SEC);

    fputs("[Alphabetic sort Start To End.]\n\n", out);
    PrintTextTokens(&hamlet, out, '\n');
    fputs("------------------------------------------------------------------------------------------\n", out);

    start = clock();
    SortTextTokens(&hamlet, END_TO_START);
    printf("Sorting took %g seconds\n", ((double)(clock() - start)) / CLOCKS_PER_SEC);

    fputs("[Alphabetic sort End To Start.]\n\n", out);
    PrintTextTokens(&hamlet, out, '\n');
    fputs("------------------------------------------------------------------------------------------\n", out);

    fputs("[Original text.]\n\n", out);
    PrintRawText(&hamlet, out);

    DestroyText(&hamlet);
    fclose(out);
#else
    for (int k = 0; k < 1; k++)
    {
        int a[] = {5, 3, 1, 5, 8, 6, 3, 1};
        size_t n = sizeof(a) / sizeof(a[0]);

        Sort(a, n, 4, intC);

        for (size_t i = 0; i < n; i++)
            printf("%d ", a[i]);
        puts("");
    }
#endif
    return 0;
}