#ifndef ONEGIN_FUNCTIONS_HPP
#define ONEGIN_FUNCTIONS_HPP

#include <stddef.h>
#include "string_functions.hpp"

static const char* IGNORED_SYMBOLS = " ,.;:'\"-!";

struct Text
{
    const char* rawText;
    const char* const* lines;
    size_t size;
    size_t numberOfLines;
};

Text CreateText(const char* path);

void DestroyText(Text* text);

void SortTextLines(Text* text, StringCompareMethod sortType);

void PrintRawText(const Text* text);

void PrintTextLines(const Text* text);

#endif
