void *curl_dorealloc(void *ptr, size_t wantedsize,
                     int line, const char *source)
{
  struct memdebug *mem;

  size_t size = sizeof(struct memdebug)+wantedsize;

  mem = (struct memdebug *)((char *)ptr - offsetof(struct memdebug, mem));

  mem=(struct memdebug *)(realloc)(mem, size);
  if(logfile)
    fprintf(logfile, "MEM %s:%d realloc(%p, %d) = %p\n",
            source, line, ptr, wantedsize, mem?mem->mem:NULL);

  if(mem) {
    mem->size = wantedsize;
    return mem->mem;
  }

  return NULL;
}