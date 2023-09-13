#include <ctype.h>
#include "StringFunctions.hpp"
#include "Utils.hpp"

const int INCLUDE_NULL_TERMINATOR_FIX = 1, FOUND_STRING = -1, ALPHABET_LENGTH = 256;

int findShift(const char* where, const char* target, const size_t place, const size_t targetLength);

int stringCompareStartToEnd(const char* s1, const char* s2, CaseOptions caseOption, const char* filter, char terminator);

int stringCompareEndToStart(const char* s1, const char* s2, CaseOptions caseOption, const char* filter, char terminator);

int checkFilter(char c, const char* filter);

size_t StringLength(const char* string)
{
    MyAssertHard(string, ERROR_NULLPTR, );

    size_t length = 0;
    while (*string++ != '\0')
        length++;

    return length;
}

char* StringCopy(char* destination, const char* source, size_t maxLength)
{
    MyAssertHard(destination, ERROR_NULLPTR, );
    MyAssertHard(source, ERROR_NULLPTR, );

    size_t sourceLength = StringLength(source);
    size_t numOfElToCopy = min(sourceLength, maxLength - INCLUDE_NULL_TERMINATOR_FIX);

    MyAssertHard(destination + maxLength <= source
        || source + sourceLength < destination,
        ERROR_OVERLAP,
        );

    for (size_t i = 0; i < numOfElToCopy; i++)
        destination[i] = source[i];

    destination[numOfElToCopy] = '\0';

    return destination;
}

char* StringCopyAll(char* destination, const char* source)
{
    MyAssertHard(destination, ERROR_NULLPTR, );
    MyAssertHard(source, ERROR_NULLPTR, );

    size_t sourceLength = StringLength(source);

    MyAssertHard(destination + sourceLength < source
        || source + sourceLength < destination,
        ERROR_OVERLAP,
        );

    for (size_t i = 0; i < sourceLength - 1; i++)
        destination[i] = source[i];

    destination[sourceLength - 1] = '\0';

    return destination;
}

char* StringCat(char* destination, const char* source, size_t maxLength)
{
    MyAssertHard(destination, ERROR_NULLPTR, );
    MyAssertHard(source, ERROR_NULLPTR, );

    size_t destinationLength = StringLength(destination);

    return StringCopy(destination + destinationLength, source, maxLength - destinationLength) - destinationLength;
}

int StringCompare(const char* s1, const char* s2, StringCompareMethod stringCompareMethod, CaseOptions caseOption, const char* filter, char terminator)
{
    MyAssertHard(s1, ERROR_NULLPTR, );
    MyAssertHard(s2, ERROR_NULLPTR, );

    switch (stringCompareMethod)
    {
        case START_TO_END:
            return stringCompareStartToEnd(s1, s2, caseOption, filter, terminator);
        case END_TO_START:
            return stringCompareEndToStart(s1, s2, caseOption, filter, terminator);
        default:
            return 0;
    }
}

int stringCompareStartToEnd(const char* s1, const char* s2, CaseOptions caseOption, const char* filter, char terminator)
{
    MyAssertHard(s1, ERROR_NULLPTR, );
    MyAssertHard(s2, ERROR_NULLPTR, );

    while (*s1 != terminator && *s2 != terminator && *s1 != 0 && *s2 != 0)
    {
        if (*s1 == *s2 || (caseOption == IGNORE_CASE && tolower(*s1) == tolower(*s2)))
        {
            s1++;
            s2++;
            continue;
        }
        int checkS1 = checkFilter(*s1, filter);
        int checkS2 = checkFilter(*s2, filter);

        if (checkS1 && checkS2)
            break;
            
        s1 += !checkS1;
        s2 += !checkS2;
    }

    return caseOption == IGNORE_CASE ? tolower(*s1) - tolower(*s2) : *s1 - *s2;
}

