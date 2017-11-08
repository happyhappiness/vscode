void *curl_domalloc(size_t wantedsize, int line, const char *source)
{
  struct memdebug *mem;
  size_t size;

  if(countcheck("malloc", line, source))
    return NULL;

  /* alloc at least 64 bytes */
  size = sizeof(struct memdebug)+wantedsize;

  mem=(struct memdebug *)(Curl_cmalloc)(size);
  if(mem) {
    /* fill memory with junk */
    memset(mem->mem, 0xA5, wantedsize);
    mem->size = wantedsize;
  }

  if(logfile && source)
    fprintf(logfile, "MEM %s:%d malloc(%zd) = %p\n",
            source, line, wantedsize, mem ? mem->mem : 0);
  return (mem ? mem->mem : NULL);
}