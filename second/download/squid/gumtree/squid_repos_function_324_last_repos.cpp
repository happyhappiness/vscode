void *
lt__zalloc (size_t n)
{
  void *mem;

  if ((mem = lt__malloc (n)))
    memset (mem, 0, n);

  return mem;
}