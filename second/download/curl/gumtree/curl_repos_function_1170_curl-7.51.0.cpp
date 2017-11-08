void *curl_docalloc(size_t wanted_elements, size_t wanted_size,
                    int line, const char *source)
{
  struct memdebug *mem;
  size_t size, user_size;

  assert(wanted_elements != 0);
  assert(wanted_size != 0);

  if(countcheck("calloc", line, source))
    return NULL;

  /* alloc at least 64 bytes */
  user_size = wanted_size * wanted_elements;
  size = sizeof(struct memdebug) + user_size;

  mem = (Curl_ccalloc)(1, size);
  if(mem)
    mem->size = user_size;

  if(source)
    curl_memlog("MEM %s:%d calloc(%zu,%zu) = %p\n",
                source, line, wanted_elements, wanted_size,
                mem ? (void *)mem->mem : (void *)0);

  return (mem ? mem->mem : NULL);
}