int stringCompareEndToStart(const char* s1, const char* s2, CaseOptions caseOption, const char* filter, char terminator)
{
    MyAssertHard(s1, ERROR_NULLPTR, );
    MyAssertHard(s2, ERROR_NULLPTR, );

    const char* s1Arrow = s1;
    const char* s2Arrow = s2;

    while (*s1Arrow != terminator && *s1Arrow != 0)
        s1Arrow++;
    while (*s2Arrow != terminator && *s2Arrow != 0)
        s2Arrow++;

    s1Arrow--;
    s2Arrow--;

    while (s1Arrow >= s1 && s2Arrow >= s2)
    {
        if (*s1Arrow == *s2Arrow || (caseOption == IGNORE_CASE && tolower(*s1Arrow) == tolower(*s2Arrow)))
        {
            s1Arrow--;
            s2Arrow--;
            continue;
        }
        
        int checkS1Arrow = checkFilter(*s1Arrow, filter);
        int checkS2Arrow = checkFilter(*s2Arrow, filter);

        if (checkS1Arrow && checkS2Arrow)
            break;

        s1Arrow -= !checkS1Arrow;
        s2Arrow -= !checkS2Arrow;
    }

    return caseOption == IGNORE_CASE ? tolower(*s1Arrow) - tolower(*s2Arrow) : *s1Arrow - *s2Arrow;
}

int checkFilter(char c, const char* filter)
{
    MyAssertHard(filter, ERROR_NULLPTR, );

    while (*filter != 0)
    {
        if (c == *filter)
            return 0; // to be filtered out
        filter++;
    }
    return 1;         // to stay
}

bool StringEqual(const char* s1, const char* s2, const size_t length)
{
    MyAssertHard(s2, ERROR_NULLPTR, );
    MyAssertHard(s1, ERROR_NULLPTR, );

    size_t s1Length = StringLength(s1);
    size_t s2Length = StringLength(s2);

    if (s1Length < length || s2Length < length)
        return false;

    for (size_t i = 0; i < length; i++)
        if (s1[i] != s2[i])
            return false;

    return true;
}

char* StringFind(char* where, const char* target)
{
    MyAssertHard(where, ERROR_NULLPTR, );
    MyAssertHard(target, ERROR_NULLPTR, );

    size_t whereLength = StringLength(where);
    size_t targetLength = StringLength(target);
    if (whereLength < targetLength)
        return NULL;

    size_t shifts[ALPHABET_LENGTH] = {};

    for (size_t i = 0; i < ArrayLength(shifts); i++)
        shifts[i] = targetLength;

    for (size_t i = 2; i < targetLength + 1; i++)
    {
        int c = target[targetLength - i];
        shifts[c] = min(shifts[c], i - 1);
    }

    size_t place = 0;

    while (place + targetLength - 1 < whereLength)
    {
        int shiftChar = findShift(where, target, place, targetLength);
        if (shiftChar == FOUND_STRING)
            return where + place;
        place += shifts[shiftChar];
    }

    return NULL;
}

int findShift(const char* where, const char* target, const size_t place, const size_t targetLength)
{
    MyAssertHard(where, ERROR_NULLPTR, );
    MyAssertHard(target, ERROR_NULLPTR, );

    for (size_t i = 0; i < targetLength; i++)
        if (where[place + targetLength - 1 - i] != target[targetLength - 1 - i])
            return where[place + targetLength - 1 - i];
    return FOUND_STRING;
}

char* StringFindChar(char* where, const char target)
{
    MyAssertHard(where, ERROR_NULLPTR, );

    while (*where != '\0')
    {
        if (*where == target)
            return where;
        where++;
    }

    return NULL;
}

char* StringFilter(char* string, const char* filter)
{
    MyAssertHard(string, ERROR_NULLPTR, );
    MyAssertHard(filter, ERROR_NULLPTR, );

    const char* readPtr = string;
    char* writePtr = string;

    while (*readPtr != 0 && *readPtr != '\n')
    {
        char c = *readPtr++;

        if (checkFilter(c, filter))
            *writePtr++ = c;
    }
    *writePtr = '\0';

    return string;
}

void StringPrint(FILE* where, const char* string, char terminator)
{
    MyAssertHard(string, ERROR_NULLPTR, );
    MyAssertHard(where, ERROR_BAD_FILE, );

    while (*string != terminator && *string != 0)
        putc(*string++, where);
    putc('\n', where);
}
