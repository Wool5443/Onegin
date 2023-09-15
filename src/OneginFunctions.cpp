#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "OneginFunctions.hpp"
#include "Utils.hpp"
#include "StringFunctions.hpp"

size_t getFileSize(const char* path);

size_t countLines(const char* string);

const char* const* split(const char* string, size_t numOfLines);

int _stringCompareStartToEnd(const void* s1, const void* s2);

int _stringCompareEndToStart(const void* s1, const void* s2);

Text CreateText(const char* path)
{
    MyAssertHard(path, ERROR_NULLPTR, );

    Text text = {};

    text.size = getFileSize(path);
    
    char* rawText = (char*)calloc(text.size + 1, sizeof(char));

    FILE* file = fopen(path, "rb");
    MyAssertHard(file, ERROR_BAD_FILE, );
    MyAssertHard(text.size == fread(rawText, sizeof(char), text.size, file), ERROR_BAD_FILE, );
    fclose(file); 

    rawText[text.size] = '\0';

    text.rawText = rawText;

    text.numberOfLines = countLines(rawText);

    text.lines = split(rawText, text.numberOfLines);

    return text;
}

void DestroyText(Text* text)
{
    MyAssertHard(text, ERROR_NULLPTR, );
    free((void*)(text->lines));
    free((void*)(text->rawText));
}

void SortTextLines(Text* text, StringCompareMethod sortType)
{
    switch (sortType)
    {
        case START_TO_END:
            Sort((void*)(text->lines), text->numberOfLines, sizeof((text->lines)[0]), _stringCompareStartToEnd);
            break;
        case END_TO_START:
            Sort((void*)(text->lines), text->numberOfLines, sizeof((text->lines)[0]), _stringCompareEndToStart);
            break;
        default:
            Sort((void*)(text->lines), text->numberOfLines, sizeof((text->lines)[0]), _stringCompareStartToEnd);
            break;
    }
}

void PrintRawText(const Text* text, FILE* file)
{
    fputs(text->rawText, file);
}

void PrintTextLines(const Text* text, FILE* file)
{
    for (size_t i = 0; i < text->numberOfLines; i++)
    {
        const char* line = text->lines[i];
        if (*line != '\n')
            StringPrint(file, line, '\n');
    }
}

int _stringCompareStartToEnd(const void* s1, const void* s2)
{
    return StringCompare(*(const char* const*)s1, *(const char* const*)s2, START_TO_END, IGNORE_CASE, IGNORED_SYMBOLS, '\n');
}

int _stringCompareEndToStart(const void* s1, const void* s2)
{
    return StringCompare(*(const char* const*)s1, *(const char* const*)s2, END_TO_START, IGNORE_CASE, IGNORED_SYMBOLS, '\n');
}

size_t getFileSize(const char* path)
{
    MyAssertHard(path, ERROR_NULLPTR, );

    struct stat result = {};
    stat(path, &result);

    return (size_t)result.st_size;
}

size_t countLines(const char* string)
{
    MyAssertHard(string, ERROR_NULLPTR, );

    size_t lines = 1;
    const char* newLineSymbol = strchr(string, '\n');
    while (newLineSymbol != NULL)
    {
        lines++;
        newLineSymbol = strchr(newLineSymbol + 1, '\n');
    }
    return lines;
}

const char* const* split(const char* string, size_t numOfLines)
{
    MyAssertHard(string, ERROR_NULLPTR, );

    const char** lines = (const char**)calloc(numOfLines, sizeof(lines[0]));

    MyAssertHard(lines, ERROR_NO_MEMORY, );

    lines[0] = string;

    const char* endCurLine = strchr(string, '\n');
    size_t i = 1;

    while (endCurLine)
    {
        lines[i] = endCurLine + 1;
        endCurLine = strchr(endCurLine + 1, '\n');
        i++;
    }

    return (const char* const*)lines;
}
