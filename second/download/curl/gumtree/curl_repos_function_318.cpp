char *curl_dostrdup(const char *str, int line, const char *source)
{
  char *mem;
  size_t len;

  curlassert(str != NULL);

  if(countcheck("strdup", line, source))
    return NULL;

  len=strlen(str)+1;

  mem=curl_domalloc(len, 0, NULL); /* NULL prevents logging */
  if (mem)
  memcpy(mem, str, len);

  if(logfile)
    fprintf(logfile, "MEM %s:%d strdup(%p) (%zd) = %p\n",
            source, line, str, len, mem);

  return mem;
}