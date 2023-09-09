#include <sys/stat.h>
#include "OneginFunctions.hpp"

size_t GetFileLength(const char* path)
{
    struct stat result = {};
    stat(path, &result);

    return (size_t)result.st_size;
}
