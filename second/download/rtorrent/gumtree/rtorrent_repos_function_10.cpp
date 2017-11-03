inline size_t
strlcpy(char *dest, const char *src, size_t size) {
  size_t n = size;
  const char* first = src;

  if (n != 0) {
    while (--n != 0)
      if ((*dest++ = *src++) == '\0')
        break;
  }

  if (n == 0) {
    if (size != 0)
      *dest = '\0';
    
    while (*src++)
      ;
  }

  return src - first - 1;
}