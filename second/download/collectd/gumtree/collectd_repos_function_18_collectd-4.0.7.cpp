static lt_ptr
lt_erealloc (addr, size)
     lt_ptr addr;
     size_t size;
{
  lt_ptr mem = lt_dlrealloc (addr, size);
  if (size && !mem)
    LT_DLMUTEX_SETERROR (LT_DLSTRERROR (NO_MEMORY));
  return mem;
}