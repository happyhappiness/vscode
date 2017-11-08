void *curl_domalloc(size_t wantedsize, int line, const char *source)
{
  struct memdebug *mem;
  size_t size;

  assert(wantedsize != 0);

  if(countcheck("malloc", line, source))
    return NULL;

  /* alloc at least 64 bytes */
  size = sizeof(struct memdebug)+wantedsize;

  mem = (Curl_cmalloc)(size);
  if(mem) {
    /* fill memory with junk */
    mt_malloc_fill(mem->mem, wantedsize);
    mem->size = wantedsize;
  }

  if(source)
    curl_memlog("MEM %s:%d malloc(%zu) = %p\n",
                source, line, wantedsize,
                mem ? (void *)mem->mem : (void *)0);

  return (mem ? mem->mem : NULL);
}