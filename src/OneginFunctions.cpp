#include <sys/stat.h>
#include "OneginFunctions.hpp"

size_t GetFileLength(const char* path)
{
    struct stat result = {};
    stat(path, &result);

    return result.st_size;
}
