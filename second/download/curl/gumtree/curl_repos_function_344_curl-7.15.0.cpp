void *curl_docalloc(size_t wanted_elements, size_t wanted_size,
                    int line, const char *source)
{
  struct memdebug *mem;
  size_t size, user_size;

  if(countcheck("calloc", line, source))
    return NULL;

  /* alloc at least 64 bytes */
  user_size = wanted_size * wanted_elements;
  size = sizeof(struct memdebug) + user_size;

  mem = (struct memdebug *)(Curl_cmalloc)(size);
  if(mem) {
    /* fill memory with zeroes */
    memset(mem->mem, 0, user_size);
    mem->size = user_size;
  }

  if(logfile && source)
    fprintf(logfile, "MEM %s:%d calloc(%u,%u) = %p\n",
            source, line, wanted_elements, wanted_size, mem ? mem->mem : 0);
  return (mem ? mem->mem : NULL);
}