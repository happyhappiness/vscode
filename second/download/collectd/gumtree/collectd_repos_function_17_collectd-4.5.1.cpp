static lt_ptr
lt_emalloc (size)
     size_t size;
{
  lt_ptr mem = lt_dlmalloc (size);
  if (size && !mem)
    LT_DLMUTEX_SETERROR (LT_DLSTRERROR (NO_MEMORY));
  return mem;
}