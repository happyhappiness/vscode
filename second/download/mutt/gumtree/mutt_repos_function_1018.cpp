static inline int is_ascii (const char *p, size_t len) {
  register const char *s = p;
  while (s && (unsigned) (s - p) < len) {
    if ((*s & 0x80) != 0)
      return 0;
    s++;
  }
  return 1;
}