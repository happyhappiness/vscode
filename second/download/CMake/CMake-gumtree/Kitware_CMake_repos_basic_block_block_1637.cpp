{
    kwsysSystem_ptrdiff_t length = *end - *begin;
    char** newPointers = (char**)malloc((size_t)(*size) * 2 * sizeof(char*));
    if (!newPointers) {
      return 0;
    }
    memcpy(newPointers, *begin, (size_t)(length) * sizeof(char*));
    if (*begin != local) {
      free(*begin);
    }
    *begin = newPointers;
    *end = *begin + length;
    *size *= 2;
  }