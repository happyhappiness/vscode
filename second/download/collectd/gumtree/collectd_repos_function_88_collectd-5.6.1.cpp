void *
lt__memdup (void const *mem, size_t n)
{
  void *newmem;

  if ((newmem = lt__malloc (n)))
    return memcpy (newmem, mem, n);

  return 0;
}