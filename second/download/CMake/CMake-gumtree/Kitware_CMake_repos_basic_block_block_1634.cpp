{
    kwsysSystem_ptrdiff_t length = *end - *begin;
    char* newBuffer = (char*)malloc((size_t)(*size * 2));
    if (!newBuffer) {
      return 0;
    }
    memcpy(newBuffer, *begin, (size_t)(length) * sizeof(char));
    if (*begin != local) {
      free(*begin);
    }
    *begin = newBuffer;
    *end = *begin + length;
    *size *= 2;
  }