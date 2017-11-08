void *curl_domalloc(size_t size, int line, const char *source)
{
  void *mem=(malloc)(size);
  fprintf(logfile?logfile:stderr, "MEM %s:%d malloc(%d) = %p\n",
          source, line, size, mem);
  return mem;
}