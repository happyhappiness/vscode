void *curl_dorealloc(void *ptr, size_t wantedsize,
                     int line, const char *source)
{
  struct memdebug *mem=NULL;

  size_t size = sizeof(struct memdebug)+wantedsize;

  if(countcheck("realloc", line, source))
    return NULL;

  if(ptr)
    mem = (struct memdebug *)((char *)ptr - offsetof(struct memdebug, mem));

  mem=(struct memdebug *)(Curl_crealloc)(mem, size);
  if(logfile)
    fprintf(logfile, "MEM %s:%d realloc(%p, %zd) = %p\n",
            source, line, ptr, wantedsize, mem?mem->mem:NULL);

  if(mem) {
    mem->size = wantedsize;
    return mem->mem;
  }

  return NULL;
}