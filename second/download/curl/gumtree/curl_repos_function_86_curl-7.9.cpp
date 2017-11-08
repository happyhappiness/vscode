void *curl_dorealloc(void *ptr, size_t size, int line, const char *source)
{
  void *mem=(realloc)(ptr, size);
  fprintf(logfile?logfile:stderr, "MEM %s:%d realloc(%p, %d) = %p\n",
          source, line, ptr, size, mem);
  return mem;
}