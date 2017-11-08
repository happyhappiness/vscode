char *curl_dostrdup(const char *str, int line, const char *source)
{
  char *mem;
  size_t len;
  
  if(NULL ==str) {
    fprintf(stderr, "ILLEGAL strdup() on NULL at %s:%d\n",
            source, line);
    exit(2);
  }

  len=strlen(str)+1;

  mem=curl_domalloc(len, 0, NULL); /* NULL prevents logging */
  memcpy(mem, str, len);

  if(logfile)
    fprintf(logfile, "MEM %s:%d strdup(%p) (%d) = %p\n",
            source, line, str, len, mem);

  return mem;
}