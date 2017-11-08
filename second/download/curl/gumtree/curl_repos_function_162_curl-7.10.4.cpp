void curl_dofree(void *ptr, int line, const char *source)
{
  struct memdebug *mem;

  if(NULL == ptr) {
    fprintf(stderr, "ILLEGAL free() on NULL at %s:%d\n",
            source, line);
    exit(2);
  }
  mem = (struct memdebug *)((char *)ptr - offsetof(struct memdebug, mem));

  /* destroy  */
  memset(mem->mem, 0x13, mem->size);
  
  /* free for real */
  (free)(mem);

  if(logfile)
    fprintf(logfile, "MEM %s:%d free(%p)\n", source, line, ptr);
}