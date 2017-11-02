void curl_dofree(void *ptr, int line, const char *source)
{
  struct memdebug *mem;

  if(ptr) {

#ifdef __INTEL_COMPILER
#  pragma warning(push)
#  pragma warning(disable:1684)
   /* 1684: conversion from pointer to same-sized integral type */
#endif

    mem = (void *)((char *)ptr - offsetof(struct memdebug, mem));

#ifdef __INTEL_COMPILER
#  pragma warning(pop)
#endif

    /* destroy */
    mt_free_fill(mem->mem, mem->size);

    /* free for real */
    (Curl_cfree)(mem);
  }

  if(source)
    curl_memlog("MEM %s:%d free(%p)\n", source, line, (void *)ptr);
}