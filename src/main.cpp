#include <stdio.h>
#include <time.h>

#include "OneginFunctions.hpp"
#include "StringFunctions.hpp"
#include "Utils.hpp"

// int intC(const void* a, const void* b)
// {
//     return *(int*)a - *(int*)b;
// }

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
    // for (int i = 0; i < 100; i++)
    // {
    // int a[] = {5, 6, 1, 2, 7, 7, 7};
    // size_t n = 7;

    // Sort(a, n, 4, intC);

    // for (size_t i = 0; i < n; i++)
    //     printf("%d ", a[i]);
    // puts("");
    // printf("1 2 5 6 7 7 7\n\n");
    // }

    return 0;
}