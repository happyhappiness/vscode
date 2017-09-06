static void print_hex(FILE *handle, const char *buf, size_t len)
{
  const char *p = buf;
  fprintf(stderr, "0x");
  while (len-- > 0)
    fprintf(stderr, "%02.2x", (unsigned int)*p++);
}