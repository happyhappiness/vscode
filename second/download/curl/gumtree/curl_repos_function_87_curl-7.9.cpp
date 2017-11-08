void curl_dofree(void *ptr, int line, const char *source)
{
  if(NULL == ptr) {
    fprintf(stderr, "ILLEGAL free() on NULL at %s:%d\n",
            source, line);
    exit(2);
  }

  (free)(ptr);

  fprintf(logfile?logfile:stderr, "MEM %s:%d free(%p)\n",
          source, line, ptr);
}