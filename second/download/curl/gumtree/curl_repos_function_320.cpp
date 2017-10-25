void curl_dofree(void *ptr, int line, const char *source)
{
  struct memdebug *mem;

  curlassert(ptr != NULL);

  mem = (struct memdebug *)((char *)ptr - offsetof(struct memdebug, mem));

  /* destroy  */
  memset(mem->mem, 0x13, mem->size);

  /* free for real */
  (Curl_cfree)(mem);

  if(logfile)
    fprintf(logfile, "MEM %s:%d free(%p)\n", source, line, ptr);
}